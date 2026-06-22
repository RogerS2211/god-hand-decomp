#!/usr/bin/env python3
"""
re4ps2_fingerprint.py  --  same-architecture byte-fingerprint matcher.

Find God Hand (GH) functions that are byte-portable / near-identical to
Resident Evil 4 PS2 (RE4) functions.  Both games are PS2 MIPS R5900
little-endian, built with ee-gcc, so machine code is directly comparable.

Method
------
For every function we build two signatures over its instruction word stream:

  * EXACT  : the raw 32-bit words (catches truly byte-identical ports).
  * MASKED : each word with relocation / position-sensitive fields zeroed:
               - 26-bit target of  j / jal
               - 16-bit immediate of lui / addiu / ori / lw / sw / lhu /
                 sh / lb / lbu / lh / sb / lwc1 / swc1 / ldc1 / sdc1 / ld /
                 sd / daddiu / lui ... (loads/stores/imm-arith that carry
                 %hi/%lo of a global address)
             Opcode + register fields + (PC-relative) branch offsets are kept,
             because identical code keeps those identical.

Two functions "match" when their instruction counts are equal AND their
MASKED signatures are equal.  If additionally the EXACT signatures are equal,
they are byte-identical.

Inputs
------
  GH  : asm/cod/000000.s            (instruction words embedded in /* .. */)
  RE4 : /tmp/re4ps2/SLUS_211.34     (ELF; .text disassembled from raw words)

Usage
-----
  re4ps2_fingerprint.py [--min-insns N] [--out FILE] [--validate-only]
"""

import argparse
import os
import struct
import sys

# --------------------------------------------------------------------------
# Paths.  Repo root is auto-detected from this file's location; the RE4 ELF
# and the optional GH reflection map come from the environment so the tool is
# portable (RE4 is third-party data and lives outside the repo).
#   GODHAND_REPO       override the auto-detected repo root
#   GODHAND_RE4_ELF    path to the RE4 PS2 ELF (SLUS-21134)
#   GODHAND_GH_REFLECT optional name->addr map for nicer GH names
# --------------------------------------------------------------------------
REPO = os.environ.get(
    "GODHAND_REPO",
    os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
)
GH_ASM = os.path.join(REPO, "asm/cod/000000.s")
RE4_ELF = os.environ.get("GODHAND_RE4_ELF", "/tmp/re4ps2/SLUS_211.34")

# RE4 LOAD segment (from `objdump -p`):  off 0x1000 vaddr 0x100000 filesz 0x2c9f28
RE4_LOAD_OFF = 0x1000
RE4_LOAD_VADDR = 0x00100000
RE4_LOAD_FILESZ = 0x002C9F28
# .text section (from `objdump -h`): vaddr 0x100000 fileoff 0x1000 size 0x1ef91c
RE4_TEXT_VADDR = 0x00100000
RE4_TEXT_FILEOFF = 0x1000
RE4_TEXT_SIZE = 0x1EF91C
RE4_TEXT_END = RE4_TEXT_VADDR + RE4_TEXT_SIZE

GH_REFLECT = os.environ.get("GODHAND_GH_REFLECT", "/tmp/gh_reflect_map.txt")

# Known shared mangled names (verified seeds).  RE4 stores the mangled form;
# the God Hand asm listing uses the demangled-ish label, so we key the GH side
# by its known vaddr (provided) rather than the name.
KNOWN_NAMES = ["Rnd__Fv", "Trans__Fv", "fRand0_1__Fv", "fRand1_1__Fv"]
KNOWN_GH_ADDR = {
    "Rnd__Fv": 0x0031CEF8,
    "Trans__Fv": 0x0015FBA8,
    "fRand0_1__Fv": 0x0031D000,
    "fRand1_1__Fv": 0x0031D020,
}


# --------------------------------------------------------------------------
# MIPS masking
# --------------------------------------------------------------------------
# Primary opcodes (bits 31..26) whose 16-bit immediate is a relocation
# candidate (global %hi/%lo or absolute constant).  Branch opcodes are
# deliberately EXCLUDED so their PC-relative offsets stay in the signature.
IMM16_OPCODES = {
    0x08,  # addi
    0x09,  # addiu
    0x0A,  # slti
    0x0B,  # sltiu
    0x0C,  # andi
    0x0D,  # ori
    0x0E,  # xori
    0x0F,  # lui
    0x18,  # daddi
    0x19,  # daddiu
    0x20,  # lb
    0x21,  # lh
    0x22,  # lwl
    0x23,  # lw
    0x24,  # lbu
    0x25,  # lhu
    0x26,  # lwr
    0x27,  # lwu
    0x28,  # sb
    0x29,  # sh
    0x2A,  # swl
    0x2B,  # sw
    0x2C,  # sdl
    0x2D,  # sdr
    0x2E,  # swr
    0x30,  # ll / lwc0
    0x31,  # lwc1
    0x34,  # ldc0 / lld
    0x35,  # ldc1
    0x36,  # ld (lqc2 region varies; treat as imm)
    0x37,  # ld
    0x38,  # sc / swc0
    0x39,  # swc1
    0x3C,  # sdc0 / scd
    0x3D,  # sdc1
    0x3E,  # sq / sdc2 region
    0x3F,  # sd
    0x1E,  # lq (R5900)
}

# andi/ori/xori/slti/sltiu carry true immediate *constants* far more often
# than relocations; but they may still hold %lo of an address in rare cases.
# Masking their immediate is safe for structural matching (we keep opcode+regs)
# and avoids false negatives, so we mask all IMM16_OPCODES.

OPC_J = 0x02
OPC_JAL = 0x03


def mask_word(w):
    """Return the relocation-masked form of a 32-bit instruction word."""
    op = (w >> 26) & 0x3F
    if op == OPC_J or op == OPC_JAL:
        return w & 0xFC000000  # keep opcode, zero 26-bit target
    if op in IMM16_OPCODES:
        return w & 0xFFFF0000  # keep opcode+rs+rt, zero 16-bit immediate
    return w  # R-type, branches, coproc ops: keep verbatim


def is_return(w):
    return w == 0x03E00008  # jr ra


# --------------------------------------------------------------------------
# God Hand: parse instruction words straight out of the asm listing.
# Each instruction line: "/* OFFSET VADDR BYTES */  mnemonic ..."
# BYTES is the little-endian retail word in hex (e.g. 3005828C).
# Functions run from `glabel <name>` to the matching `endlabel`.
# --------------------------------------------------------------------------
def parse_gh_functions(path):
    funcs = []  # (vaddr, name, [words])
    cur_name = None
    cur_vaddr = None
    cur_words = []
    in_func = False
    with open(path, "r", errors="replace") as f:
        for line in f:
            s = line.strip()
            if s.startswith("glabel "):
                cur_name = s.split(None, 1)[1].strip()
                cur_words = []
                cur_vaddr = None
                in_func = True
                continue
            if s.startswith("endlabel"):
                if in_func and cur_words:
                    funcs.append((cur_vaddr, cur_name, cur_words))
                in_func = False
                cur_name = None
                cur_words = []
                cur_vaddr = None
                continue
            if not in_func:
                continue
            # instruction line
            if s.startswith("/*"):
                end = s.find("*/")
                if end < 0:
                    continue
                fields = s[2:end].split()
                # fields = [OFFSET, VADDR, BYTES]
                if len(fields) < 3:
                    continue
                try:
                    vaddr = int(fields[1], 16)
                    raw = fields[2]
                    if len(raw) != 8:
                        continue
                    # BYTES is little-endian bytes as written; convert to word.
                    b = bytes.fromhex(raw)
                    w = struct.unpack("<I", b)[0]
                except ValueError:
                    continue
                if cur_vaddr is None:
                    cur_vaddr = vaddr
                cur_words.append(w)
    return funcs


# --------------------------------------------------------------------------
# RE4 helpers
# --------------------------------------------------------------------------
def re4_off2vaddr(o):
    if RE4_LOAD_OFF <= o < RE4_LOAD_OFF + RE4_LOAD_FILESZ:
        return o - RE4_LOAD_OFF + RE4_LOAD_VADDR
    return None


def re4_vaddr2off(v):
    o = v - RE4_LOAD_VADDR + RE4_LOAD_OFF
    if RE4_LOAD_OFF <= o < RE4_LOAD_OFF + RE4_LOAD_FILESZ:
        return o
    return None


def load_re4_text(elf_bytes):
    """Return dict vaddr->word for the whole .text, plus ordered vaddr list."""
    words = {}
    base = RE4_TEXT_FILEOFF
    for i in range(0, RE4_TEXT_SIZE, 4):
        w = struct.unpack_from("<I", elf_bytes, base + i)[0]
        words[RE4_TEXT_VADDR + i] = w
    return words


def parse_re4_reflection(elf_bytes):
    """
    Recover RE4 name->code-addr table.

    The reflection table stores, for each entry, a 4-byte LE pointer to the
    mangled name string immediately followed by a 4-byte LE code pointer into
    .text.  We locate it by: find each standalone (NUL-preceded, NUL-followed)
    mangled-name string, compute its vaddr, search the image for a 4-byte LE
    word equal to that vaddr, and read the following word as the code pointer
    (validated to be in .text range).
    """
    name2addr = {}
    # Scan all C-strings that look like mangled symbols ("__" inside) and try
    # to resolve them through the pointer table.  To keep it bounded we collect
    # every NUL-terminated ascii run that contains "__".
    n = len(elf_bytes)
    i = 0
    candidates = []  # (str_vaddr, name)
    while i < n:
        # find next plausible string start
        c = elf_bytes[i]
        if 33 <= c < 127:
            j = i
            while j < n and 32 <= elf_bytes[j] < 127:
                j += 1
            if j < n and elf_bytes[j] == 0 and (i == 0 or elf_bytes[i - 1] == 0):
                run = elf_bytes[i:j]
                if b"__" in run and 3 <= len(run) <= 200:
                    v = re4_off2vaddr(i)
                    if v is not None:
                        candidates.append((v, run.decode("latin1")))
            i = j + 1
        else:
            i += 1

    # Build an index of every 4-byte word in the file -> list of file offsets
    # would be huge; instead, for each candidate search directly.  To keep the
    # broad scan fast we only resolve the candidates we actually need; here we
    # resolve all, but cache the raw file for find().
    raw = elf_bytes
    for v, name in candidates:
        needle = struct.pack("<I", v)
        pos = raw.find(needle)
        # take the first hit that is followed by an in-text code pointer
        while pos >= 0:
            cp = struct.unpack_from("<I", raw, pos + 4)[0]
            if RE4_TEXT_VADDR <= cp < RE4_TEXT_END:
                # prefer first valid; many names appear once
                if name not in name2addr:
                    name2addr[name] = cp
                break
            pos = raw.find(needle, pos + 1)
    return name2addr


def split_re4_functions(words):
    """
    Carve RE4 .text into functions using ee-gcc return convention.

    A function ends at `jr ra` plus its (single) delay-slot instruction.
    The next function begins at the following word, skipping any alignment
    `nop`s.  This mirrors how the GH listing is bounded.  We also begin a
    new function whenever a referenced jal/j target or reflection address
    is known to start one, but boundary-by-return is sufficient and robust
    for fingerprint matching of leaf/normal functions.
    """
    addrs = sorted(words.keys())
    funcs = []  # (start_vaddr, [words])
    start = None
    cur = []
    pending_end = False  # saw jr ra, consuming delay slot next
    for a in addrs:
        if start is None:
            start = a
        w = words[a]
        cur.append(w)
        if pending_end:
            # this word was the delay slot; function ends here
            funcs.append((start, cur))
            cur = []
            start = None
            pending_end = False
            continue
        if is_return(w):
            pending_end = True
    if cur and start is not None:
        funcs.append((start, cur))

    # Trim leading/trailing alignment nops that belong to padding, and set
    # the real start to the first non-nop word.
    cleaned = []
    for start, ws in funcs:
        if start is None:
            continue
        # strip trailing nops
        while ws and ws[-1] == 0:
            ws = ws[:-1]
        # strip leading nops, advancing start
        lead = 0
        while lead < len(ws) and ws[lead] == 0:
            lead += 1
        if lead:
            start = start + 4 * lead
            ws = ws[lead:]
        if ws:
            cleaned.append((start, ws))
    return cleaned


# --------------------------------------------------------------------------
# Signatures
# --------------------------------------------------------------------------
def exact_sig(words):
    return tuple(words)


def masked_sig(words):
    return tuple(mask_word(w) for w in words)


# --------------------------------------------------------------------------
# objdump helper (for side-by-side display only)
# --------------------------------------------------------------------------
def objdump_range(start, end):
    import subprocess

    for mflag in (["-m", "mips:5900"], []):
        try:
            out = subprocess.check_output(
                ["mipsel-linux-gnu-objdump", "-d", "-EL"]
                + mflag
                + [
                    "--start-address=0x%X" % start,
                    "--stop-address=0x%X" % end,
                    RE4_ELF,
                ],
                stderr=subprocess.DEVNULL,
            ).decode("latin1")
            lines = [
                l.rstrip()
                for l in out.splitlines()
                if "\t" in l and ":" in l.split("\t")[0]
            ]
            if lines:
                return lines
        except Exception:
            continue
    return []


# --------------------------------------------------------------------------
# Main
# --------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument(
        "--min-insns",
        type=int,
        default=4,
        help="ignore functions with fewer instructions than this (default 4)",
    )
    ap.add_argument("--out", default=None, help="write candidate table to file")
    ap.add_argument(
        "--validate-only",
        action="store_true",
        help="only run the 4-known-function validation",
    )
    ap.add_argument(
        "--max-candidates",
        type=int,
        default=10_000,
        help="cap on printed/written candidates",
    )
    args = ap.parse_args()

    elf = open(RE4_ELF, "rb").read()

    # ---- Load GH ----
    print("[*] parsing God Hand functions from asm ...", file=sys.stderr)
    gh_funcs = parse_gh_functions(GH_ASM)
    print("    GH functions: %d" % len(gh_funcs), file=sys.stderr)

    # GH reflection map (addr-hex -> demangled)  for nicer names
    gh_name_by_addr = {}
    if os.path.exists(GH_REFLECT):
        for line in open(GH_REFLECT, errors="replace"):
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 2:
                try:
                    a = int(parts[0], 16)
                except ValueError:
                    continue
                gh_name_by_addr[a] = parts[1]

    # ---- Load RE4 ----
    print("[*] disassembling RE4 .text ...", file=sys.stderr)
    re4_words = load_re4_text(elf)
    print("[*] recovering RE4 reflection table ...", file=sys.stderr)
    re4_name2addr = parse_re4_reflection(elf)
    print("    RE4 named symbols: %d" % len(re4_name2addr), file=sys.stderr)

    print("[*] carving RE4 functions ...", file=sys.stderr)
    re4_funcs = split_re4_functions(re4_words)
    print("    RE4 carved functions: %d" % len(re4_funcs), file=sys.stderr)

    re4_addr2name = {v: k for k, v in re4_name2addr.items()}

    # ============================================================
    # VALIDATION on the 4 known shared functions
    # ============================================================
    gh_by_addr = {v: (n, w) for (v, n, w) in gh_funcs}
    gh_by_name = {n: (v, w) for (v, n, w) in gh_funcs}

    print("\n" + "=" * 72)
    print("VALIDATION  --  4 known shared functions")
    print("=" * 72)
    re4_word_at = re4_words

    def re4_func_words(start):
        # find carved function beginning exactly at start
        for s, ws in re4_funcs:
            if s == start:
                return ws
        return None

    shown_disasm = False
    for name in KNOWN_NAMES:
        gh_vaddr = KNOWN_GH_ADDR.get(name)
        ghentry = gh_by_addr.get(gh_vaddr) if gh_vaddr is not None else None
        re4addr = re4_name2addr.get(name)
        print("\n--- %s ---" % name)
        if ghentry is None:
            print("  GH: NOT FOUND at expected vaddr 0x%08X" % (gh_vaddr or 0))
            continue
        gh_label, gh_words = ghentry
        print("  GH label in asm: %s" % gh_label)
        print("  GH  @ 0x%08X  (%d insns)" % (gh_vaddr, len(gh_words)))
        if re4addr is None:
            print("  RE4: name not resolved in reflection table")
            continue
        re4_words_f = re4_func_words(re4addr)
        if re4_words_f is None:
            # carve directly from start until return+delay
            re4_words_f = []
            a = re4addr
            pend = False
            while a in re4_word_at and a < RE4_TEXT_END:
                w = re4_word_at[a]
                re4_words_f.append(w)
                if pend:
                    break
                if is_return(w):
                    pend = True
                a += 4
        print("  RE4 @ 0x%08X  (%d insns)" % (re4addr, len(re4_words_f)))

        verdict = compare(gh_words, re4_words_f)
        print("  VERDICT: %s" % verdict)

        if not shown_disasm or name == "Rnd__Fv":
            print("  side-by-side (GH word | RE4 word | masked-equal):")
            mx = max(len(gh_words), len(re4_words_f))
            for i in range(mx):
                gw = gh_words[i] if i < len(gh_words) else None
                rw = re4_words_f[i] if i < len(re4_words_f) else None
                meq = (
                    "="
                    if gw is not None
                    and rw is not None
                    and mask_word(gw) == mask_word(rw)
                    else "x"
                )
                print(
                    "    %2d  %s   %s   %s"
                    % (
                        i,
                        "        " if gw is None else "%08X" % gw,
                        "        " if rw is None else "%08X" % rw,
                        meq,
                    )
                )
            shown_disasm = True

    if args.validate_only:
        return

    # ============================================================
    # BROAD SCAN
    # ============================================================
    print("\n" + "=" * 72)
    print("BROAD SCAN  --  GH functions with a fingerprint-identical RE4 twin")
    print("=" * 72)

    # Index RE4 by masked signature -> list of (addr, words)
    re4_index = {}
    for s, ws in re4_funcs:
        if len(ws) < args.min_insns:
            continue
        re4_index.setdefault(masked_sig(ws), []).append((s, ws))

    re4_exact_index = {}
    for s, ws in re4_funcs:
        if len(ws) < args.min_insns:
            continue
        re4_exact_index.setdefault(exact_sig(ws), []).append(s)

    candidates = []  # (gh_addr, gh_name, re4_addr, verdict, ninsns)
    for gh_vaddr, gh_name, gh_words in gh_funcs:
        if gh_vaddr is None or len(gh_words) < args.min_insns:
            continue
        ms = masked_sig(gh_words)
        hits = re4_index.get(ms)
        if not hits:
            continue
        # pick best hit; prefer one that is also exact-identical
        es = exact_sig(gh_words)
        exact_hits = re4_exact_index.get(es, [])
        if exact_hits:
            re4_addr = exact_hits[0]
            verdict = "byte-identical"
        else:
            re4_addr = hits[0][0]
            verdict = "fingerprint-identical"
        nm = re4_addr2name.get(re4_addr, "")
        candidates.append(
            (gh_vaddr, gh_name, re4_addr, verdict, len(gh_words), nm)
        )

    # Sort: byte-identical first, then by instruction count desc (bigger =
    # stronger evidence), then address.
    order = {"byte-identical": 0, "fingerprint-identical": 1}
    candidates.sort(key=lambda c: (order[c[3]], -c[4], c[0]))

    n_exact = sum(1 for c in candidates if c[3] == "byte-identical")
    n_fp = sum(1 for c in candidates if c[3] == "fingerprint-identical")
    print(
        "\nGH functions with a fingerprint-identical RE4 counterpart: %d"
        % len(candidates)
    )
    print("  byte-identical        : %d" % n_exact)
    print("  fingerprint-identical : %d" % n_fp)
    print("  (min-insns = %d)" % args.min_insns)

    header = "%-12s %-40s %-12s %-22s %5s  %s" % (
        "GH_addr",
        "GH_name",
        "RE4_addr",
        "verdict",
        "insns",
        "RE4_name",
    )
    print("\n" + header)
    print("-" * len(header))
    lines = []
    for gh_vaddr, gh_name, re4_addr, verdict, n, re4nm in candidates:
        disp = gh_name
        if disp.startswith("func_") and gh_vaddr in gh_name_by_addr:
            disp = gh_name_by_addr[gh_vaddr]
        row = "0x%08X %-40s 0x%08X %-22s %5d  %s" % (
            gh_vaddr,
            disp[:40],
            re4_addr,
            verdict,
            n,
            re4nm,
        )
        lines.append(row)
    for row in lines[: args.max_candidates]:
        print(row)

    if args.out:
        with open(args.out, "w") as fo:
            fo.write(header + "\n")
            for row in lines:
                fo.write(row + "\n")
        print("\n[*] full table written to %s (%d rows)" % (args.out, len(lines)))


def compare(gh_words, re4_words):
    if len(gh_words) != len(re4_words):
        # still report masked-prefix similarity
        same = sum(
            1
            for a, b in zip(
                [mask_word(w) for w in gh_words],
                [mask_word(w) for w in re4_words],
            )
            if a == b
        )
        return "DIFFER (len %d vs %d; %d/%d masked-equal in overlap)" % (
            len(gh_words),
            len(re4_words),
            same,
            min(len(gh_words), len(re4_words)),
        )
    if exact_sig(gh_words) == exact_sig(re4_words):
        return "byte-identical"
    if masked_sig(gh_words) == masked_sig(re4_words):
        return "fingerprint-identical (reloc-masked)"
    # near?
    same = sum(
        1
        for a, b in zip(
            [mask_word(w) for w in gh_words],
            [mask_word(w) for w in re4_words],
        )
        if a == b
    )
    return "DIFFER (%d/%d masked-equal)" % (same, len(gh_words))


if __name__ == "__main__":
    main()
