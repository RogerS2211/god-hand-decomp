#!/usr/bin/env python3
"""Gap B: verify the `expected/build/` ratchet baseline really
*is* the retail-equal build.

The task as originally drafted asked us to confirm that the section bytes
of every `expected/build/<u>.o` concatenate, in lcf declaration order, to
retail's loaded-section bytes.  That literal check **cannot pass** for a
mechanical reason discovered in session 12: `objcopy -O binary` of an
unlinked `.o` returns the *unrelocated* bytes, where every absolute
address slot is zero.  Retail's `.text`/`.data`/`.rodata`/`.sndata` are
the *relocated* bytes ld wrote after applying the 200k+ entries in
`.rel.<section>`.  So per-section extraction will diverge at the first
relocation site (offset 0x11c in `.text`, ~28k relocations into `.text`
in total).

The *meaningful* invariant — what the task was really pointing at — is:

  the ratchet baseline is exactly the byte-identical build.

That decomposes into two equivalent gates:

  G1 (cheap, primary): `expected/build/<u>.o` is byte-equal to
       `build/<u>.o` produced by the current `python compile.py`,
       for every unit in the lcf.  If G1 holds and the current build
       hashes to retail, the baseline measures retail by transitivity.

  G2 (deep, redundant): link `expected/build/*.o` through the same
       lcf + `elf_postprocess.py` pipeline and confirm the resulting
       ELF hashes to retail (`1742f95b…f3cd`).  Strictly redundant
       given G1, but a useful cross-check that the link itself is
       stable across input-file paths.

This script runs G1 always (fast).  Pass `--deep` to additionally run
G2 (~5 s).  Exits 0 on every gate passing, 1 on any divergence with
sha256 + first-differing-bytes evidence per failure.

For audit transparency, `--show-section-extract-diff` re-runs the
*original* (broken) section-extract comparison and prints the diff,
to make the relocation explanation concrete for future readers.
"""

from __future__ import annotations

import argparse
import hashlib
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RETAIL_ELF = ROOT / "disc_extract" / "SLUS_215.03"
RETAIL_SHA256 = "1742f95bef65bdb2aa57b7a77df4ac7619a092e9646e1ea325bc32ec8a64f3cd"
COMMITTED_LCF = ROOT / "config" / "SLUS_215.03.lcf"
# When carving is active, compile.py emits a build-time copy of
# the lcf at build/SLUS_215.03.lcf with the monolithic .text reference
# replaced by fragment + carve-owner references.  Both gates parse this
# build-time copy in preference to the committed lcf so the invariants
# track whatever the actual link uses.
BUILD_LCF = ROOT / "build" / "SLUS_215.03.lcf"
EXPECTED_ROOT = ROOT / "expected" / "build"
BUILD_ROOT = ROOT / "build"


def _active_lcf() -> Path:
    """Return the build-time lcf if carving has produced one, else the
    committed lcf.  Centralised so G1, G2, and the audit demo all agree."""
    return BUILD_LCF if BUILD_LCF.exists() else COMMITTED_LCF

OBJCOPY = "mipsel-linux-gnu-objcopy"

# Same shape as compile.py::_LD_OBJ_RE.
_LD_OBJ_RE = re.compile(
    r"^\s*(build/[A-Za-z0-9_./-]+\.o)\s*\(", re.MULTILINE
)


def _ld_script_objects() -> list[Path]:
    """Return active-lcf objects in declaration order, deduped.  Uses the
    build-time lcf when carving has emitted one, else the committed lcf."""
    seen: set[str] = set()
    out: list[Path] = []
    for m in _LD_OBJ_RE.finditer(_active_lcf().read_text()):
        obj = m.group(1)
        if obj in seen:
            continue
        seen.add(obj)
        out.append(ROOT / obj)
    return out


def _sha256(p: Path) -> str:
    return hashlib.sha256(p.read_bytes()).hexdigest()


def _hexdump(data: bytes, offset: int, width: int = 64) -> str:
    half = width // 2
    lo = max(0, offset - half)
    hi = min(len(data), lo + width)
    parts: list[str] = []
    for i in range(0, hi - lo, 16):
        row = data[lo + i : lo + i + 16]
        parts.append(
            f"  {lo + i:08x}  " + " ".join(f"{b:02x}" for b in row)
        )
    return "\n".join(parts) or "  <empty>"


def check_g1_mirror() -> tuple[bool, list[str]]:
    """G1: each `expected/build/<u>.o` is byte-equal to `build/<u>.o`."""
    failures: list[str] = []
    objs = _ld_script_objects()
    if not objs:
        return False, ["no objects parsed from lcf"]
    for obj in objs:
        rel = obj.relative_to(BUILD_ROOT)
        cur = BUILD_ROOT / rel
        exp = EXPECTED_ROOT / rel
        if not cur.exists():
            failures.append(f"missing current build object: {cur}")
            continue
        if not exp.exists():
            failures.append(f"missing expected object: {exp}")
            continue
        cur_sha = _sha256(cur)
        exp_sha = _sha256(exp)
        if cur_sha != exp_sha:
            failures.append(
                f"{rel}: build={cur_sha} expected={exp_sha}"
            )
            print(f"  ✗ {rel}")
            print(f"    build:    {cur_sha}")
            print(f"    expected: {exp_sha}")
            cur_b = cur.read_bytes()
            exp_b = exp.read_bytes()
            n = min(len(cur_b), len(exp_b))
            first = next(
                (i for i in range(n) if cur_b[i] != exp_b[i]),
                n,
            )
            print(f"    first diff @ 0x{first:x} "
                  f"(cur={len(cur_b)}B exp={len(exp_b)}B)")
            print("    build:")
            print(_hexdump(cur_b, first))
            print("    expected:")
            print(_hexdump(exp_b, first))
        else:
            print(f"  ✓ {rel}  {cur_sha[:12]}…  "
                  f"{cur.stat().st_size:>10} B")
    return not failures, failures


def check_g2_relink_deep() -> tuple[bool, list[str]]:
    """G2: link `expected/build/*.o` through the committed lcf +
    elf_postprocess.py and confirm ELF sha256 = retail.

    Implemented as a ld-only relink (no `as` re-run) against a scratch
    `build/` populated from `expected/build/`.  The committed lcf
    references inputs by relative path (`build/asm/<...>.o`) so we run
    ld from a scratch CWD with the lcf path made absolute and `build/`
    seeded from expected/.  This bypasses `compile.py`'s assembler step,
    which would otherwise overwrite our seeded objects from the
    committed `.s` sources.
    """
    import json as _json
    cfg = _json.loads((ROOT / "compile_config.json").read_text())
    ld = cfg["tools"]["mipsel_ld"]
    linker_flags = cfg.get("linker_flags", [])
    failures: list[str] = []
    with tempfile.TemporaryDirectory(prefix="m2v_gap_b_g2_") as td:
        scratch = Path(td)
        scratch_build = scratch / "build"
        shutil.copytree(EXPECTED_ROOT, scratch_build)
        out_elf = scratch_build / "SLUS_215.03.elf"
        out_map = scratch_build / "SLUS_215.03.map"
        argv = [ld, "-T", str(_active_lcf())]
        argv += linker_flags
        argv += ["-Map", str(out_map), "-o", str(out_elf)]
        r = subprocess.run(
            argv, cwd=scratch, capture_output=True, text=True,
        )
        if r.returncode != 0:
            failures.append(f"ld failed: {r.stderr[-400:]}")
            return False, failures
        # Apply the same post-link patch compile.py applies.
        pp = ROOT / "scripts" / "elf_postprocess.py"
        rp = subprocess.run(
            [sys.executable, str(pp), str(out_elf)],
            capture_output=True, text=True,
        )
        if rp.returncode != 0:
            failures.append(f"elf_postprocess failed: {rp.stderr[-400:]}")
            return False, failures
        sha = _sha256(out_elf)
        if sha != RETAIL_SHA256:
            failures.append(f"relink sha={sha} (want {RETAIL_SHA256})")
            print(f"  ✗ relink-from-expected sha mismatch:")
            print(f"    got:  {sha}")
            print(f"    want: {RETAIL_SHA256}")
        else:
            print(f"  ✓ relink-from-expected ELF sha256={sha}")
    return not failures, failures


def show_section_extract_diff() -> None:
    """For audit: show the section-extract divergence at one site,
    proving the unrelocated-bytes finding from the script header.
    """
    print()
    print("Audit: original (broken) section-extract comparison demo")
    print("-------------------------------------------------------")
    print("Why the literal task-as-drafted check cannot pass: per-")
    print(".o `.text` bytes are unrelocated.  Below is the first")
    print("`.text` divergence between `expected/build/asm/cod/000000.o`")
    print("and retail; the bytes at offset 0x11c are an R_MIPS_HI16")
    print("relocation slot for symbol D_00460D00 (run readelf -r to")
    print("confirm).  This is structural; no expected/build/ change")
    print("can fix it.")
    obj = EXPECTED_ROOT / "asm" / "cod" / "000000.o"
    if not obj.exists():
        print(f"(missing {obj})")
        return
    with tempfile.TemporaryDirectory() as td:
        scratch = Path(td)
        retail_text = scratch / "retail.text.bin"
        exp_text = scratch / "exp.text.bin"
        subprocess.run(
            [OBJCOPY, "-O", "binary", "--only-section", ".text",
             str(RETAIL_ELF), str(retail_text)],
            check=True, capture_output=True,
        )
        subprocess.run(
            [OBJCOPY, "-O", "binary", "--only-section", ".text",
             str(obj), str(exp_text)],
            check=True, capture_output=True,
        )
        r = retail_text.read_bytes()
        e = exp_text.read_bytes()
        n = min(len(r), len(e))
        first = next((i for i in range(n) if r[i] != e[i]), n)
        print(f"  first diff @ 0x{first:x}  retail={len(r)}B exp={len(e)}B")
        print("  retail:")
        print(_hexdump(r, first))
        print("  expected (unrelocated):")
        print(_hexdump(e, first))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--deep", action="store_true",
                    help="also run G2 relink-and-compare (slow)")
    ap.add_argument("--show-section-extract-diff", action="store_true",
                    help="audit: show the relocation-driven divergence "
                         "the original literal check would have hit")
    args = ap.parse_args()

    if not RETAIL_ELF.exists():
        sys.stderr.write(f"missing retail ELF: {RETAIL_ELF}\n")
        return 2
    if not COMMITTED_LCF.exists():
        sys.stderr.write(f"missing committed lcf: {COMMITTED_LCF}\n")
        return 2
    if not EXPECTED_ROOT.exists() or not any(EXPECTED_ROOT.rglob("*.o")):
        sys.stderr.write(
            f"empty/missing {EXPECTED_ROOT}; run `python compile.py --setup` first\n"
        )
        return 2
    if not BUILD_ROOT.exists() or not (BUILD_ROOT / "SLUS_215.03.elf").exists():
        sys.stderr.write(
            f"missing {BUILD_ROOT}/SLUS_215.03.elf; run `python compile.py` first\n"
        )
        return 2
    if not shutil.which(OBJCOPY):
        sys.stderr.write(f"{OBJCOPY} not on PATH\n")
        return 2

    rc = 0
    print("G1 — expected/build/<u>.o byte-equals build/<u>.o:")
    ok1, failures1 = check_g1_mirror()
    if not ok1:
        rc = 1
        print(f"  FAIL ({len(failures1)} divergences)")
    else:
        print("  PASS")

    if args.deep:
        print()
        print("G2 — relink expected/build/*.o → retail-equal ELF:")
        ok2, failures2 = check_g2_relink_deep()
        if not ok2:
            rc = 1
            print(f"  FAIL ({len(failures2)} issues)")
        else:
            print("  PASS")

    if args.show_section_extract_diff:
        show_section_extract_diff()

    print()
    if rc == 0:
        print("PASS: expected/build/ baseline measures retail by transitivity")
        print(f"      (current build/SLUS_215.03.elf sha256 must equal "
              f"{RETAIL_SHA256[:12]}…; verified by `scripts/checks/build.sh`)")
    else:
        print("FAIL: baseline divergence — open a rebase follow-up")
    return rc


if __name__ == "__main__":
    raise SystemExit(main())
