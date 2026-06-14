#!/usr/bin/env python3
"""
Verify splat data-segment round-trip without invoking the linker.

For every data .s file splat emits, walk the directives and reconstruct the
exact byte stream of the original ELF section.  This proves splat read every
byte and re-encoded it losslessly even though `.word` references to other
sections are still symbolic (those get resolved by the linker at link time).

How splat writes data lines (observed from spimdisasm 1.40.3 output):

    /* off vaddr HEXBYTES */ .word 0xXXXXXXXX     -- literal word, hex in comment
    /* off vaddr HEXBYTES */ .word symbol         -- symbolic word, hex shows ORIGINAL bytes
    /* off vaddr HEXBYTES */ .float 1.0           -- IEEE float, hex shows bytes
    /* off vaddr HEXBYTES */ .double 1.0          -- IEEE double, hex shows bytes
    /* off vaddr */          .short 0xVAL         -- no hex comment, value is little-endian short
    /* off vaddr */          .byte  0xVAL         -- no hex comment, value is the byte
    /* off vaddr */          .asciz "..."         -- no hex on this line
        /* HEXBYTES */                            -- bare comment carries asciz bytes + alignment pad
    .align N                                      -- aligns the running cursor to 2**N; spat WILL emit
                                                    `.align` *before* a label inside a subsegment but
                                                    inside a data subsegment the alignment is also
                                                    captured by either the bare hex line above or by
                                                    the surrounding directive layout (we honor .align
                                                    explicitly to be safe)

We honor `.align`, `.word`, `.byte`, `.short`, `.float`, `.double`, `.asciz`,
and the bare-hex follow-up line.  The trailing-HEX triplet remains the
ground truth for any directive that has one.

Usage:
    python scripts/verify_splat_roundtrip.py
Exits 0 on byte-perfect round-trip of every data subsegment, 1 otherwise.
"""
from __future__ import annotations

import hashlib
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
# Splat reads the contiguous loaded image (build/SLUS_215.03.rom), not the
# ELF. The .rom is laid out by subsegment offset, so .data/.sndata/.rodata
# include the inter-section alignment padding that the linker emits at link
# time. Compare against the .rom to validate exactly what splat read.
ROM = ROOT / "build" / "SLUS_215.03.rom"

# (label, splat relpath, ROM offset, size-including-trailing-gap)
# Size is `next_subsegment_offset - this_subsegment_offset`, i.e. exactly
# the byte range splat assigns to this subsegment.
SECTIONS = [
    (".text",             "asm/cod/000000.s",                       0x000000, 0x2BBF80 - 0x000000),
    (".data",             "asm/data/cod/2BBF80.data.s",             0x2BBF80, 0x30A400 - 0x2BBF80),
    (".sndata",           "asm/data/cod/30A400.sndata.s",           0x30A400, 0x31B580 - 0x30A400),
    (".rodata",           "asm/data/cod/31B580.rodata.s",           0x31B580, 0x360C00 - 0x31B580),
    (".gcc_except_table", "asm/data/cod/360C00.gcc_except_table.s", 0x360C00, 0x360CE4 - 0x360C00),
]

# Trailing-HEX form: /* off vaddr HEX */ .directive ...
ADDR_HEX_RE = re.compile(
    r"^\s*/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+\*/"
)
# Addr-only form (no hex):     /* off vaddr */ .directive ...
ADDR_ONLY_RE = re.compile(
    r"^\s*/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+\*/\s*(\..+)$"
)
# Bare hex line on its own (asciz bytes + alignment pad)
BARE_HEX_RE = re.compile(r"^\s*/\*\s+([0-9A-Fa-f]+)\s+\*/\s*$")
# Standalone .align directive
ALIGN_RE = re.compile(r"^\s*\.align\s+(\d+)\s*$")


def parse_literal(arg: str) -> int:
    arg = arg.strip().rstrip(",").strip()
    if arg.startswith(("0x", "0X")) or arg.startswith(("-0x", "-0X")):
        return int(arg, 16)
    return int(arg, 0)


def directive_bytes(directive_line: str) -> bytes:
    """Encode an addr-only directive line into its byte sequence."""
    # Strip trailing comments
    line = directive_line.split("#")[0].rstrip()
    # The asciz/ascii body is followed by a bare-hex line so we ignore it
    # here -- the BARE_HEX line will contribute its bytes.
    if line.startswith(".asciz") or line.startswith(".ascii"):
        return b""
    if line.startswith(".short"):
        val = parse_literal(line[len(".short"):])
        return struct.pack("<H", val & 0xFFFF)
    if line.startswith(".byte"):
        # .byte may have multiple comma-separated values
        body = line[len(".byte"):].strip()
        vals = [parse_literal(v) for v in body.split(",") if v.strip()]
        return bytes(v & 0xFF for v in vals)
    if line.startswith(".word"):
        # No-hex .word is unusual but possible; treat as symbolic-zero word.
        return b"\x00\x00\x00\x00"
    if line.startswith(".float"):
        val = float(line[len(".float"):].strip())
        return struct.pack("<f", val)
    if line.startswith(".double"):
        val = float(line[len(".double"):].strip())
        return struct.pack("<d", val)
    return b""


def rebuild(path: Path) -> bytes:
    out = bytearray()

    def align_to(boundary: int) -> None:
        if boundary <= 1:
            return
        rem = len(out) % boundary
        if rem:
            out.extend(b"\x00" * (boundary - rem))

    for line in path.read_text().splitlines():
        # Trailing-HEX form is always authoritative: use those bytes.
        m = ADDR_HEX_RE.match(line)
        if m:
            out.extend(bytes.fromhex(m.group(1)))
            continue
        # Bare-hex line (asciz body / alignment fill).
        m = BARE_HEX_RE.match(line)
        if m:
            out.extend(bytes.fromhex(m.group(1)))
            continue
        # Addr-only form with directive: interpret directive.
        m = ADDR_ONLY_RE.match(line)
        if m:
            out.extend(directive_bytes(m.group(1).strip()))
            continue
        # Standalone .align (rare for data, but be safe).
        m = ALIGN_RE.match(line)
        if m:
            align_to(1 << int(m.group(1)))
            continue
        # Any other line (labels, .section, comments) contributes no bytes.
    return bytes(out)


import json

ELF = ROOT / "disc_extract" / "SLUS_215.03"
METADATA_MANIFEST = ROOT / "bin" / "elf_metadata" / "manifest.json"


def check_loaded_subsegments() -> int:
    print(f"\n[1/2] loaded subsegments vs {ROM.name}")
    rc = 0
    for name, rel, off, size in SECTIONS:
        src = ROOT / rel
        rebuilt = rebuild(src)
        with ROM.open("rb") as fh:
            fh.seek(off)
            ref = fh.read(size)
        ok = rebuilt == ref
        mark = "OK " if ok else "BAD"
        rb_sha = hashlib.sha256(rebuilt).hexdigest()[:16]
        rf_sha = hashlib.sha256(ref).hexdigest()[:16]
        print(
            f"  [{mark}] {name:<18s} src={src.name:<32s} "
            f"rebuilt={len(rebuilt):>8d} ref={len(ref):>8d} "
            f"sha={rb_sha}"
        )
        if not ok:
            rc = 1
            for i, (a, b) in enumerate(zip(rebuilt, ref)):
                if a != b:
                    ctx = max(0, i - 8)
                    print(
                        f"        first diff at off=0x{i:x}: "
                        f"rebuilt={a:#04x} ref={b:#04x}  "
                        f"context rebuilt={rebuilt[ctx:i+8].hex()}  "
                        f"context ref={ref[ctx:i+8].hex()}"
                    )
                    break
            if len(rebuilt) != len(ref):
                print(f"        size mismatch: rebuilt={len(rebuilt)} ref={len(ref)}")
    return rc


def check_dvp_overlays() -> int:
    print(f"\n[2/2] .DVP.overlay blobs vs {ELF.name}")
    m = json.loads(METADATA_MANIFEST.read_text())
    elf = ELF.read_bytes()
    elf_sha = hashlib.sha256(elf).hexdigest()
    if elf_sha != m["source_sha256"]:
        print(f"  [BAD] ELF sha256 mismatch with manifest source_sha256")
        return 1
    rc = 0
    ok = total = 0
    total_bytes = 0
    for s in m["sections"]:
        if "DVP.overlay" not in s["name"]:
            continue
        total += 1
        blob = (ROOT / s["payload"]).read_bytes()
        ref = elf[s["sh_offset"] : s["sh_offset"] + s["sh_size"]]
        if blob == ref and hashlib.sha256(blob).hexdigest() == s["payload_sha256"]:
            ok += 1
            total_bytes += s["sh_size"]
        else:
            rc = 1
            print(f"  [BAD] {s['name']}  bytes={len(blob)} expect={s['sh_size']}")
    mark = "OK " if rc == 0 else "BAD"
    print(f"  [{mark}] {ok}/{total} overlay blobs match  (total 0x{total_bytes:X} bytes)")
    return rc


def main() -> int:
    print(f"Verifying splat round-trip")
    rc = check_loaded_subsegments()
    rc |= check_dvp_overlays()
    print()
    if rc == 0:
        print("PASS: every byte of every section is accounted for.")
    else:
        print("FAIL: see diagnostics above.")
    return rc


if __name__ == "__main__":
    sys.exit(main())
