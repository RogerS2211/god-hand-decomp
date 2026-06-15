#!/usr/bin/env python3
"""afs_extract.py — extract a filtered subset of ``_DATA.AFS`` to disk.

Reads:
  * ``God Hand (USA).iso``     for the ``_DATA.AFS`` blob.
  * ``disc_extract/GODHAND.FST`` for human-readable names.

Writes:
  * ``<out>/<basename>`` per matched FST file (e.g. ``event.rel``, ``r000.rel``).
  * ``<out>/manifest.json``: sorted-by-name list of
    ``{name, idx, sha256, size}`` for every extracted blob.

Usage::

    python scripts/afs_extract.py [-i path/to/God\\ Hand\\ (USA).iso]
                                  [-f path/to/GODHAND.FST]
                                  [-o disc_extract/rel]
                                  [--filter '*.rel'] [--filter PAT ...]

If no ``--filter`` is given, ``*.rel`` is implied (the default; see
``DECISIONS.md``).  Pass ``--filter '*'`` to extract
everything (NOT recommended; ``_DATA.AFS`` is 1.5 GB).

Idempotent: re-running yields byte-identical outputs and an unchanged
manifest.  Each file is hashed during extraction and the manifest's
``sha256`` is the canonical record; no separate verify pass is needed.

Exit codes:
  0   success
  1   user / I/O error (missing ISO/FST, no write permission, etc.)
  2   format error    (AFS magic mismatch, FST schema mismatch, etc.)
  3   filter matched zero files (likely a typo in the pattern)

Sibling tool: ``scripts/afs_index.py``.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import sys
from pathlib import Path

# Make ``scripts/`` importable when run as ``python scripts/...``.
sys.path.insert(0, str(Path(__file__).resolve().parent))
import afs  # noqa: E402

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_ISO = REPO_ROOT / "God Hand (USA).iso"
DEFAULT_FST = REPO_ROOT / "disc_extract" / "GODHAND.FST"
DEFAULT_OUT = REPO_ROOT / "disc_extract" / "rel"
DEFAULT_FILTERS = ["*.rel"]

# Stream blocks; same rationale as afs_index.py.
COPY_BLOCK = 4 * 1024 * 1024


def _eprint(*a, **k) -> None:
    print(*a, file=sys.stderr, **k)


def _parse_args(argv: list[str]) -> argparse.Namespace:
    p = argparse.ArgumentParser(
        prog="afs_extract.py",
        description="Extract a filtered subset of _DATA.AFS to disk.",
    )
    p.add_argument("-i", "--iso", type=Path, default=DEFAULT_ISO)
    p.add_argument("-f", "--fst", type=Path, default=DEFAULT_FST)
    p.add_argument("-o", "--out", type=Path, default=DEFAULT_OUT)
    p.add_argument(
        "--filter",
        action="append",
        dest="filters",
        default=None,
        metavar="PATTERN",
        help=(
            "fnmatch pattern against the FST basename (no '/') or full path "
            "(contains '/'); case-insensitive. May be passed multiple times. "
            f"Defaults to {DEFAULT_FILTERS!r} (the .rel-only policy)."
        ),
    )
    p.add_argument(
        "--manifest-name",
        default="manifest.json",
        help="manifest filename inside --out (default: manifest.json)",
    )
    return p.parse_args(argv)


def _copy_and_hash(iso, iso_off: int, size: int, dest: Path) -> str:
    """Copy ``size`` bytes from ``iso`` at ``iso_off`` into ``dest`` while
    streaming sha256.  Returns hex digest.  Uses a tmp-then-rename so a
    crashed extraction never leaves a half-written .rel on disk."""
    iso.seek(iso_off)
    h = hashlib.sha256()
    tmp = dest.with_suffix(dest.suffix + ".tmp")
    remaining = size
    try:
        with open(tmp, "wb") as out:
            while remaining > 0:
                chunk = iso.read(min(COPY_BLOCK, remaining))
                if not chunk:
                    raise IOError(
                        f"ISO truncated while extracting {dest.name} "
                        f"at offset {iso_off + size - remaining:#x}"
                    )
                h.update(chunk)
                out.write(chunk)
                remaining -= len(chunk)
        os.replace(tmp, dest)
    except BaseException:
        try:
            tmp.unlink()
        except OSError:
            pass
        raise
    return h.hexdigest()


def main(argv: list[str] | None = None) -> int:
    args = _parse_args(argv if argv is not None else sys.argv[1:])
    filters = args.filters if args.filters else list(DEFAULT_FILTERS)

    if not args.iso.is_file():
        _eprint(f"ERROR: ISO not found: {args.iso}")
        return 1
    if not args.fst.is_file():
        _eprint(
            f"ERROR: FST not found: {args.fst}\n"
            f"       Run ./scripts/extract_iso.sh first."
        )
        return 1

    args.out.mkdir(parents=True, exist_ok=True)

    # Parse FST.
    try:
        _hdr, fst_files = afs.parse_fst(args.fst.read_bytes())
    except ValueError as e:
        _eprint(f"ERROR: FST parse failed: {e}")
        return 2

    matched = [f for f in fst_files if afs.match_filter(f.path, filters)]
    if not matched:
        _eprint(f"ERROR: filter {filters!r} matched 0 of {len(fst_files)} FST files")
        return 3

    # Guard against basename collisions in the matched set.  Different
    # FST paths with the same basename would clobber each other in the
    # flat extraction layout.  Prior analysis verified zero collisions for *.rel;
    # this check makes the assumption explicit for future filter changes.
    seen_bn: dict[str, str] = {}
    for f in matched:
        if f.name in seen_bn and seen_bn[f.name] != f.path:
            _eprint(
                f"ERROR: basename collision: {seen_bn[f.name]!r} and "
                f"{f.path!r} both map to {f.name!r}.\n"
                f"       Extracting both to a flat dir would clobber. "
                f"Refine --filter, or pre-create subdirs."
            )
            return 1
        seen_bn[f.name] = f.path

    print(
        f"[afs_extract] {len(matched)} of {len(fst_files)} FST files match "
        f"{filters!r}; extracting to {args.out}"
    )

    manifest: list[dict] = []
    with open(args.iso, "rb") as iso:
        try:
            data_afs = afs.find_iso_file(iso, "_DATA.AFS")
        except (FileNotFoundError, ValueError) as e:
            _eprint(f"ERROR: {e}")
            return 2
        iso.seek(data_afs.offset)
        head = iso.read(16384)
        try:
            afs_hdr = afs.parse_afs_header(head)
        except ValueError as e:
            _eprint(f"ERROR: AFS parse failed: {e}")
            return 2

        for f in matched:
            if not (0 <= f.afs_index < afs_hdr.file_count):
                _eprint(
                    f"ERROR: {f.path} cites AFS idx {f.afs_index} "
                    f"out of range [0, {afs_hdr.file_count})"
                )
                return 2
            rel_off, size = afs_hdr.entries[f.afs_index]
            if rel_off == 0 and size == 0:
                _eprint(
                    f"WARNING: {f.path}: AFS slot {f.afs_index} is empty; skipping"
                )
                continue
            dest = args.out / f.name
            sha256 = _copy_and_hash(
                iso, data_afs.offset + rel_off, size, dest
            )
            manifest.append(
                afs.manifest_entry(
                    name=f.name, afs_index=f.afs_index,
                    sha256_hex=sha256, size=size,
                )
            )

    manifest.sort(key=afs.manifest_sort_key)
    mpath = args.out / args.manifest_name
    # Write deterministically: indent=2, sorted keys per record (manifest_entry
    # already pins the order), trailing newline.
    mpath.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")

    total_bytes = sum(m["size"] for m in manifest)
    print(
        f"[afs_extract] {len(manifest)} files / {total_bytes} bytes "
        f"-> {args.out}/  +  {mpath.name}"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
