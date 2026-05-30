#!/usr/bin/env python3
"""
Verify per-REL splat round-trip without invoking the linker.

This is the REL sibling of `scripts/verify_splat_roundtrip.py` for the
main ELF, adapted to SNR2-format REL overlays.  For every REL with a
splat config (currently just r207.rel), we:

  1. Read every splat-emitted bin / asm file in the segment's
     subsegment order.
  2. Re-encode the asm files by walking each line and reading the
     literal hex bytes from the trailing `/* off vaddr HEX */`
     comments (the same trick used for data subsegments in the main-
     ELF round-trip — splat / spimdisasm always emit the original
     bytes in the comment regardless of whether the directive
     reproduces them losslessly).
  3. Concatenate header + asm + tail in subsegment order.
  4. Assert the result is byte-identical to the on-disc SNR2 blob.

If this script reports `PASS`, splat read every byte of the REL and we
have a deterministic recipe to reproduce the original bytes from the
split-out tree.  That is the property the REL build path leans on when
wiring `compile.py --rel r207` to actually compile + link + SNR2-wrap.

Exits 0 on byte-perfect round-trip of every configured REL, 1
otherwise.  Skips with exit 77 if no REL splat output exists yet
(so `scripts/checks/rel-splat.sh` can defer cleanly until the REL
splat has actually run).
"""
from __future__ import annotations

import hashlib
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# ---------------------------------------------------------------------------
# REL registry. Each entry describes the on-disc REL and the splat-output
# files that together must re-encode it. `parts` is an ordered list of
# (kind, path, expected_byte_length) tuples where kind is one of:
#
#   "bin"  — splat-emitted .bin file, written verbatim
#   "asm"  — splat-emitted .s file, decoded via rebuild_asm()
#
# This is hand-curated for each REL (small, ~3 entries per REL — the
# SNR2 carve is well-bounded). r207 ships first; later RELs append.
# ---------------------------------------------------------------------------

RELS = [
    {
        "name": "r207.rel",
        "input": ROOT / "disc_extract" / "rel" / "r207.rel",
        "expected_sha256":
            "ea59932301345e48add7a3eff029b7d0d0138fff1abc67569467880678c653c1",
        "parts": [
            ("bin", ROOT / "bin/rel/r207/header.bin", 0x3C),
            ("asm", ROOT / "asm/rel/r207/00003C.s",  0x44C),
            ("bin", ROOT / "bin/rel/r207/tail.bin",  0x230),
        ],
    },
]


# ---------------------------------------------------------------------------
# Asm-file → bytes re-encoder. Same idea as the main-ELF roundtrip's
# rebuild() helper but stripped down: REL splat output only ever uses the
# trailing-HEX form for .text subsegments (no .word/.byte/.short/.asciz
# in this corpus's REL .text), so we don't need the directive-aware
# fall-throughs.  `.align N` is still honored as a safety net (always a
# no-op in MIPS .text where every instruction is 4-byte aligned, but
# spimdisasm emits one after each function — see asm/rel/r207/00003C.s).
# ---------------------------------------------------------------------------

ADDR_HEX_RE = re.compile(
    r"^\s*/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+\*/"
)
BARE_HEX_RE = re.compile(r"^\s*/\*\s+([0-9A-Fa-f]+)\s+\*/\s*$")
ALIGN_RE = re.compile(r"^\s*\.align\s+(\d+)\s*$")


def rebuild_asm(path: Path) -> bytes:
    out = bytearray()

    def align_to(boundary: int) -> None:
        if boundary <= 1:
            return
        rem = len(out) % boundary
        if rem:
            out.extend(b"\x00" * (boundary - rem))

    for line in path.read_text().splitlines():
        m = ADDR_HEX_RE.match(line)
        if m:
            out.extend(bytes.fromhex(m.group(1)))
            continue
        m = BARE_HEX_RE.match(line)
        if m:
            out.extend(bytes.fromhex(m.group(1)))
            continue
        m = ALIGN_RE.match(line)
        if m:
            align_to(1 << int(m.group(1)))
            continue
        # Any other line (.section, .set, glabel, endlabel, nonmatching,
        # labels, comments, blank lines) contributes no bytes.
    return bytes(out)


# ---------------------------------------------------------------------------
# Per-REL check
# ---------------------------------------------------------------------------

def check_one(entry: dict) -> int:
    name = entry["name"]
    src = entry["input"]
    if not src.is_file():
        print(f"  [SKIP] {name}: source missing ({src})")
        return 77

    expect = src.read_bytes()
    actual_sha = hashlib.sha256(expect).hexdigest()
    if actual_sha != entry["expected_sha256"]:
        print(
            f"  [BAD] {name}: source sha256 mismatch "
            f"(expected {entry['expected_sha256'][:16]}…, "
            f"got {actual_sha[:16]}…)"
        )
        return 1

    rebuilt = bytearray()
    for kind, p, expect_len in entry["parts"]:
        if not p.is_file():
            print(f"  [SKIP] {name}: part missing ({p}); run splat first")
            return 77
        if kind == "bin":
            chunk = p.read_bytes()
        elif kind == "asm":
            chunk = rebuild_asm(p)
        else:
            print(f"  [BAD] {name}: unknown part kind {kind!r}")
            return 1
        if len(chunk) != expect_len:
            print(
                f"  [BAD] {name}: part {p.name} size {len(chunk)} != "
                f"expected {expect_len}"
            )
            return 1
        rebuilt.extend(chunk)

    rebuilt = bytes(rebuilt)
    if rebuilt == expect:
        sha = hashlib.sha256(rebuilt).hexdigest()[:16]
        print(
            f"  [OK ] {name}: {len(rebuilt)} B, "
            f"sha={sha}… matches {src.name}"
        )
        return 0

    # Find first diff
    for i, (a, b) in enumerate(zip(rebuilt, expect)):
        if a != b:
            ctx = max(0, i - 8)
            print(
                f"  [BAD] {name}: first diff at off=0x{i:x}: "
                f"rebuilt={a:#04x} ref={b:#04x}  "
                f"context rebuilt={rebuilt[ctx:i+8].hex()} "
                f"ref={expect[ctx:i+8].hex()}"
            )
            break
    if len(rebuilt) != len(expect):
        print(f"  [BAD] {name}: size mismatch rebuilt={len(rebuilt)} ref={len(expect)}")
    return 1


def main() -> int:
    print("Verifying REL splat round-trip")
    rc = 0
    any_run = 0
    for entry in RELS:
        result = check_one(entry)
        if result == 77:
            continue
        any_run += 1
        if result != 0:
            rc = 1
    if any_run == 0:
        print("\nSKIP: no configured REL has been split yet.")
        return 77
    print()
    if rc == 0:
        print(f"PASS: every byte of every configured REL is accounted for "
              f"({any_run} REL{'s' if any_run != 1 else ''}).")
    else:
        print("FAIL: see diagnostics above.")
    return rc


if __name__ == "__main__":
    sys.exit(main())
