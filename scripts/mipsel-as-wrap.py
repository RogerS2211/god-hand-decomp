#!/usr/bin/env python3
"""mipsel-as-wrap.py — assembler shim for modern GNU binutils (>= ~2.43).

Why this exists
---------------
The monolithic/​carved ``.s`` for this project use the **O32 symbolic register
names** ($t0-$t7 == $8-$15) that the EE disassembly emits.  Historically the
build assembled them with ``mipsel-linux-gnu-as -mabi=eabi``, and binutils
through 2.42 mapped EABI register names the O32 way, so $t0-$t7 resolved to
$8-$15 and the eabi64 ELF flag (0x4000) matched retail / the ee-as C objects.

Binutils changed EABI to use the **N32/N64 register-name table** (where
$t0-$t3 == $12-$15 and $t4-$t7 do not exist).  Under that table the EE asm
either mis-encodes (e.g. $t0 -> $12 instead of $8) or fails outright on
$t4-$t7 ("invalid operands").

The fix that reproduces the old bytes exactly:
  * assemble with ``-mabi=o64`` instead of ``-mabi=eabi`` — o64 keeps the O32
    register-name table *and* allows the 64-bit / MMI ops the EE needs, so the
    ``.text`` is byte-identical to the 2.42 ``-mabi=eabi`` output (verified
    across all 3655 monolithic fragments);
  * then rewrite the object's EF_MIPS_ABI field from o64 (0x2000) to eabi64
    (0x4000) so ld merges it with the eabi64 C objects and the linked image
    keeps matching retail.

This shim is a no-op on toolchains where ``-mabi=eabi`` already produces the
right bytes (the e_flags rewrite is idempotent: eabi64 -> eabi64).
"""
from __future__ import annotations

import os
import struct
import subprocess
import sys

REAL_AS = os.environ.get("MIPSEL_AS_REAL", "mipsel-linux-gnu-as")

EF_MIPS_ABI_MASK = 0x0000F000
EF_MIPS_ABI_O64 = 0x00002000
EF_MIPS_ABI_EABI64 = 0x00004000


def _patch_eabi64(obj_path: str) -> None:
    """Rewrite EF_MIPS_ABI in a 32-bit ELF e_flags field to eabi64."""
    with open(obj_path, "r+b") as f:
        ident = f.read(16)
        if ident[:4] != b"\x7fELF" or ident[4] != 1:  # ELFCLASS32 only
            return
        little = ident[5] == 1
        end = "<" if little else ">"
        # e_flags is at offset 0x24 in the 32-bit ELF header.
        f.seek(0x24)
        (flags,) = struct.unpack(end + "I", f.read(4))
        new = (flags & ~EF_MIPS_ABI_MASK) | EF_MIPS_ABI_EABI64
        if new != flags:
            f.seek(0x24)
            f.write(struct.pack(end + "I", new))


def main(argv: list[str]) -> int:
    args = ["-mabi=o64" if a == "-mabi=eabi" else a for a in argv]
    rc = subprocess.run([REAL_AS, *args]).returncode
    if rc != 0:
        return rc
    # locate -o OUTPUT and patch its ABI flag
    out = None
    for i, a in enumerate(args):
        if a == "-o" and i + 1 < len(args):
            out = args[i + 1]
        elif a.startswith("-o") and len(a) > 2:
            out = a[2:]
    if out and os.path.exists(out):
        _patch_eabi64(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
