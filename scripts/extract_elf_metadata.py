#!/usr/bin/env python3
"""Extract the non-loaded ELF sections (and retail invariants) from a boot ELF.

The splat config (`config/<basename>.yaml` / `config/<key>/<basename>.yaml`)
operates on the .rom blob produced by `objcopy -O binary` — i.e. the contents
of the single LOAD program header (.text + .data + .sndata + .rodata +
.gcc_except_table, plus NOBITS .sbss/.bss).

However, the original ELF contains 43 sections that live *outside* that
LOAD segment and are therefore not in the .rom:

    1× .reginfo            MIPS_REGINFO     0x18 bytes
    1× .DVP.ovlytab        SHT_LOPROC+...   0x1D4 bytes
    1× .DVP.ovlystrtab     STRTAB           0x57C bytes
    1× .mdebug.eabi64      PROGBITS         0    bytes (header only)
   39× .DVP.overlay[N]     SHT_LOPROC+...   various

These are accessed at runtime by the VU0 microcode overlay loader and the
SN Systems debug runtime. To produce a byte-identical ELF we need to be
able to re-emit each as its own section, so we dump them to the per-version
metadata dir plus a JSON manifest with file offsets, sizes, addresses,
section types, and flags.

The manifest also records the *retail invariants* that ``elf_postprocess.py``
needs but cannot derive from the linked build alone:

  * ``retail.pt_load``        — the 8 PT_LOAD program-header fields.
  * ``retail.load_file_end``  — p_offset + p_filesz (where the LOAD content
                                ends in the file; the synth tail begins here).
  * ``retail.loaded_sections``— {name: {sh_size, sh_flags}} for each loaded
                                section, so the post-link SHT patch is exact.

These were US-hardcoded constants in ``elf_postprocess.py`` before; deriving
them here from the retail ELF makes the whole pipeline version-agnostic.

Usage:
    python scripts/extract_elf_metadata.py                 # us (default)
    python scripts/extract_elf_metadata.py --version eu    # eu/jp/...
    python scripts/extract_elf_metadata.py path/to/ELF     # explicit ELF
    python scripts/extract_elf_metadata.py path/to/ELF --out-dir DIR

Idempotent. Output dir convention: ``bin/elf_metadata`` for us (flat,
back-compat) and ``bin/elf_metadata/<key>`` for every other version.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
VERSIONS_JSON = REPO_ROOT / "config" / "versions.json"
DEFAULT_ELF = REPO_ROOT / "disc_extract" / "SLUS_215.03"
METADATA_ROOT = REPO_ROOT / "bin" / "elf_metadata"

# ELF32 little-endian
EHDR_FMT = "<16sHHIIIIIHHHHHH"
SHDR_FMT = "<IIIIIIIIII"
PHDR_FMT = "<8I"
EHDR_SIZE = struct.calcsize(EHDR_FMT)
SHDR_SIZE = struct.calcsize(SHDR_FMT)
PHDR_SIZE = struct.calcsize(PHDR_FMT)

PT_LOAD = 1
SHT_NOBITS = 8

# Field order for the PT_LOAD program header (ELF32).
PHDR_FIELDS = (
    "p_type", "p_offset", "p_vaddr", "p_paddr",
    "p_filesz", "p_memsz", "p_flags", "p_align",
)

# Section names whose payload is part of the LOAD segment and therefore
# already included in the .rom blob. We skip dumping these (their bytes are
# in the .rom) but DO record their sh_size/sh_flags as retail invariants.
LOAD_SEGMENT_SECTIONS = {
    ".text",
    ".data",
    ".sndata",
    ".rodata",
    ".gcc_except_table",
    ".sbss",
    ".bss",
}

# Pure-metadata / no-payload sections that we also skip (they don't need
# to be re-emitted byte-for-byte from a bin file).
SKIP_SECTIONS = {
    "",  # null section [0]
    ".shstrtab",  # section name string table — handled separately
}


def _load_versions() -> dict:
    if not VERSIONS_JSON.exists():
        return {}
    return json.loads(VERSIONS_JSON.read_text())


def metadata_dir_for(version: str) -> Path:
    """Per-version metadata dir. us is flat (back-compat); others nest."""
    if version == "us":
        return METADATA_ROOT
    return METADATA_ROOT / version


def resolve_inputs(version: str | None, elf_arg: str | None,
                   out_dir_arg: str | None) -> tuple[Path, Path, str]:
    """Resolve (elf_path, out_dir, version_key) from CLI args + registry."""
    reg = _load_versions()
    key = version or (reg.get("default", "us") if reg else "us")

    if elf_arg is not None:
        elf_path = Path(elf_arg)
    else:
        versions = reg.get("versions", {})
        if key in versions:
            basename = versions[key]["basename"]
            elf_path = REPO_ROOT / "disc_extract" / basename
        elif key == "us":
            elf_path = DEFAULT_ELF
        else:
            raise SystemExit(
                f"version '{key}' not in {VERSIONS_JSON.relative_to(REPO_ROOT)}"
            )

    out_dir = Path(out_dir_arg) if out_dir_arg else metadata_dir_for(key)
    return elf_path, out_dir, key


def parse_elf(path: Path) -> dict:
    raw = path.read_bytes()
    (
        ident,
        e_type,
        e_machine,
        e_version,
        e_entry,
        e_phoff,
        e_shoff,
        e_flags,
        e_ehsize,
        e_phentsize,
        e_phnum,
        e_shentsize,
        e_shnum,
        e_shstrndx,
    ) = struct.unpack(EHDR_FMT, raw[:EHDR_SIZE])

    assert ident[:4] == b"\x7fELF", "not an ELF"
    assert e_shentsize == SHDR_SIZE, f"unexpected shentsize {e_shentsize}"
    assert e_phentsize == PHDR_SIZE, f"unexpected phentsize {e_phentsize}"

    # Program headers.
    phdrs = []
    for i in range(e_phnum):
        off = e_phoff + i * PHDR_SIZE
        vals = struct.unpack(PHDR_FMT, raw[off:off + PHDR_SIZE])
        phdrs.append(dict(zip(PHDR_FIELDS, vals)))

    # shstrtab
    shstr_off = struct.unpack(
        SHDR_FMT, raw[e_shoff + e_shstrndx * SHDR_SIZE:][:SHDR_SIZE]
    )[4]
    shstr = raw[shstr_off:]

    sections = []
    for i in range(e_shnum):
        off = e_shoff + i * SHDR_SIZE
        (
            sh_name,
            sh_type,
            sh_flags,
            sh_addr,
            sh_offset,
            sh_size,
            sh_link,
            sh_info,
            sh_addralign,
            sh_entsize,
        ) = struct.unpack(SHDR_FMT, raw[off:off + SHDR_SIZE])
        name_end = shstr.index(b"\x00", sh_name)
        name = shstr[sh_name:name_end].decode("ascii", "replace")
        sections.append(
            dict(
                idx=i,
                name=name,
                sh_type=sh_type,
                sh_flags=sh_flags,
                sh_addr=sh_addr,
                sh_offset=sh_offset,
                sh_size=sh_size,
                sh_link=sh_link,
                sh_info=sh_info,
                sh_addralign=sh_addralign,
                sh_entsize=sh_entsize,
            )
        )

    return dict(
        raw=raw,
        e_flags=e_flags,
        e_entry=e_entry,
        phdrs=phdrs,
        sections=sections,
        e_shoff=e_shoff,
        e_shnum=e_shnum,
        e_shstrndx=e_shstrndx,
    )


def safe_filename(name: str, idx: int) -> str:
    """ELF sections can repeat names (`.DVP.overlay[...]` ×39).
    Stash by section index to keep them unique on disk."""
    base = name.lstrip(".").replace(".", "_").replace("[", "_").replace("]", "_") or "noname"
    return f"sec{idx:02d}_{base}.bin"


def build_retail_block(elf: dict) -> dict:
    """Derive the version-agnostic retail invariants for elf_postprocess.py.

    Replaces the formerly US-hardcoded RETAIL_LOAD / LOADED_SECTION_PATCHES /
    LOAD_FILE_END constants — every value here is read straight from the
    retail boot ELF, so eu/jp/... get correct values for free.
    """
    load = next((p for p in elf["phdrs"] if p["p_type"] == PT_LOAD), None)
    if load is None:
        raise RuntimeError("no PT_LOAD program header in retail ELF")

    loaded_sections = {}
    for s in elf["sections"]:
        if s["name"] in LOAD_SEGMENT_SECTIONS:
            loaded_sections[s["name"]] = {
                "sh_size":  s["sh_size"],
                "sh_flags": s["sh_flags"],
            }

    return {
        "pt_load": dict(load),
        "load_file_end": load["p_offset"] + load["p_filesz"],
        "load_file_end_hex": f"0x{load['p_offset'] + load['p_filesz']:x}",
        "loaded_sections": loaded_sections,
        "entry": elf["e_entry"],
        "entry_hex": f"0x{elf['e_entry']:x}",
    }


def extract(elf_path: Path, out_dir: Path, version: str) -> dict:
    elf = parse_elf(elf_path)
    raw = elf["raw"]
    sections = elf["sections"]
    e_shoff = elf["e_shoff"]
    e_shnum = elf["e_shnum"]
    e_shstrndx = elf["e_shstrndx"]
    out_dir.mkdir(parents=True, exist_ok=True)

    def relpath(p: Path) -> str:
        return str(p.relative_to(REPO_ROOT)) if p.is_relative_to(REPO_ROOT) else str(p)

    out_dir_rel = relpath(out_dir)

    manifest = {
        "version": version,
        "source_elf": relpath(elf_path),
        "source_sha256": hashlib.sha256(raw).hexdigest(),
        "e_flags": f"0x{elf['e_flags']:08x}",
        # Retail invariants consumed by elf_postprocess.py (previously
        # hardcoded for US in that script).
        "retail": build_retail_block(elf),
        "sections": [],
    }

    # The .shstrtab is pure metadata (only contains C-string section names
    # plus historical .symtab/.strtab leading entries that survive strip).
    # Dumping it lets the post-link ELF synthesiser splice the retail
    # byte-identical section header string table back in without having to
    # carry the leading-string archaeology in code.
    shstr_ent = struct.unpack(
        SHDR_FMT, raw[e_shoff + e_shstrndx * SHDR_SIZE:][:SHDR_SIZE]
    )
    shstr_bytes = raw[shstr_ent[4]:shstr_ent[4] + shstr_ent[5]]
    (out_dir / "shstrtab.bin").write_bytes(shstr_bytes)
    manifest["shstrtab"] = {
        "sh_offset":      shstr_ent[4],
        "sh_offset_hex":  f"0x{shstr_ent[4]:x}",
        "sh_size":        shstr_ent[5],
        "sh_size_hex":    f"0x{shstr_ent[5]:x}",
        "payload":        f"{out_dir_rel}/shstrtab.bin",
        "payload_sha256": hashlib.sha256(shstr_bytes).hexdigest(),
    }

    # The section header table also lives outside the LOAD segment and is
    # purely metadata.  Record its location and bytes for the synthesiser.
    sht_bytes = raw[e_shoff:e_shoff + e_shnum * SHDR_SIZE]
    (out_dir / "sht.bin").write_bytes(sht_bytes)
    manifest["sht"] = {
        "e_shoff":        e_shoff,
        "e_shoff_hex":    f"0x{e_shoff:x}",
        "e_shnum":        e_shnum,
        "e_shstrndx":     e_shstrndx,
        "shentsize":      SHDR_SIZE,
        "payload":        f"{out_dir_rel}/sht.bin",
        "payload_sha256": hashlib.sha256(sht_bytes).hexdigest(),
    }

    # Total retail ELF size — useful for the synthesiser to right-size the
    # output and for sanity checks.
    manifest["total_size"] = len(raw)
    manifest["total_size_hex"] = f"0x{len(raw):x}"

    extracted = 0
    skipped_loaded = 0
    for s in sections:
        name = s["name"]
        if name in SKIP_SECTIONS:
            continue
        if name in LOAD_SEGMENT_SECTIONS:
            skipped_loaded += 1
            continue
        entry = dict(s)
        entry["sh_type_hex"] = f"0x{s['sh_type']:08x}"
        entry["sh_flags_hex"] = f"0x{s['sh_flags']:08x}"
        entry["sh_addr_hex"] = f"0x{s['sh_addr']:08x}"
        entry["sh_offset_hex"] = f"0x{s['sh_offset']:x}"
        entry["sh_size_hex"] = f"0x{s['sh_size']:x}"

        if s["sh_type"] == SHT_NOBITS:
            entry["payload"] = None
        elif s["sh_size"] == 0:
            entry["payload"] = None  # e.g. .mdebug.eabi64 (header only)
        else:
            payload = raw[s["sh_offset"]:s["sh_offset"] + s["sh_size"]]
            fname = safe_filename(name, s["idx"])
            (out_dir / fname).write_bytes(payload)
            entry["payload"] = f"{out_dir_rel}/{fname}"
            entry["payload_sha256"] = hashlib.sha256(payload).hexdigest()
            extracted += 1

        manifest["sections"].append(entry)

    manifest_path = out_dir / "manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(
        f"[{version}] Extracted {extracted} payload section(s) → {out_dir_rel}/, "
        f"skipped {skipped_loaded} loaded section(s) already in .rom. "
        f"Manifest: {relpath(manifest_path)}"
    )
    return manifest


def main(argv: list[str]) -> int:
    p = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    p.add_argument("elf", nargs="?", default=None,
                   help="path to the boot ELF (default: resolved from --version)")
    p.add_argument("--version", default=None,
                   help="version key from config/versions.json (default: us)")
    p.add_argument("--out-dir", default=None,
                   help="output dir (default: bin/elf_metadata[/<key>])")
    args = p.parse_args(argv)

    elf_path, out_dir, key = resolve_inputs(args.version, args.elf, args.out_dir)
    if not elf_path.exists():
        raise SystemExit(
            f"retail ELF not found: {elf_path} "
            f"(run scripts/extract_iso.sh --version {key})"
        )
    extract(elf_path, out_dir, key)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
