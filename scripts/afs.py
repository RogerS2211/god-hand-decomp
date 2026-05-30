"""Read-only parsers for God Hand's ISO9660 → _DATA.AFS → GODHAND.FST stack.

This module is pure-function and import-only: no top-level I/O, no logging.
``scripts/afs_index.py`` and ``scripts/afs_extract.py`` wrap it with CLIs;
``tests/test_afs.py`` exercises it with synthetic byte fixtures.

Lock-in summary:

ISO9660
-------
PVD lives at 0x8000.  Only the root directory is scanned (we never need
nested ISO directories; the four interesting files are all at root).
Each directory record: ``rec_len, ext_attr_len, lba(LE), lba(BE), size(LE),
size(BE), ...`` etc.  We only need LBA-LE (offset 2) and size-LE (offset 10),
plus name_len at offset 32 and the name itself at offset 33.

AFS
---
Capcom shipped 1445 files in `_DATA.AFS` (CRI standard layout)::

    char     magic[4]   = "AFS\\0"
    uint32   file_count = 0x5a5
    struct { uint32 offset; uint32 size; } entries[file_count]
    /* zero-padded to 0x800 */
    /* file blobs follow, each aligned to 0x800 */

All offsets are relative to the AFS file's first byte (not to the ISO).

FST
---
GODHAND.FST is 32944 bytes, schema-1.0, layout::

    char     magic[4]    = "FST\\0"
    float32  version     = 1.0f          (raw 0x3F800000 LE)
    uint32   strings_off                 (always 0x10)
    uint32   entries_off                 (= end of string table)
    char     strings[entries_off - strings_off]   /* nul-terminated names */
    Entry    entries[]                   /* 12 B each, recursive tree */

Each ``Entry`` is::

    uint8   type                /* 1 = dir, 2 = file, 3 = end-of-dir */
    uint8   flags               /* file-only; observed 0/1/2/3/4/5/6/11/17/...   */
                                /* (109 entries flag=1, 27 flag=4, etc; most 0)  */
    uint16  size_hint           /* file-only: roughly afs_size/16, capped 0xffff.*/
                                /* Does NOT equal floor or ceil(size/16) exactly;*/
                                /* the precise relationship is left for later.  */
    uint32  str_off             /* offset into strings[]; 0 for type=3 */
    uint32  value               /* type=1: child-entry offset (in entries[]) */
                                /* type=2: AFS index (0..file_count-1) */
                                /* type=3: 0 */

The AFS table is the authoritative source of byte offset & size; the FST's
``size_hint`` is captured for recon but never used for extraction.

The first sub-table starts at ``entries[0]`` and terminates at the first
type=3 marker; recursion follows ``value`` offsets for directories.

Recon results (do not relitigate):

- 1240 files declared (vs 1445 AFS entries; ~205 unnamed/empty AFS slots).
- 27 top-level dirs declared, 22 non-empty.
- All 81 ``.rel`` overlays live under ``dll/debugoptimize/`` (note: NOT
  ``dll/Release/`` as the runtime ``cMcb::DllLoad`` format strings imply
  — that's Capcom dev-build vs ship-build dir renaming, not our concern).
"""
from __future__ import annotations

import dataclasses
import fnmatch
import struct
from typing import BinaryIO, Iterable

# --------------------------------------------------------------------------- #
# Constants — pinned so a future format-bump can't silently re-interpret.
# --------------------------------------------------------------------------- #

ISO_BLOCK = 2048
PVD_OFFSET = 0x8000
ISO_PVD_ID = b"CD001"

AFS_MAGIC = b"AFS\0"
AFS_BLOB_ALIGN = 0x800  # CRI pads file blobs to 2 KiB boundaries

FST_MAGIC = b"FST\0"
FST_VERSION_1_0_RAW = 0x3F800000  # IEEE-754 float 1.0 LE
FST_HEADER_SIZE = 16
FST_ENTRY_SIZE = 12
FST_ENTRY_TYPE_DIR = 1
FST_ENTRY_TYPE_FILE = 2
FST_ENTRY_TYPE_END = 3

# Soft cap on FST tree depth to guard against a malformed file causing
# unbounded recursion (real depth is 2-3).
FST_MAX_DEPTH = 16


# --------------------------------------------------------------------------- #
# Dataclasses
# --------------------------------------------------------------------------- #


@dataclasses.dataclass(frozen=True)
class IsoFile:
    """One entry from the ISO9660 root directory."""

    name: str  # as stored in the ISO, e.g. ``_DATA.AFS;1``
    lba: int
    size: int

    @property
    def offset(self) -> int:
        return self.lba * ISO_BLOCK


@dataclasses.dataclass(frozen=True)
class AfsHeader:
    """Parsed AFS header.  ``entries[i] = (offset, size)`` AFS-relative."""

    file_count: int
    entries: tuple  # tuple[tuple[int, int], ...]


@dataclasses.dataclass(frozen=True)
class FstHeader:
    version: float
    strings_off: int
    entries_off: int  # = start of entry table = end of strings


@dataclasses.dataclass(frozen=True)
class FstFile:
    """A file leaf discovered by walking the FST tree."""

    path: str  # slash-joined FST path, e.g. ``dll/debugoptimize/event.rel``
    name: str  # basename only
    afs_index: int
    flags: int  # uint8 from the entry header; meaning TBD
    size_hint: int  # uint16; roughly afs_size/16 but exact relationship TBD


# --------------------------------------------------------------------------- #
# ISO9660
# --------------------------------------------------------------------------- #


def find_iso_root_files(iso: BinaryIO) -> list[IsoFile]:
    """Return every entry in the ISO9660 root directory (no recursion).

    Skips the two self-/parent-dir entries (``\\x00`` / ``\\x01`` names)
    and subdirectories — we only need the four files at root.
    """
    iso.seek(PVD_OFFSET)
    pvd = iso.read(ISO_BLOCK)
    if len(pvd) < ISO_BLOCK or pvd[1:6] != ISO_PVD_ID:
        raise ValueError(
            f"not an ISO9660 PVD at offset {PVD_OFFSET:#x} "
            f"(got magic {pvd[1:6]!r})"
        )
    # PVD root directory record at offset 156, 34 bytes long.
    root_rec = pvd[156 : 156 + 34]
    root_lba = struct.unpack_from("<I", root_rec, 2)[0]
    root_size = struct.unpack_from("<I", root_rec, 10)[0]
    iso.seek(root_lba * ISO_BLOCK)
    root_data = iso.read(root_size)

    out: list[IsoFile] = []
    o = 0
    while o < len(root_data):
        rec_len = root_data[o]
        if rec_len == 0:
            # Padding to next sector inside the directory extent.
            next_sector = ((o // ISO_BLOCK) + 1) * ISO_BLOCK
            if next_sector >= len(root_data):
                break
            o = next_sector
            continue
        rec = root_data[o : o + rec_len]
        lba = struct.unpack_from("<I", rec, 2)[0]
        size = struct.unpack_from("<I", rec, 10)[0]
        flags = rec[25]
        name_len = rec[32]
        name_raw = rec[33 : 33 + name_len]
        is_dir = bool(flags & 0x02)
        # name "\x00"/"\x01" are the self/parent entries in ISO9660.
        if not is_dir and name_raw not in (b"\x00", b"\x01"):
            name = name_raw.decode("latin-1")
            out.append(IsoFile(name=name, lba=lba, size=size))
        o += rec_len
    return out


def find_iso_file(iso: BinaryIO, name: str) -> IsoFile:
    """Find a single file in the ISO root by exact name minus ``;N`` version
    suffix (case-insensitive).  Raises ``FileNotFoundError`` if missing."""
    target = name.upper().split(";", 1)[0]
    for entry in find_iso_root_files(iso):
        bare = entry.name.upper().split(";", 1)[0]
        if bare == target:
            return entry
    raise FileNotFoundError(f"{name!r} not found in ISO root directory")


# --------------------------------------------------------------------------- #
# AFS
# --------------------------------------------------------------------------- #


def parse_afs_header(buf: bytes) -> AfsHeader:
    """Parse an AFS header from ``buf``.  ``buf`` must hold
    ``magic + file_count + file_count*8`` bytes; typically the first ~16 KiB
    of ``_DATA.AFS`` (8 + 1445*8 = 11568 B for our game)."""
    if len(buf) < 8:
        raise ValueError("AFS header too short (need at least 8 bytes)")
    if buf[:4] != AFS_MAGIC:
        raise ValueError(f"AFS magic mismatch: got {buf[:4]!r}, want {AFS_MAGIC!r}")
    file_count = struct.unpack_from("<I", buf, 4)[0]
    if file_count == 0 or file_count > 0x100000:
        raise ValueError(f"AFS file_count out of plausible range: {file_count}")
    need = 8 + file_count * 8
    if len(buf) < need:
        raise ValueError(
            f"AFS header buffer too small for {file_count} entries "
            f"(need {need} bytes, have {len(buf)})"
        )
    entries = tuple(
        struct.unpack_from("<II", buf, 8 + i * 8) for i in range(file_count)
    )
    return AfsHeader(file_count=file_count, entries=entries)


def read_afs_header(afs: BinaryIO) -> AfsHeader:
    """Read the AFS header from an open AFS stream.  Reads only as much as
    the entry table requires.  ``afs`` must be seekable to its start."""
    pos = afs.tell()
    fixed = afs.read(8)
    if len(fixed) < 8 or fixed[:4] != AFS_MAGIC:
        raise ValueError(
            f"AFS magic mismatch at stream offset {pos:#x}: got {fixed[:4]!r}"
        )
    file_count = struct.unpack("<I", fixed[4:8])[0]
    entries_buf = afs.read(file_count * 8)
    return parse_afs_header(fixed + entries_buf)


# --------------------------------------------------------------------------- #
# FST
# --------------------------------------------------------------------------- #


def parse_fst(buf: bytes) -> tuple[FstHeader, list[FstFile]]:
    """Parse a complete GODHAND.FST.  ``buf`` is the whole file as bytes.

    Returns ``(header, files)`` where ``files`` is a flat list of all file
    leaves in tree-walk order (depth-first, sibling order preserved).
    """
    if len(buf) < FST_HEADER_SIZE:
        raise ValueError(
            f"FST too short (need ≥ {FST_HEADER_SIZE} bytes, have {len(buf)})"
        )
    if buf[:4] != FST_MAGIC:
        raise ValueError(f"FST magic mismatch: got {buf[:4]!r}, want {FST_MAGIC!r}")
    version_raw = struct.unpack_from("<I", buf, 4)[0]
    if version_raw != FST_VERSION_1_0_RAW:
        raise ValueError(
            f"FST version mismatch: got {version_raw:#010x}, "
            f"want {FST_VERSION_1_0_RAW:#010x} (1.0f)"
        )
    strings_off = struct.unpack_from("<I", buf, 8)[0]
    entries_off = struct.unpack_from("<I", buf, 12)[0]
    if not (FST_HEADER_SIZE <= strings_off < entries_off <= len(buf)):
        raise ValueError(
            f"FST header bounds invalid: strings_off={strings_off:#x}, "
            f"entries_off={entries_off:#x}, file_size={len(buf):#x}"
        )
    version = struct.unpack("<f", struct.pack("<I", version_raw))[0]
    header = FstHeader(
        version=version, strings_off=strings_off, entries_off=entries_off
    )
    strings_blob = buf[strings_off:entries_off]
    entries_blob = buf[entries_off:]

    def get_str(off: int) -> str:
        if off < 0 or off >= len(strings_blob):
            raise ValueError(f"FST string offset out of range: {off:#x}")
        try:
            end = strings_blob.index(b"\0", off)
        except ValueError as e:
            raise ValueError(
                f"FST string at {off:#x} is not nul-terminated"
            ) from e
        return strings_blob[off:end].decode("ascii")

    files: list[FstFile] = []
    # Detect cycles / repeated walks by remembering visited sub-table offsets.
    # The format does not declare it acyclic; defending here is cheap.
    visited: set[int] = set()

    def walk(sub_off: int, prefix: tuple[str, ...], depth: int) -> None:
        if depth > FST_MAX_DEPTH:
            raise ValueError(
                f"FST tree too deep at {sub_off:#x} (depth={depth} > "
                f"{FST_MAX_DEPTH}); likely malformed"
            )
        if sub_off in visited:
            raise ValueError(f"FST sub-table cycle detected at {sub_off:#x}")
        visited.add(sub_off)
        o = sub_off
        while True:
            if o < 0 or o + FST_ENTRY_SIZE > len(entries_blob):
                raise ValueError(
                    f"FST entry overruns blob at {o:#x} "
                    f"(prefix={'/'.join(prefix)!r})"
                )
            etype, flags, size_hint, str_off, value = struct.unpack_from(
                "<BBHII", entries_blob, o
            )
            if etype == FST_ENTRY_TYPE_END:
                return
            if etype not in (FST_ENTRY_TYPE_DIR, FST_ENTRY_TYPE_FILE):
                raise ValueError(
                    f"unknown FST entry type {etype} at {o:#x} "
                    f"(prefix={'/'.join(prefix)!r})"
                )
            name = get_str(str_off)
            if etype == FST_ENTRY_TYPE_DIR:
                walk(value, prefix + (name,), depth + 1)
            else:  # FST_ENTRY_TYPE_FILE
                path = "/".join(prefix + (name,))
                files.append(
                    FstFile(
                        path=path,
                        name=name,
                        afs_index=value,
                        flags=flags,
                        size_hint=size_hint,
                    )
                )
            o += FST_ENTRY_SIZE

    walk(0, (), 0)
    return header, files


# --------------------------------------------------------------------------- #
# Filtering & manifest helpers
# --------------------------------------------------------------------------- #


def match_filter(path: str, patterns: Iterable[str]) -> bool:
    """fnmatch ``path`` against any of ``patterns``.  Case-insensitive.

    A pattern containing ``/`` is matched against the full FST path; a
    pattern without is matched against the basename only.  If ``patterns``
    is empty, returns True (no filter = pass through).
    """
    pats = list(patterns)
    if not pats:
        return True
    name = path.rsplit("/", 1)[-1]
    p_lower_path = path.lower()
    p_lower_name = name.lower()
    for pat in pats:
        pl = pat.lower()
        if "/" in pat:
            if fnmatch.fnmatchcase(p_lower_path, pl):
                return True
        else:
            if fnmatch.fnmatchcase(p_lower_name, pl):
                return True
    return False


def manifest_entry(name: str, afs_index: int, sha256_hex: str, size: int) -> dict:
    """Return one manifest record.  Order is fixed for diff stability."""
    return {
        "name": name,
        "idx": afs_index,
        "sha256": sha256_hex,
        "size": size,
    }


def manifest_sort_key(entry: dict) -> str:
    """Sort key for ``disc_extract/rel/manifest.json``: by basename, ASCII."""
    return entry["name"]
