#!/usr/bin/env python3
"""afs_index.py — print a stable table of every ``_DATA.AFS`` entry.

Reads:
  * ``God Hand (USA).iso``     for the ``_DATA.AFS`` blob (LBA from ISO9660,
                               magic/entries from the AFS header; the AFS
                               payload is never materialised to disk).
  * ``disc_extract/GODHAND.FST`` for human-readable names (must have been
                               extracted via ``scripts/extract_iso.sh``).

Prints to stdout, one line per AFS entry sorted by index, columns::

    idx     offset       size  sha256_8  name

The sha256_8 column is the first 8 hex chars of sha256(<full blob bytes>);
stable, abbreviating, and cheap to diff.  Reading every entry to hash it
takes ~5-10 s for the full 1.5 GB ISO on commodity SSD.

Usage::

    python scripts/afs_index.py [-i path/to/'God Hand (USA).iso']
                                [-f path/to/GODHAND.FST]
                                [--no-hash]

Exit codes:
  0   success
  1   user / I/O error (missing ISO or FST, no read permission)
  2   format error    (AFS magic mismatch, FST schema mismatch, etc.)

See ``scripts/afs.py`` for the format reference; ``scripts/afs_extract.py``
for the targeted extractor that produces ``disc_extract/rel/``.

Produces a stable index table without writing the AFS to disk.
"""
from __future__ import annotations

import argparse
import hashlib
import os
import sys
from pathlib import Path

# Make ``scripts/`` importable when this file is run as ``python scripts/...``.
sys.path.insert(0, str(Path(__file__).resolve().parent))
import afs  # noqa: E402

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_ISO = REPO_ROOT / "God Hand (USA).iso"
DEFAULT_FST = REPO_ROOT / "disc_extract" / "GODHAND.FST"

# Block size used while streaming blobs through sha256.  4 MiB hits a
# sweet spot for SSDs and keeps RAM bounded for the few large AFS entries.
HASH_BLOCK = 4 * 1024 * 1024


def _eprint(*a, **k) -> None:
    print(*a, file=sys.stderr, **k)


def _parse_args(argv: list[str]) -> argparse.Namespace:
    p = argparse.ArgumentParser(
        prog="afs_index.py",
        description="Print a stable table of every _DATA.AFS entry.",
    )
    p.add_argument(
        "-i", "--iso",
        type=Path, default=DEFAULT_ISO,
        help=f"path to God Hand ISO (default: {DEFAULT_ISO.name!r} at repo root)",
    )
    p.add_argument(
        "-f", "--fst",
        type=Path, default=DEFAULT_FST,
        help=f"path to GODHAND.FST (default: disc_extract/GODHAND.FST)",
    )
    p.add_argument(
        "--no-hash",
        action="store_true",
        help="skip sha256 (faster; sha256_8 column shows '--------')",
    )
    return p.parse_args(argv)


def _hash_blob(iso, iso_off: int, size: int) -> str:
    """sha256 a contiguous slice of the ISO without materialising it."""
    h = hashlib.sha256()
    iso.seek(iso_off)
    remaining = size
    while remaining > 0:
        chunk = iso.read(min(HASH_BLOCK, remaining))
        if not chunk:
            raise IOError(
                f"ISO truncated at offset {iso_off + size - remaining:#x} "
                f"(expected {size} bytes, got {size - remaining})"
            )
        h.update(chunk)
        remaining -= len(chunk)
    return h.hexdigest()


def main(argv: list[str] | None = None) -> int:
    args = _parse_args(argv if argv is not None else sys.argv[1:])

    if not args.iso.is_file():
        _eprint(f"ERROR: ISO not found: {args.iso}")
        return 1
    if not args.fst.is_file():
        _eprint(
            f"ERROR: FST not found: {args.fst}\n"
            f"       Run ./scripts/extract_iso.sh first."
        )
        return 1

    # 1) FST: full parse, all names indexed by AFS index.
    try:
        fst_bytes = args.fst.read_bytes()
        _hdr, fst_files = afs.parse_fst(fst_bytes)
    except ValueError as e:
        _eprint(f"ERROR: FST parse failed: {e}")
        return 2

    name_by_idx: dict[int, str] = {}
    for f in fst_files:
        # Collisions would mean two FST entries claim the same AFS slot —
        # treat as a fatal format error rather than silently picking one.
        if f.afs_index in name_by_idx and name_by_idx[f.afs_index] != f.path:
            _eprint(
                f"ERROR: FST collision: AFS idx {f.afs_index} claimed by "
                f"{name_by_idx[f.afs_index]!r} and {f.path!r}"
            )
            return 2
        name_by_idx[f.afs_index] = f.path

    # 2) ISO: find _DATA.AFS, read AFS header, sanity-check.
    try:
        with open(args.iso, "rb") as iso:
            try:
                data_afs = afs.find_iso_file(iso, "_DATA.AFS")
            except (FileNotFoundError, ValueError) as e:
                _eprint(f"ERROR: {e}")
                return 2
            iso.seek(data_afs.offset)
            # Read enough for the full entry table: 8 + count*8.  We don't
            # know count yet; speculatively read 16 KiB which covers the
            # observed 11568 B for count=0x5a5.  Re-read if count is bigger.
            head = iso.read(16384)
            try:
                hdr = afs.parse_afs_header(head)
            except ValueError:
                # Try again with a bigger buffer if the AFS is huge.
                need = 8 + 0x100000 * 8  # cap
                iso.seek(data_afs.offset)
                head = iso.read(min(need, data_afs.size))
                try:
                    hdr = afs.parse_afs_header(head)
                except ValueError as e:
                    _eprint(f"ERROR: AFS parse failed: {e}")
                    return 2

            # 3) Print table.  Header line is comment-prefixed for grep-friendliness.
            print(
                "# idx   offset           size      sha256_8  name"
            )
            for i, (rel_off, size) in enumerate(hdr.entries):
                if rel_off == 0 and size == 0:
                    # Spec-compliant "empty / dummy" slot.
                    sha8 = "--------"
                    name = name_by_idx.get(i, "(empty)")
                    print(f"  {i:04x}  {0:#014x}  {0:9d}  {sha8}  {name}")
                    continue
                if args.no_hash:
                    sha8 = "--------"
                else:
                    sha8 = _hash_blob(iso, data_afs.offset + rel_off, size)[:8]
                name = name_by_idx.get(i, "(unnamed)")
                print(
                    f"  {i:04x}  {rel_off:#014x}  {size:9d}  {sha8}  {name}"
                )
    except IOError as e:
        _eprint(f"ERROR: I/O failure on ISO: {e}")
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
