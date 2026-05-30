#!/usr/bin/env python3
"""Per-`.rel` SNR2 inventory.

Walks ``disc_extract/rel/*.rel`` and emits a per-REL summary table to
stdout *and* a machine-readable JSON file at
``progress/rel_inventory.json``.

An earlier assumption held that the on-disc ``.rel`` blobs were plain
``ET_REL`` MIPS ELF objects.  That is **wrong**: every blob begins
with ``"SNR2"``
(SN ProDG relocatable EXE for PS2), the same container used by Capcom's
PS2 Resident Evil 4 overlays.  Format reference: emoose/re4-research
(`prodg-rel.py`, `file-formats/ProDG-SNR2.bt`); cross-checked by
parsing each header here.

SNR2 header layout (60 B / 0x3C):

    /* 0x00 */ uint32  Magic                      "SNR2" (0x32524E53 LE)
    /* 0x04 */ uint32  RelocTableAddress
    /* 0x08 */ uint32  RelocTableCount
    /* 0x0C */ uint32  FuncTableAddress
    /* 0x10 */ uint32  FuncTableCount
    /* 0x14 */ uint32  OriginalImageNameAddress   (offset of NUL-term string)
    /* 0x18 */ uint32  GlobalCtorsAddress
    /* 0x1C */ uint32  GlobalDtorsAddress
    /* 0x20 */ uint32  ExportsAddress
    /* 0x24 */ uint32  ExportsCount
    /* 0x28 */ uint32  Unk28                      (== 0x80 across this corpus)
    /* 0x2C */ uint32  FileSize                   (== os.path.getsize, always)
    /* 0x30 */ uint32  Unk30
    /* 0x34 */ uint32  UnkAddr34
    /* 0x38 */ uint32  UnkAddr38
    /* 0x3C  end */

Reloc table entry (12 B); per emoose's IDAPython loader this is
``Elf32_Rela``-shaped:

    uint32 r_offset    (patch site, in REL-local image bytes)
    uint8  r_type      (MIPS relocation type)
    uint8  r_sym       (index into the function table)
    int32  r_addend    (always 0 in this corpus)
    uint16 _pad        (always 0)

The 010 Editor template (`ProDG-SNR2.bt`) names byte-5/6 as a single
``uint16 FunctionIdx``.  In this corpus every REL's function index
fits in a single byte (max observed = 122 vs. FuncTableCount up to
470) so the two readings are observationally indistinguishable; we
go with the IDA loader's ``Elf32_Rela`` shape because it is the
interpretation that was actually run against MIPS bytecode.  The
``cRelSys`` decomp will resolve the ambiguity definitively.

Function table entry (12 B):

    uint32 NameAddress    (offset of NUL-term string)
    uint32 CodeAddress    (REL-local; 0 == undefined / external import)
    uint16 Unk8
    uint8  Type
    uint8  UnkB

A function with ``CodeAddress == 0`` is an undefined external symbol —
the REL loader must resolve it against the main ELF's ``.symtab``
(per IDA loader: ``if ent.CodeAddress == 0: continue``).  We count
those as ``n_undef_syms``.  The ``ImageSize``-derived ``text_size`` /
``data_size`` are *heuristic*: the SNR2 header doesn't carry explicit
section bounds, so we follow the IDA loader's strategy of carving:

    sndata_ext_addr = min(OriginalImageNameAddress, RelocTableAddress,
                          FuncTableAddress, every NameAddress)
    text_size  = sndata_ext_addr - 0x3C          (code + early data)
    data_size  = file_size - sndata_ext_addr     (strings + tables)
    bss_size   = 0                               (not encoded on disc)

Pure read-only.  No deps outside the stdlib.

Output JSON shape (sorted by name):

    [
      {
        "name": "event.rel",
        "sha256": "...",
        "size": 80431,
        "n_sections": 2,
        "n_relocs": 518,
        "n_funcs": 393,
        "n_undef_syms": <count>,
        "n_exports": 0,
        "text_size": <int>,
        "data_size": <int>,
        "bss_size": 0,
        "reloc_types": {"4": 221, "5": 130, "6": 167}
      },
      ...
    ]

The ``n_sections`` is fixed at 2 (`.text+early-data` and `.sndata`-
like tail) since SNR2 does not encode section bounds explicitly; this
mirrors the IDA loader's segment carving.
"""

from __future__ import annotations

import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
REL_DIR = ROOT / "disc_extract" / "rel"
PROGRESS_DIR = ROOT / "progress"
OUT_JSON = PROGRESS_DIR / "rel_inventory.json"

SNR2_MAGIC = 0x32524E53  # "SNR2" little-endian
HEADER_SIZE = 0x3C
RELOC_ENTRY_SIZE = 12
FUNC_ENTRY_SIZE = 12

# MIPS relocation types observed (per emoose's IDA loader: only 2/4/5/6 ever
# seen across PS2 SNR2 corpora). Keep the enum minimal — recon-only.
MIPS_RELOC_NAMES = {
    0: "R_MIPS_NONE",
    1: "R_MIPS_16",
    2: "R_MIPS_32",
    3: "R_MIPS_REL32",
    4: "R_MIPS_26",
    5: "R_MIPS_HI16",
    6: "R_MIPS_LO16",
}


def _read_cstr(data: bytes, offset: int, max_len: int = 256) -> str:
    end = data.find(b"\x00", offset, min(offset + max_len, len(data)))
    if end < 0:
        end = min(offset + max_len, len(data))
    try:
        return data[offset:end].decode("ascii")
    except UnicodeDecodeError:
        return data[offset:end].decode("latin-1", errors="replace")


def parse_rel(path: Path) -> dict:
    raw = path.read_bytes()
    if len(raw) < HEADER_SIZE:
        raise ValueError(f"{path.name}: short file ({len(raw)} B)")
    hdr = struct.unpack_from("<15I", raw, 0)
    (
        magic,
        reloc_addr,
        reloc_cnt,
        func_addr,
        func_cnt,
        img_name_addr,
        ctors_addr,
        dtors_addr,
        exports_addr,
        exports_cnt,
        unk28,
        file_size_hdr,
        unk30,
        unk_addr_34,
        unk_addr_38,
    ) = hdr
    if magic != SNR2_MAGIC:
        raise ValueError(
            f"{path.name}: bad magic 0x{magic:08x} (expected SNR2)"
        )
    if file_size_hdr != len(raw):
        raise ValueError(
            f"{path.name}: header FileSize {file_size_hdr} != on-disk "
            f"{len(raw)}"
        )

    # Function table — parse first so we know which entries are externals
    # and so we can compute sndata_ext_addr.
    funcs: list[dict] = []
    name_addrs: list[int] = []
    for i in range(func_cnt):
        off = func_addr + i * FUNC_ENTRY_SIZE
        (n_addr, c_addr, unk8, ftype, unkB) = struct.unpack_from(
            "<IIHBB", raw, off
        )
        funcs.append(
            {
                "name_addr": n_addr,
                "code_addr": c_addr,
                "unk8": unk8,
                "type": ftype,
                "unkB": unkB,
            }
        )
        name_addrs.append(n_addr)

    # IDA-loader carving: .text+early-data ends where the first name string
    # or any of the three tables starts.
    candidates = [a for a in name_addrs if a > 0]
    for a in (img_name_addr, reloc_addr, func_addr):
        if a > 0:
            candidates.append(a)
    sndata_ext_addr = min(candidates) if candidates else len(raw)

    # Resolve names lazily and tag externals.
    n_undef = 0
    for f in funcs:
        f["name"] = _read_cstr(raw, f["name_addr"]) if f["name_addr"] else ""
        if f["code_addr"] == 0:
            n_undef += 1

    # Reloc table — interpret as Elf32_Rela (uint8 r_sym, int32 r_addend, u16 pad)
    reloc_types: dict[int, int] = {}
    sym_ref_count: dict[str, int] = {}
    addend_nonzero = 0
    pad_nonzero = 0
    relocs: list[dict] = []
    for i in range(reloc_cnt):
        off = reloc_addr + i * RELOC_ENTRY_SIZE
        (r_off, r_type, r_sym, r_addend, r_pad) = struct.unpack_from(
            "<IBBiH", raw, off
        )
        reloc_types[r_type] = reloc_types.get(r_type, 0) + 1
        if r_sym < len(funcs):
            nm = funcs[r_sym]["name"]
            sym_ref_count[nm] = sym_ref_count.get(nm, 0) + 1
        if r_addend != 0:
            addend_nonzero += 1
        if r_pad != 0:
            pad_nonzero += 1
        relocs.append(
            {
                "r_offset": r_off,
                "r_type": r_type,
                "r_sym": r_sym,
                "r_addend": r_addend,
            }
        )

    img_name = _read_cstr(raw, img_name_addr) if img_name_addr else ""

    text_size = max(0, sndata_ext_addr - HEADER_SIZE)
    data_size = max(0, len(raw) - sndata_ext_addr)

    return {
        "name": path.name,
        "sha256": hashlib.sha256(raw).hexdigest(),
        "size": len(raw),
        "n_sections": 2,
        "n_relocs": reloc_cnt,
        "n_funcs": func_cnt,
        "n_undef_syms": n_undef,
        "n_exports": exports_cnt,
        "text_size": text_size,
        "data_size": data_size,
        "bss_size": 0,
        "reloc_types": {str(k): v for k, v in sorted(reloc_types.items())},
        "addend_nonzero": addend_nonzero,
        "pad_nonzero": pad_nonzero,
        "image_name": img_name,
        "header": {
            "reloc_addr": reloc_addr,
            "func_addr": func_addr,
            "img_name_addr": img_name_addr,
            "ctors_addr": ctors_addr,
            "dtors_addr": dtors_addr,
            "exports_addr": exports_addr,
            "unk28": unk28,
            "unk30": unk30,
            "unk_addr_34": unk_addr_34,
            "unk_addr_38": unk_addr_38,
        },
        "top_symbols": sorted(
            sym_ref_count.items(), key=lambda kv: (-kv[1], kv[0])
        )[:10],
        "_relocs": relocs,  # filtered out of the JSON below
        "_funcs": funcs,    # filtered out of the JSON below
    }


def _strip_internal(entry: dict) -> dict:
    return {k: v for k, v in entry.items() if not k.startswith("_")}


def main(argv: list[str]) -> int:
    rels = sorted(REL_DIR.glob("*.rel"))
    if not rels:
        print(
            f"error: no .rel files in {REL_DIR.relative_to(ROOT)}. "
            "Run scripts/afs_extract.py first.",
            file=sys.stderr,
        )
        return 2

    rows: list[dict] = []
    for path in rels:
        try:
            rows.append(parse_rel(path))
        except Exception as exc:  # noqa: BLE001 — recon, surface everything
            print(f"error parsing {path.name}: {exc}", file=sys.stderr)
            return 2

    rows.sort(key=lambda r: r["name"])

    # Markdown table to stdout.
    print(
        "| name | size | n_funcs | n_undef | n_reloc | "
        "r4_26 | r5_HI16 | r6_LO16 | r2_32 | text | data |"
    )
    print("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|")
    for r in rows:
        rt = r["reloc_types"]
        print(
            "| `{name}` | {size} | {nf} | {nu} | {nr} | {r4} | {r5} | "
            "{r6} | {r2} | {tx} | {da} |".format(
                name=r["name"],
                size=r["size"],
                nf=r["n_funcs"],
                nu=r["n_undef_syms"],
                nr=r["n_relocs"],
                r4=rt.get("4", 0),
                r5=rt.get("5", 0),
                r6=rt.get("6", 0),
                r2=rt.get("2", 0),
                tx=r["text_size"],
                da=r["data_size"],
            )
        )

    # JSON dump (strip the internal arrays before writing).
    PROGRESS_DIR.mkdir(exist_ok=True)
    clean = [_strip_internal(r) for r in rows]
    OUT_JSON.write_text(
        json.dumps(clean, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    print(
        f"\nwrote {OUT_JSON.relative_to(ROOT)} "
        f"({len(rows)} entries, {sum(r['n_relocs'] for r in rows)} relocs "
        f"total, {sum(r['n_funcs'] for r in rows)} func entries total)",
        file=sys.stderr,
    )
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
