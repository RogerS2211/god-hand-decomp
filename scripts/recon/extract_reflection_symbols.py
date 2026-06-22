#!/usr/bin/env python3
"""extract_reflection_symbols.py — recover function names from God Hand's
embedded C++ method reflection table.

God Hand's boot ELF ships a C++ method-registration table: ~48-byte records,
each holding a pointer to a mangled GNU-v2 symbol name immediately followed by
the function's code pointer. This recovers a name->address map directly from
the retail bytes (ground truth), demangles with mipsel-linux-gnu-c++filt, and
emits house-style `Class_method` names for use in config/symbol_addrs.txt.

Usage:
    .venv/bin/python scripts/recon/extract_reflection_symbols.py            # report
    .venv/bin/python scripts/recon/extract_reflection_symbols.py --out FILE # write map
"""
from __future__ import annotations
import argparse, re, struct, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
ROM = ROOT / "build" / "SLUS_215.03.rom"
BASE = 0x00100000                      # rom offset 0 == vaddr 0x00100000
TEXT_LO, TEXT_HI = 0x00100000, 0x003FFFFF
MANGLED = re.compile(rb"[A-Za-z_][A-Za-z0-9_]*__[0-9FCHQ][A-Za-z0-9_]*")

def find_strings(rom: bytes) -> dict[bytes, int]:
    """All NUL-terminated mangled symbol strings -> their vaddr."""
    out = {}
    for m in re.finditer(rb"[ -~]{5,}", rom):
        s = m.group()
        for mm in MANGLED.finditer(s):
            sym = mm.group()
            # absolute offset of this sym within rom
            off = m.start() + mm.start()
            out.setdefault(sym, BASE + off)
    return out

def recover_pairs(rom: bytes, sym_va: dict[bytes, int]) -> dict[int, bytes]:
    """For each symbol string, find word-aligned refs; the next word is the
    function pointer when it lands in TEXT. Returns func_addr -> mangled name."""
    pairs = {}
    for sym, va in sym_va.items():
        tgt = struct.pack("<I", va)
        start = 0
        while True:
            j = rom.find(tgt, start)
            if j < 0:
                break
            if j % 4 == 0 and j + 8 <= len(rom):
                nxt = struct.unpack("<I", rom[j + 4:j + 8])[0]
                if TEXT_LO <= nxt <= TEXT_HI:
                    pairs.setdefault(nxt, sym)
            start = j + 1
    return pairs

def _parse_class(rest: str) -> str | None:
    """Parse a GNU-v2 class spec off the front of a mangled type stream."""
    if not rest:
        return None
    c = rest[0]
    if c == "F":                                  # global function (no class)
        return None
    if c in "CV":                                 # const/volatile member
        return _parse_class(rest[1:])
    if c == "Q":                                  # nested: Q<count><comp>...
        m = re.match(r"_(\d+)_", rest[1:])
        if m:
            cnt = int(m.group(1)); k = 1 + m.end()
        else:
            cnt = int(rest[1]); k = 2
        comps = []
        for _ in range(cnt):
            mm = re.match(r"(\d+)", rest[k:])
            if not mm:
                break
            n = int(mm.group(1)); k += mm.end()
            comps.append(rest[k:k + n]); k += n
        return "_".join(comps) if comps else None
    if c.isdigit():                               # length-prefixed class name
        mm = re.match(r"(\d+)", rest); n = int(mm.group(1)); s = mm.end()
        return rest[s:s + n]
    return None

def house_name(mangled: str) -> str | None:
    """GNU-v2 mangled symbol -> house-style `Class_method` / `func` identifier.

    ee-gcc 2.96 uses the pre-3.0 (GNU v2) mangling that modern c++filt no
    longer demangles, so we parse class+method directly. Argument types are
    dropped on purpose (they only matter for overload disambiguation, handled
    with an address suffix at apply time)."""
    i = mangled.find("__")
    while i != -1:
        nxt = mangled[i + 2:i + 3]
        if nxt and (nxt.isdigit() or nxt in "FCQVtH"):
            break
        i = mangled.find("__", i + 2)
    if i == -1:
        return re.sub(r"[^A-Za-z0-9_]", "_", mangled) or None
    method = mangled[:i] or "ctor"
    cls = _parse_class(mangled[i + 2:])
    name = f"{cls}_{method}" if cls else method
    name = re.sub(r"[^A-Za-z0-9_]", "_", name)
    if not re.match(r"[A-Za-z_]", name):
        name = "_" + name
    return name or None

def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=None)
    args = ap.parse_args(argv)
    if not ROM.exists():
        sys.exit(f"missing {ROM}; run the build first")
    rom = ROM.read_bytes()
    sym_va = find_strings(rom)
    pairs = recover_pairs(rom, sym_va)
    rows = []
    for addr, sym in sorted(pairs.items()):
        s = sym.decode("latin1")
        rows.append((addr, s, s, house_name(s)))
    print(f"mangled symbols found : {len(sym_va)}")
    print(f"name->addr recovered  : {len(pairs)}")
    print(f"house-nameable        : {sum(1 for r in rows if r[3])}")
    if args.out:
        with open(args.out, "w") as f:
            for addr, sym, d, hn in rows:
                f.write(f"0x{addr:08X}\t{hn or ''}\t{sym}\t{d}\n")
        print(f"wrote {args.out}")
    return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
