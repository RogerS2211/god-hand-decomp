#!/usr/bin/env python3
"""scripts/elf_postprocess.py — post-link ELF synthesis for byte-identical match.

GNU ld can produce the LOAD segment *content* byte-identically to retail
but cannot replicate retail's exact ELF wrapper:

1. **Loaded section sh_size** for ``.text`` / ``.data`` / ``.sndata`` /
   ``.rodata`` / ``.sbss`` / ``.bss`` includes the trailing inter-section
   padding that splat allocates to each subsegment (24 nops at the end of
   ``.text``, all-zero filler for the others).  Retail's section headers
   exclude that padding so sh_addr+sh_size leaves a small gap to the next
   sh_addr.  ld inherits sh_size from input sections and has no scriptable
   way to declare a smaller sh_size while keeping the trailing bytes in
   the file — this script patches them.

2. **``.text`` sh_flags** in retail are ``WAX`` (the overlay loader patches
   over ``.text`` at runtime).  Even when we mark ``.text`` in the ``.o``
   as ``WAX`` via ``objcopy --set-section-flags`` (see compile.py), ld
   strips the ``W`` bit on output sections it deems "code".  This script
   forces it back on.

3. **43 non-loaded sections** (.reginfo + 39 × .DVP.overlay + .mdebug.eabi64
   + .DVP.ovlytab + .DVP.ovlystrtab) live outside the LOAD segment in the
   retail ELF.  Their payloads were extracted to the per-version metadata
   dir by ``scripts/extract_elf_metadata.py`` and are spliced back in here
   at retail file offsets.

4. **Section header table + .shstrtab** appear after the non-loaded
   payloads.  Retail's SHT lists 52 sections in a specific order; the
   .shstrtab keeps leading ``\\0.symtab\\0.strtab\\0.shstrtab\\0`` strings
   that survive the original strip pass.  We rebuild both from the
   manifest and the saved retail bytes.

End result: ``build/<basename>.elf`` becomes byte-identical to
``disc_extract/<basename>``.

**Version-agnostic.** Every "retail invariant" (PT_LOAD program header,
loaded-section sh_size/sh_flags, where the LOAD content ends) is read from
the per-version ``manifest.json`` (``manifest["retail"]``, produced by
``extract_elf_metadata.py``) rather than hardcoded.  Point this at a
version's metadata dir with ``--metadata-dir`` (compile.py passes the
per-version dir; default is the US-flat ``bin/elf_metadata``).
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_METADATA_DIR = ROOT / "bin" / "elf_metadata"

# --------------------------------------------------------------------------- #
# Legacy US fallback
# --------------------------------------------------------------------------- #
# These reproduce the original US-hardcoded constants and are used ONLY when a
# manifest predates the ``retail`` block (a stale US ``bin/elf_metadata``).
# Every freshly extracted manifest carries ``manifest["retail"]`` and these are
# never consulted.  Kept so a stale US clone still byte-matches.
_LEGACY_US_LOADED_SECTION_PATCHES = {
    ".text":              {"sh_size": 0x2BBF20, "sh_flags": 0x00000007},  # WAX
    ".data":              {"sh_size": 0x4E460,  "sh_flags": 0x00000007},  # WAX
    ".sndata":            {"sh_size": 0x11170,  "sh_flags": 0x00000003},  # WA
    ".rodata":            {"sh_size": 0x45620,  "sh_flags": 0x00000002},  # A
    ".gcc_except_table":  {"sh_size": 0x000E4,  "sh_flags": 0x00000003},  # WA
    ".sbss":              {"sh_size": 0x000C0,  "sh_flags": 0x10000003},  # WAp
    ".bss":               {"sh_size": 0x3259B4, "sh_flags": 0x00000003},  # WA
}
_LEGACY_US_RETAIL_LOAD = {
    "p_type":    1,
    "p_offset":  0x001000,
    "p_vaddr":   0x00100000,
    "p_paddr":   0x00100000,
    "p_filesz":  0x360CE4,
    "p_memsz":   0x6867B4,
    "p_flags":   0x7,        # RWE
    "p_align":   0x1000,
}

# Format constants.
EHDR_OFF_PHOFF      = 0x1C
EHDR_OFF_SHOFF      = 0x20
EHDR_OFF_PHENTSIZE  = 0x2A
EHDR_OFF_PHNUM      = 0x2C
EHDR_OFF_SHENTSIZE  = 0x2E
EHDR_OFF_SHNUM      = 0x30
EHDR_OFF_SHSTRNDX   = 0x32

# Retail e_ident[7..16] is all zero (ei_osabi=0, ei_abiversion=0,
# EI_PAD[7]=0).  Cross-binutils reproducibility note: binutils 2.44 (and
# possibly other versions) sets EI_ABIVERSION=5 in the MIPS BFD backend
# (originally added for PT_GNU_STACK in 2016, reverted in glibc-land but
# the slot stays "taken" in some series).  binutils 2.45 leaves it 0.
# Retail SLUS_215.03 has it 0.  Stamping bytes 7..16 to all-zero makes
# the build retail-byte-identical on every binutils version we've
# tested (2.40, 2.44, 2.45).
EHDR_OFF_EIDENT_NORM = 7
EHDR_LEN_EIDENT_NORM = 16 - 7

SHENT_FMT  = "<10I"
SHENT_SIZE = 40
PHENT_FMT  = "<8I"
PHENT_SIZE = 32

PHDR_FIELDS = (
    "p_type", "p_offset", "p_vaddr", "p_paddr",
    "p_filesz", "p_memsz", "p_flags", "p_align",
)


# --------------------------------------------------------------------------- #
# Retail-invariant resolution
# --------------------------------------------------------------------------- #
def _load_retail_invariants(manifest: dict, *, verbose: bool) -> tuple[dict, dict, int]:
    """Return (loaded_section_patches, retail_load, load_file_end).

    Prefer the manifest's ``retail`` block (version-agnostic, produced by
    extract_elf_metadata.py).  Fall back to the legacy US constants only when
    the block is absent (a stale US manifest), so an un-refreshed US clone
    still byte-matches.
    """
    retail = manifest.get("retail")
    if retail:
        patches = {
            name: {"sh_size": spec["sh_size"], "sh_flags": spec["sh_flags"]}
            for name, spec in retail["loaded_sections"].items()
        }
        load = {k: int(retail["pt_load"][k]) for k in PHDR_FIELDS}
        load_file_end = int(retail["load_file_end"])
        return patches, load, load_file_end

    if verbose:
        print("  (manifest has no 'retail' block — using legacy US fallback; "
              "re-run scripts/extract_elf_metadata.py to refresh)")
    load = dict(_LEGACY_US_RETAIL_LOAD)
    return (
        dict(_LEGACY_US_LOADED_SECTION_PATCHES),
        load,
        load["p_offset"] + load["p_filesz"],
    )


# --------------------------------------------------------------------------- #
# Helpers
# --------------------------------------------------------------------------- #
def _normalize_eident(data: bytearray, verbose: bool) -> dict:
    """Stamp ``e_ident[7..16]`` to all-zero to match retail.

    This is a cross-binutils-version normalization: see the comment on
    ``EHDR_OFF_EIDENT_NORM`` above.  No-op on binutils 2.45 (the
    fingerprint baseline); rewrites byte 8 from 5 to 0 on binutils 2.44
    (Debian trixie) and on any other version where the MIPS BFD backend
    still allocates EI_ABIVERSION=5 for PT_GNU_STACK-style outputs.
    Returns a dict of any changed bytes for the post-process report.
    """
    start = EHDR_OFF_EIDENT_NORM
    end   = start + EHDR_LEN_EIDENT_NORM
    before = bytes(data[start:end])
    target = b"\x00" * EHDR_LEN_EIDENT_NORM
    if before == target:
        return {}
    changed: dict[str, tuple[int, int]] = {}
    for i, (b, t) in enumerate(zip(before, target)):
        if b != t:
            changed[f"e_ident[{start + i}]"] = (b, t)
    data[start:end] = target
    if verbose:
        for k, (old, new) in changed.items():
            print(f"  ehdr e_ident {k}: 0x{old:02x} -> 0x{new:02x}")
    return changed


def _patch_loaded_sht(data: bytearray, patches: dict, verbose: bool) -> dict:
    """Stage 1: patch loaded section sh_size + sh_flags in place.

    Operates on the SHT that ld left behind.  The final output SHT is the
    retail ``sht.bin`` spliced in by Stage 3, so this stage is diagnostic /
    defence-in-depth (its bytes are dropped with ld's tail); it keeps the
    returned report meaningful.
    """
    sh_off       = struct.unpack_from("<I", data, EHDR_OFF_SHOFF)[0]
    sh_entsize   = struct.unpack_from("<H", data, EHDR_OFF_SHENTSIZE)[0]
    sh_num       = struct.unpack_from("<H", data, EHDR_OFF_SHNUM)[0]
    shstrndx     = struct.unpack_from("<H", data, EHDR_OFF_SHSTRNDX)[0]
    if sh_entsize != SHENT_SIZE:
        raise ValueError(f"unexpected sh_entsize {sh_entsize}, want {SHENT_SIZE}")

    # Read the ld-produced shstrtab to map section indices to names.
    base_ss = sh_off + shstrndx * SHENT_SIZE
    _, _, _, _, ss_off, ss_size, *_ = struct.unpack_from(SHENT_FMT, data, base_ss)
    strtab = bytes(data[ss_off:ss_off + ss_size])

    diffs: dict[str, list[tuple[str, int, int]]] = {}
    for i in range(sh_num):
        base = sh_off + i * SHENT_SIZE
        ent  = struct.unpack_from(SHENT_FMT, data, base)
        name_off = ent[0]
        name_end = strtab.index(b"\x00", name_off)
        name     = strtab[name_off:name_end].decode("ascii", errors="replace")
        spec     = patches.get(name)
        if spec is None:
            continue
        if ent[5] != spec["sh_size"]:
            diffs.setdefault(name, []).append(("sh_size", ent[5], spec["sh_size"]))
            struct.pack_into("<I", data, base + 5 * 4, spec["sh_size"])
        if ent[2] != spec["sh_flags"]:
            diffs.setdefault(name, []).append(("sh_flags", ent[2], spec["sh_flags"]))
            struct.pack_into("<I", data, base + 2 * 4, spec["sh_flags"])

    if verbose:
        for name, fields in diffs.items():
            for field, old, new in fields:
                print(f"  loaded sht  {name:20s} {field}: 0x{old:x} -> 0x{new:x}")
    return diffs


def _patch_phdr(data: bytearray, retail_load: dict, verbose: bool) -> dict:
    """Stage 2: patch PT_LOAD program header to retail values."""
    ph_off     = struct.unpack_from("<I", data, EHDR_OFF_PHOFF)[0]
    ph_entsize = struct.unpack_from("<H", data, EHDR_OFF_PHENTSIZE)[0]
    ph_num     = struct.unpack_from("<H", data, EHDR_OFF_PHNUM)[0]
    if ph_entsize != PHENT_SIZE:
        raise ValueError(f"unexpected ph_entsize {ph_entsize}, want {PHENT_SIZE}")

    diffs: list[tuple[str, int, int]] = []
    for pi in range(ph_num):
        base = ph_off + pi * PHENT_SIZE
        ent  = struct.unpack_from(PHENT_FMT, data, base)
        if ent[0] != 1:        # only patch PT_LOAD
            continue
        for fi, key in enumerate(PHDR_FIELDS):
            want = retail_load[key]
            if ent[fi] != want:
                diffs.append((key, ent[fi], want))
                struct.pack_into("<I", data, base + fi * 4, want)
        break

    if verbose:
        for field, old, new in diffs:
            print(f"  PT_LOAD     {field}: 0x{old:x} -> 0x{new:x}")
    return {"PT_LOAD": diffs} if diffs else {}


def _synthesize_tail(
    data: bytearray, manifest: dict, load_file_end: int, verbose: bool
) -> tuple[bytearray, dict]:
    """Stage 3: replace everything after the LOAD segment with retail's wrapping.

    Layout produced (offsets are retail-exact, US example):

      0x001000 .. 0x361ce4   LOAD segment content (untouched, already byte-identical)
      0x361ce4 .. 0x361d40   zero padding to the first non-loaded section
      0x361d40 .. 0x361d58   .reginfo            (24 bytes)
      0x361d58 .. 0x36f480   39 × .DVP.overlay   (53,032 bytes total)
      0x36f480 .. 0x36f480   .mdebug.eabi64      (0 bytes, header only)
      0x36f480 .. 0x36f654   .DVP.ovlytab        (468 bytes)
      0x36f654 .. 0x36fbd0   .DVP.ovlystrtab     (1404 bytes)
      0x36fbd0 .. 0x3701bf   .shstrtab           (from the metadata dir)
      0x3701c0 .. 0x3709e0   SHT, 52 × 40 bytes

    All non-loaded offsets/sizes are read from the manifest (retail-derived),
    so this is version-agnostic.
    """
    # Slice out the LOAD segment content (already byte-identical to retail).
    out = bytearray(data[:load_file_end])
    expected_size = manifest["total_size"]

    sections_by_idx = {s["idx"]: s for s in manifest["sections"]}

    def payload_bearing(s: dict) -> bool:
        return s["sh_type"] != 8 and s["sh_size"] != 0

    # Pad until the first payload-bearing non-loaded section (.reginfo).
    payload_offsets = [s["sh_offset"] for s in manifest["sections"] if payload_bearing(s)]
    if not payload_offsets:
        raise RuntimeError("manifest has no payload-bearing non-loaded sections")
    first_off = min(payload_offsets)
    pad = first_off - len(out)
    if pad < 0:
        raise RuntimeError(f"LOAD content overruns first non-loaded section by {-pad}")
    out += b"\x00" * pad

    # Write every payload-bearing non-loaded section at its retail sh_offset.
    for idx in sorted(sections_by_idx):
        s = sections_by_idx[idx]
        if not payload_bearing(s):            # SHT_NOBITS or header-only
            continue
        target = s["sh_offset"]
        if target < len(out):
            raise RuntimeError(
                f"section {s['name']!r} (idx {idx}) sh_offset 0x{target:x} "
                f"overlaps earlier output (cur 0x{len(out):x})"
            )
        if target > len(out):
            out += b"\x00" * (target - len(out))
        payload_path = ROOT / s["payload"]
        payload = payload_path.read_bytes()
        if len(payload) != s["sh_size"]:
            raise RuntimeError(
                f"{payload_path}: payload size {len(payload)} != sh_size {s['sh_size']}"
            )
        out += payload

    # Append .shstrtab (verbatim retail bytes).
    shstr_meta = manifest["shstrtab"]
    target = shstr_meta["sh_offset"]
    if target > len(out):
        out += b"\x00" * (target - len(out))
    shstr_bytes = (ROOT / shstr_meta["payload"]).read_bytes()
    if len(shstr_bytes) != shstr_meta["sh_size"]:
        raise RuntimeError(
            f"shstrtab.bin size {len(shstr_bytes)} != "
            f"manifest sh_size {shstr_meta['sh_size']}"
        )
    out += shstr_bytes

    # Build SHT.  Read retail's SHT from the metadata dir — by construction it
    # references our sh_offsets and the retail sh_size / sh_flags for loaded
    # sections.
    sht_meta = manifest["sht"]
    target = sht_meta["e_shoff"]
    if target > len(out):
        out += b"\x00" * (target - len(out))
    sht_bytes = (ROOT / sht_meta["payload"]).read_bytes()
    if len(sht_bytes) != sht_meta["e_shnum"] * SHENT_SIZE:
        raise RuntimeError(
            f"sht.bin size {len(sht_bytes)} != "
            f"{sht_meta['e_shnum']} * {SHENT_SIZE}"
        )
    out += sht_bytes

    if len(out) != expected_size:
        raise RuntimeError(
            f"synthesised size 0x{len(out):x} != retail size 0x{expected_size:x}"
        )

    # Patch ELF header e_shoff / e_shnum / e_shstrndx.
    struct.pack_into("<I", out, EHDR_OFF_SHOFF,    sht_meta["e_shoff"])
    struct.pack_into("<H", out, EHDR_OFF_SHNUM,    sht_meta["e_shnum"])
    struct.pack_into("<H", out, EHDR_OFF_SHSTRNDX, sht_meta["e_shstrndx"])

    if verbose:
        print(f"  synthesised tail: {len(out) - load_file_end} bytes after LOAD end")
        print(f"  final file size:  {len(out)} bytes (retail {expected_size})")

    return out, {"synth_tail_bytes": len(out) - load_file_end,
                 "final_size":       len(out)}


def post_process(
    elf_path: Path, *, metadata_dir: Path | None = None, verbose: bool = False
) -> dict:
    metadata_dir = Path(metadata_dir) if metadata_dir else DEFAULT_METADATA_DIR
    manifest_path = metadata_dir / "manifest.json"
    if not manifest_path.exists():
        raise FileNotFoundError(
            f"{manifest_path} missing — run "
            f"scripts/extract_elf_metadata.py for this version first"
        )
    manifest = json.loads(manifest_path.read_text())
    patches, retail_load, load_file_end = _load_retail_invariants(
        manifest, verbose=verbose
    )

    data = bytearray(elf_path.read_bytes())

    report: dict = {"metadata_dir": str(metadata_dir.relative_to(ROOT))
                    if metadata_dir.is_relative_to(ROOT) else str(metadata_dir)}
    report["eident_normalized"]  = _normalize_eident(data, verbose=verbose)
    report["loaded_sht_patches"] = _patch_loaded_sht(data, patches, verbose=verbose)
    report["phdr_patches"]       = _patch_phdr(data, retail_load, verbose=verbose)

    data, synth_report = _synthesize_tail(data, manifest, load_file_end, verbose=verbose)
    report["synth"] = synth_report

    elf_path.write_bytes(bytes(data))
    return report


# --------------------------------------------------------------------------- #
# CLI
# --------------------------------------------------------------------------- #
def main(argv: list[str]) -> int:
    p = argparse.ArgumentParser()
    p.add_argument("elf", type=Path)
    p.add_argument("--metadata-dir", type=Path, default=None,
                   help="per-version metadata dir (default: bin/elf_metadata)")
    p.add_argument("--verbose", "-v", action="store_true")
    p.add_argument("--report", type=Path, default=None)
    args = p.parse_args(argv)

    report = post_process(args.elf, metadata_dir=args.metadata_dir,
                          verbose=args.verbose)
    if args.report is not None:
        args.report.write_text(json.dumps(report, indent=2, default=str) + "\n")
    if args.verbose:
        print(f"postprocess: done ({args.elf})")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
