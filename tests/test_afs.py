"""Offline unit tests for ``scripts/afs.py``.

Locks in the AFS-header / GODHAND.FST schema we reverse-engineered so a
future schema-discovery agent can't silently shift the parser without
flipping at least one of these tests.

All fixtures are synthetic byte strings — none of these tests touches the
real ISO or FST.  ``tests/test_afs_smoke.py`` covers the integration
sanity-check against the real artefacts under a pytest mark that skips
when those files aren't present.

Test inventory (one ``-k`` slice per behaviour):

    iso9660           — root-dir parser: PVD magic, single-file lookup,
                        case-insensitive ;1-suffix strip, missing-file
                        FileNotFoundError, bad-PVD ValueError.
    afs_header        — magic check, count parse, short-buffer guard,
                        sane-count guard, ``read_afs_header`` stream.
    fst_header        — magic check, version pin (1.0f exact), bounds
                        validation (strings_off / entries_off ordering).
    fst_walk          — single-file root, nested dirs, multiple files,
                        end-of-dir marker, type=2 file extraction with
                        flags + size_hint preserved.
    fst_errors        — bad type byte, string overrun, unterminated
                        string, cycle / over-deep tree.
    filter            — empty list ⇒ pass-through, basename pattern,
                        path pattern, case-insensitive, multiple patterns.
    manifest          — entry shape (key order), sort-by-name stability.
"""
from __future__ import annotations

import io
import struct
import sys
from pathlib import Path

import pytest

# Make ``scripts/`` importable.
REPO_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO_ROOT / "scripts"))
import afs  # noqa: E402


# --------------------------------------------------------------------------- #
# Tiny synthetic-fixture builders
# --------------------------------------------------------------------------- #


def _build_pvd(root_lba: int, root_size: int) -> bytes:
    """Minimal viable ISO9660 PVD payload (2048 B)."""
    pvd = bytearray(2048)
    pvd[1:6] = b"CD001"  # PVD identifier
    # Root directory record (34 bytes) at offset 156.
    rec = bytearray(34)
    rec[0] = 34  # rec_len
    rec[1] = 0  # ext_attr_len
    struct.pack_into("<I", rec, 2, root_lba)  # extent LBA LE
    struct.pack_into(">I", rec, 6, root_lba)  # extent LBA BE
    struct.pack_into("<I", rec, 10, root_size)  # size LE
    struct.pack_into(">I", rec, 14, root_size)  # size BE
    rec[25] = 0x02  # directory flag
    rec[32] = 1
    rec[33] = 0x00  # root self-name
    pvd[156:156 + 34] = rec
    return bytes(pvd)


def _build_dir_rec(name: bytes, lba: int, size: int, is_dir: bool) -> bytes:
    name_len = len(name)
    rec_len = 33 + name_len
    if rec_len % 2:
        rec_len += 1  # pad to even
    rec = bytearray(rec_len)
    rec[0] = rec_len
    struct.pack_into("<I", rec, 2, lba)
    struct.pack_into("<I", rec, 10, size)
    rec[25] = 0x02 if is_dir else 0x00
    rec[32] = name_len
    rec[33:33 + name_len] = name
    return bytes(rec)


def _build_iso(files: list[tuple[bytes, int, int]]) -> bytes:
    """Build a minimal ISO image (in-memory) with one root dir containing
    ``files`` (each ``(name, lba, size)``).  Padded with zeros to cover
    the root-dir extent."""
    root_lba = 0x14  # arbitrary, > 0x10 (PVD)
    pvd = _build_pvd(root_lba, 2048)

    # Build root dir: . / .. / files...
    blob = bytearray()
    blob += _build_dir_rec(b"\x00", root_lba, 2048, True)
    blob += _build_dir_rec(b"\x01", root_lba, 2048, True)
    for name, lba, size in files:
        blob += _build_dir_rec(name, lba, size, False)
    # pad root extent to 2048
    blob += b"\x00" * (2048 - len(blob))

    # Image must be large enough to hold the root-dir extent at root_lba.
    img = bytearray((root_lba + 1) * 2048)
    img[0x8000:0x8000 + 2048] = pvd
    img[root_lba * 2048:root_lba * 2048 + 2048] = blob
    return bytes(img)


def _build_afs(entries: list[tuple[int, int]]) -> bytes:
    """Build a synthetic AFS header (just the table; no body needed for
    parser tests)."""
    buf = bytearray()
    buf += b"AFS\0"
    buf += struct.pack("<I", len(entries))
    for off, sz in entries:
        buf += struct.pack("<II", off, sz)
    return bytes(buf)


def _build_fst(
    strings: list[bytes],
    entries_layout: list[tuple],
) -> bytes:
    """Build a FST from ``strings`` (list of name bytes) and an entry
    layout.  Each entry tuple is one of:
        ('dir',  name_bytes, child_sub_off)
        ('file', name_bytes, flags, size_hint, afs_index)
        ('end',)

    ``child_sub_off`` is the entry-blob-relative offset of the child
    sub-table; the caller is responsible for picking values that match
    the layout it builds.
    """
    # String table: 4-byte alignment-free nul-terminated.
    strings_off = afs.FST_HEADER_SIZE
    s_blob = bytearray()
    s_map: dict[bytes, int] = {}
    for s in strings:
        if s not in s_map:
            s_map[s] = len(s_blob)
            s_blob += s + b"\0"
    entries_off = strings_off + len(s_blob)

    e_blob = bytearray()
    for e in entries_layout:
        if e[0] == "dir":
            _, name, sub_off = e
            e_blob += struct.pack(
                "<BBHII",
                afs.FST_ENTRY_TYPE_DIR, 0, 0, s_map[name], sub_off,
            )
        elif e[0] == "file":
            _, name, flags, size_hint, afs_idx = e
            e_blob += struct.pack(
                "<BBHII",
                afs.FST_ENTRY_TYPE_FILE, flags, size_hint, s_map[name], afs_idx,
            )
        elif e[0] == "end":
            e_blob += struct.pack("<BBHII", afs.FST_ENTRY_TYPE_END, 0, 0, 0, 0)
        else:
            raise AssertionError(f"unknown synthetic entry kind {e[0]!r}")

    header = struct.pack(
        "<4sIII",
        b"FST\0",
        afs.FST_VERSION_1_0_RAW,
        strings_off,
        entries_off,
    )
    return header + bytes(s_blob) + bytes(e_blob)


# --------------------------------------------------------------------------- #
# ISO9660
# --------------------------------------------------------------------------- #


class TestIso9660:
    def test_iso9660_finds_named_file(self):
        img = _build_iso([(b"_DATA.AFS;1", 0x919, 1_541_885_952)])
        iso = io.BytesIO(img)
        found = afs.find_iso_file(iso, "_DATA.AFS")
        assert found.lba == 0x919
        assert found.offset == 0x919 * 2048
        assert found.size == 1_541_885_952

    def test_iso9660_strips_version_suffix(self):
        img = _build_iso([(b"GODHAND.FST;1", 10, 32944)])
        iso = io.BytesIO(img)
        found = afs.find_iso_file(iso, "GODHAND.FST")
        assert found.name == "GODHAND.FST;1"

    def test_iso9660_is_case_insensitive(self):
        img = _build_iso([(b"_DATA.AFS;1", 0x919, 100)])
        iso = io.BytesIO(img)
        found = afs.find_iso_file(iso, "_data.afs")
        assert found.lba == 0x919

    def test_iso9660_missing_file_raises(self):
        img = _build_iso([(b"SLUS_215.03;1", 277, 3_607_008)])
        iso = io.BytesIO(img)
        with pytest.raises(FileNotFoundError):
            afs.find_iso_file(iso, "_DATA.AFS")

    def test_iso9660_bad_pvd_magic(self):
        img = bytearray(_build_iso([(b"A;1", 0x14, 1)]))
        img[0x8001:0x8006] = b"XXXXX"  # corrupt CD001
        iso = io.BytesIO(bytes(img))
        with pytest.raises(ValueError, match="ISO9660"):
            afs.find_iso_file(iso, "A")

    def test_iso9660_lists_all_root_files(self):
        img = _build_iso([
            (b"A;1", 100, 10),
            (b"B;1", 200, 20),
            (b"C;1", 300, 30),
        ])
        iso = io.BytesIO(img)
        found = afs.find_iso_root_files(iso)
        names = [f.name for f in found]
        assert "A;1" in names and "B;1" in names and "C;1" in names
        # Self/parent dirs (names \x00 / \x01) are not files
        assert all(not n.startswith("\x00") for n in names)


# --------------------------------------------------------------------------- #
# AFS header
# --------------------------------------------------------------------------- #


class TestAfsHeader:
    def test_afs_parses_minimal(self):
        buf = _build_afs([(0x800, 100), (0x1000, 200)])
        hdr = afs.parse_afs_header(buf)
        assert hdr.file_count == 2
        assert hdr.entries == ((0x800, 100), (0x1000, 200))

    def test_afs_magic_mismatch(self):
        buf = _build_afs([(0x800, 100)])
        bad = b"XYZ\0" + buf[4:]
        with pytest.raises(ValueError, match="magic mismatch"):
            afs.parse_afs_header(bad)

    def test_afs_short_buffer_rejected(self):
        with pytest.raises(ValueError, match="header too short"):
            afs.parse_afs_header(b"AFS")

    def test_afs_truncated_entry_table(self):
        # Claims 10 entries but only provides 2 entries' worth of bytes.
        bad = b"AFS\0" + struct.pack("<I", 10) + struct.pack("<II", 0, 0) * 2
        with pytest.raises(ValueError, match="too small"):
            afs.parse_afs_header(bad)

    def test_afs_zero_count_rejected(self):
        bad = b"AFS\0" + struct.pack("<I", 0)
        with pytest.raises(ValueError, match="out of plausible range"):
            afs.parse_afs_header(bad)

    def test_afs_implausible_count_rejected(self):
        bad = b"AFS\0" + struct.pack("<I", 0xFFFFFFFF)
        with pytest.raises(ValueError, match="out of plausible range"):
            afs.parse_afs_header(bad)

    def test_read_afs_header_from_stream(self):
        buf = _build_afs([(0x800, 16), (0x1000, 32), (0x1800, 64)])
        # Pad to simulate a real AFS that continues with payload bytes.
        stream = io.BytesIO(buf + b"\xab" * 2048)
        hdr = afs.read_afs_header(stream)
        assert hdr.file_count == 3
        assert hdr.entries[2] == (0x1800, 64)


# --------------------------------------------------------------------------- #
# FST header
# --------------------------------------------------------------------------- #


class TestFstHeader:
    def test_fst_magic_mismatch(self):
        bad = b"XST\0" + struct.pack("<III", afs.FST_VERSION_1_0_RAW, 0x10, 0x20)
        bad += b"\0" * 32
        with pytest.raises(ValueError, match="magic mismatch"):
            afs.parse_fst(bad)

    def test_fst_version_pin(self):
        # version 2.0f instead of 1.0f
        v2 = struct.unpack("<I", struct.pack("<f", 2.0))[0]
        bad = b"FST\0" + struct.pack("<III", v2, 0x10, 0x20)
        bad += b"\0" * 32
        with pytest.raises(ValueError, match="version mismatch"):
            afs.parse_fst(bad)

    def test_fst_too_short(self):
        with pytest.raises(ValueError, match="too short"):
            afs.parse_fst(b"FST\0")

    def test_fst_bounds_invalid_strings_after_entries(self):
        # strings_off > entries_off is nonsensical
        bad = b"FST\0" + struct.pack(
            "<III", afs.FST_VERSION_1_0_RAW, 0x40, 0x20
        ) + b"\0" * 0x80
        with pytest.raises(ValueError, match="bounds invalid"):
            afs.parse_fst(bad)

    def test_fst_bounds_invalid_entries_past_file_end(self):
        bad = b"FST\0" + struct.pack(
            "<III", afs.FST_VERSION_1_0_RAW, 0x10, 0x100
        ) + b"\0" * 8  # entries_off=0x100 but file size = 0x18
        with pytest.raises(ValueError, match="bounds invalid"):
            afs.parse_fst(bad)


# --------------------------------------------------------------------------- #
# FST tree walk
# --------------------------------------------------------------------------- #


class TestFstWalk:
    def test_fst_single_file_at_root(self):
        # Layout: one file at sub_off=0, then end marker at sub_off=12.
        # entries_blob offsets: 0=file, 12=end
        fst = _build_fst(
            strings=[b"event.rel"],
            entries_layout=[
                ("file", b"event.rel", 0, 5028, 706),
                ("end",),
            ],
        )
        hdr, files = afs.parse_fst(fst)
        assert hdr.version == 1.0
        assert len(files) == 1
        f = files[0]
        assert f.path == "event.rel"
        assert f.name == "event.rel"
        assert f.afs_index == 706
        assert f.flags == 0
        assert f.size_hint == 5028

    def test_fst_nested_directory(self):
        # Top-level (sub_off=0): one dir 'dll' -> child sub_off=24; then end.
        # Child sub-table at offset 24 (= 12 (dir entry) + 12 (end marker)):
        #   one file 'event.rel', then end.
        fst = _build_fst(
            strings=[b"dll", b"event.rel"],
            entries_layout=[
                ("dir", b"dll", 24),
                ("end",),
                ("file", b"event.rel", 1, 5028, 706),
                ("end",),
            ],
        )
        hdr, files = afs.parse_fst(fst)
        assert [f.path for f in files] == ["dll/event.rel"]
        assert files[0].flags == 1

    def test_fst_multiple_files_preserve_order(self):
        fst = _build_fst(
            strings=[b"a", b"b", b"c"],
            entries_layout=[
                ("file", b"a", 0, 1, 10),
                ("file", b"b", 0, 2, 20),
                ("file", b"c", 0, 3, 30),
                ("end",),
            ],
        )
        _, files = afs.parse_fst(fst)
        assert [f.name for f in files] == ["a", "b", "c"]
        assert [f.afs_index for f in files] == [10, 20, 30]

    def test_fst_two_level_tree(self):
        # Layout:
        #   sub_off=0  : dir 'dll' -> sub_off=36
        #   sub_off=12 : dir 'bgm' -> sub_off=72
        #   sub_off=24 : end
        #   sub_off=36 : file 'event.rel' (afs=706)
        #   sub_off=48 : file 'mcport.rel' (afs=779)
        #   sub_off=60 : end
        #   sub_off=72 : file 'bgm00.afd' (afs=65)
        #   sub_off=84 : end
        fst = _build_fst(
            strings=[b"dll", b"bgm", b"event.rel", b"mcport.rel", b"bgm00.afd"],
            entries_layout=[
                ("dir", b"dll", 36),
                ("dir", b"bgm", 72),
                ("end",),
                ("file", b"event.rel", 0, 5028, 706),
                ("file", b"mcport.rel", 0, 7152, 779),
                ("end",),
                ("file", b"bgm00.afd", 0, 116, 65),
                ("end",),
            ],
        )
        _, files = afs.parse_fst(fst)
        paths = [f.path for f in files]
        assert paths == ["dll/event.rel", "dll/mcport.rel", "bgm/bgm00.afd"]


# --------------------------------------------------------------------------- #
# FST error paths
# --------------------------------------------------------------------------- #


class TestFstErrors:
    def test_fst_unknown_entry_type(self):
        # Inject type=7 manually.
        strings = b"x\0"
        e_blob = struct.pack("<BBHII", 7, 0, 0, 0, 0)
        fst = struct.pack(
            "<4sIII", b"FST\0", afs.FST_VERSION_1_0_RAW, 16, 16 + len(strings)
        ) + strings + e_blob
        with pytest.raises(ValueError, match="unknown FST entry type"):
            afs.parse_fst(fst)

    def test_fst_string_offset_out_of_range(self):
        strings = b"a\0"
        e_blob = struct.pack(
            "<BBHII", afs.FST_ENTRY_TYPE_FILE, 0, 0, 0xFF, 0
        ) + struct.pack("<BBHII", afs.FST_ENTRY_TYPE_END, 0, 0, 0, 0)
        fst = struct.pack(
            "<4sIII", b"FST\0", afs.FST_VERSION_1_0_RAW, 16, 16 + len(strings)
        ) + strings + e_blob
        with pytest.raises(ValueError, match="string offset out of range"):
            afs.parse_fst(fst)

    def test_fst_entry_overruns_blob(self):
        # No end marker; walk runs off the end of the entry blob.
        strings = b"a\0"
        e_blob = struct.pack(
            "<BBHII", afs.FST_ENTRY_TYPE_FILE, 0, 0, 0, 1
        )  # only one entry, no end
        fst = struct.pack(
            "<4sIII", b"FST\0", afs.FST_VERSION_1_0_RAW, 16, 16 + len(strings)
        ) + strings + e_blob
        with pytest.raises(ValueError, match="entry overruns"):
            afs.parse_fst(fst)

    def test_fst_cycle_detected(self):
        # Two dirs whose `value` points back to sub_off=0 → cycle on the
        # second traversal of offset 0.
        fst = _build_fst(
            strings=[b"a", b"b"],
            entries_layout=[
                ("dir", b"a", 36),
                ("dir", b"b", 0),  # value=0 points back to the start
                ("end",),
                ("file", b"a", 0, 0, 0),
                ("end",),
            ],
        )
        with pytest.raises(ValueError, match="cycle"):
            afs.parse_fst(fst)


# --------------------------------------------------------------------------- #
# Filter matching
# --------------------------------------------------------------------------- #


class TestFilter:
    def test_empty_patterns_pass(self):
        assert afs.match_filter("anything/at/all.bin", [])

    def test_basename_glob_matches(self):
        assert afs.match_filter("dll/debugoptimize/event.rel", ["*.rel"])
        assert afs.match_filter("dll/debugoptimize/r000.rel", ["r*.rel"])
        assert not afs.match_filter("dll/debugoptimize/event.rel", ["*.dat"])

    def test_path_glob_matches(self):
        assert afs.match_filter(
            "dll/debugoptimize/event.rel", ["dll/*/*.rel"]
        )
        assert not afs.match_filter(
            "bgm/event.rel", ["dll/*/*.rel"]
        )

    def test_pattern_is_case_insensitive(self):
        assert afs.match_filter("Dll/Debug/Event.REL", ["*.rel"])
        assert afs.match_filter("Dll/Debug/Event.REL", ["*EVENT*"])

    def test_multiple_patterns_or(self):
        assert afs.match_filter(
            "bgm/bgm00.afd", ["*.rel", "*.afd"]
        )
        assert not afs.match_filter(
            "bgm/bgm00.afs", ["*.rel", "*.afd"]
        )


# --------------------------------------------------------------------------- #
# Manifest emission
# --------------------------------------------------------------------------- #


class TestManifest:
    def test_manifest_entry_shape(self):
        e = afs.manifest_entry("event.rel", 706, "deadbeef" * 8, 80431)
        assert list(e.keys()) == ["name", "idx", "sha256", "size"]
        assert e["name"] == "event.rel"
        assert e["idx"] == 706
        assert len(e["sha256"]) == 64
        assert e["size"] == 80431

    def test_manifest_sort_is_alpha_by_name(self):
        entries = [
            afs.manifest_entry("r100.rel", 1000, "00" * 32, 1),
            afs.manifest_entry("event.rel", 706, "11" * 32, 2),
            afs.manifest_entry("r000.rel", 1072, "22" * 32, 3),
            afs.manifest_entry("mcport.rel", 779, "33" * 32, 4),
        ]
        entries.sort(key=afs.manifest_sort_key)
        assert [e["name"] for e in entries] == [
            "event.rel", "mcport.rel", "r000.rel", "r100.rel",
        ]
