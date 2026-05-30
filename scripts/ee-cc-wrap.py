#!/usr/bin/env python3
"""ee-gcc 2.96 driver replacement for matching decompilation of God Hand.

The SCE PS2 SDK 3.0.20 ``ee-gcc`` driver shipped in
``decompme/compilers / ee-gcc2.96.tar.xz`` segfaults on this host's kernel
during its fork+exec to ``cc1``.  The crash happens inside the forked child
*before* ``execve("cc1", …)`` is called, so the parent driver mis-reports it
as "Internal error: Segmentation fault (program cc1)".

The fix is to invoke the sub-binaries directly:

    cpp0  → preprocesses .c/.cc into .i  (preserves comments and #line info)
    cc1   → compiles .i into .s          (cc1 for C, cc1plus for C++)
    ee-as → assembles .s into .o         (SCE EE assembler, produces eabi64)

This script mirrors a small subset of the ``gcc`` command-line interface,
sufficient for the matching-decomp build:

    ee-cc-wrap.py [-x c|c++] -c [-o OUT.o] [-O0|-O2|...] [-g] [-G N]
                  [-Dname[=val]]... [-Iincludedir]... [--print-stage]...
                  [--compiler {cygnus-2.96,sn-2.95.3-136}]
                  INPUT.c

If ``--print-stage`` is given, prints the intermediate file paths instead of
deleting them — handy when diffing assembly during matching work.

``--compiler`` selects which cc1 frontend is invoked.
Default = ``cygnus-2.96`` (this wrapper's native path, back-compat with
every existing TU).  ``sn-2.95.3-136`` re-execs ``scripts/sn-cc-wrap.py``
with equivalent arguments — the SN ee-gcc cc1 (Win32 PE, runs under
wibo) emits the ``sq`` callee-save shape retail needs for the
sq-prologue failure-mode group.  Both wrappers share the Cygnus 2.96
cpp0 preprocessor and the Cygnus ee-as 2.10 assembler so the resulting
.o ELF flags (0x20924001, eabi64) match retail regardless of which cc1
produced the intermediate .s.
"""
from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
COMPILER = ROOT / "compiler" / "linux" / "ee" / "gcc"
GCCLIB_PREFIX = COMPILER / "lib" / "gcc-lib" / "ee" / "2.96-ee-001003-1"

CPP0 = GCCLIB_PREFIX / "cpp0"
CC1 = GCCLIB_PREFIX / "cc1"
CC1PLUS = GCCLIB_PREFIX / "cc1plus"
EE_AS = COMPILER / "bin" / "ee-as"
EE_DVP_AS = COMPILER / "bin" / "ee-dvp-as"

# Capture the cwd at import time.  compile.py invokes us with cwd=repo root,
# which is splat's `base_path` — the directory that splat's auto-generated
# `.include "include/<file>.inc"` paths in `include/include_asm.h` are
# resolved relative to.  We pass this as an -I to ee-as below so its
# `.include` resolver finds those files even though we run ee-as from a
# tempdir (for `.mdebug` determinism).  Doing it here, before any tempdir
# chdir, keeps the value stable regardless of subprocess plumbing.
LAUNCH_CWD = Path.cwd().resolve()

# Match the predefined macros the original SCE ee-gcc driver passes to cc1.
# Sourced from `ee-gcc -v -c trivial.c` on this very host before the driver
# crashed; verified with `cpp0 -dM -E /dev/null`.
SCE_EE_PREDEFINES = [
    "-D__GNUC__=2",
    "-D__GNUC_MINOR__=96",
    "-D__GNUC_PATCHLEVEL__=0",
    "-Dmips",
    "-DMIPSEL",
    "-DR5900",
    "-D_mips",
    "-D_MIPSEL",
    "-D_R5900",
    "-D__ee__",
    "-D__mips__",
    "-D__MIPSEL__",
    "-D__R5900__",
    "-D__mips",
    "-D__MIPSEL",
    "-D__R5900",
    "-D__LANGUAGE_C",
    "-D_LANGUAGE_C",
    "-DLANGUAGE_C",
    "-D__SIZE_TYPE__= unsigned int",
    "-D__PTRDIFF_TYPE__= int",
    "-D__LONG_MAX__=9223372036854775807L",
    "-U__mips",
    "-D__mips=3",
    "-D__mips64",
    "-D__mips_eabi",
    "-D__mips_single_float",
]


def die(msg: str, code: int = 1) -> None:
    print(f"ee-cc-wrap: {msg}", file=sys.stderr)
    sys.exit(code)


def run(cmd: list[str], stage: str, cwd: Path | None = None) -> None:
    """Run a subprocess and abort on non-zero exit.

    *cwd*: optional working directory.  Used by the cpp0/cc1/ee-as path
    to invoke each stage with a stable basename input so the .mdebug
    section ee-as writes into the .o doesn't capture the random tempdir
    path (which would break build reproducibility).
    """
    try:
        result = subprocess.run(cmd, check=False, cwd=str(cwd) if cwd else None)
    except FileNotFoundError as exc:
        die(f"{stage}: missing binary {exc.filename!r}")
    if result.returncode != 0:
        die(
            f"{stage} failed (exit {result.returncode}): "
            + " ".join(shlex_safe(arg) for arg in cmd),
            result.returncode,
        )


def shlex_safe(arg: str) -> str:
    """Shell-quote *arg* for diagnostic printing only."""
    if not arg or any(c in arg for c in " \t\n\"'$`\\"):
        return "'" + arg.replace("'", "'\\''") + "'"
    return arg


def parse_args(argv: list[str]) -> argparse.Namespace:
    p = argparse.ArgumentParser(
        prog="ee-cc-wrap",
        description="ee-gcc 2.96 driver replacement (matching-decomp build glue)",
    )
    p.add_argument("input", type=Path, help="Input .c / .cc / .cpp / .i / .s file")
    p.add_argument("-c", action="store_true", help="Compile to .o (the only mode supported)")
    p.add_argument("-o", dest="output", type=Path, default=None, help="Output .o path")
    p.add_argument(
        "-x",
        choices=("c", "c++"),
        default=None,
        help="Source language override (default: from extension)",
    )
    p.add_argument("-O", dest="optlevel", default="2", help="Optimization level (default: 2)")
    p.add_argument("-g", action="store_true", help="Emit debug info (-gstabs)")
    p.add_argument(
        "-G",
        dest="sdata_thresh",
        type=int,
        default=0,
        help="Small-data threshold (default: 0 — matches original SLUS build)",
    )
    p.add_argument("-D", dest="defines", action="append", default=[], help="Add a -D macro")
    p.add_argument("-U", dest="undefines", action="append", default=[], help="Add a -U macro")
    p.add_argument("-I", dest="includes", action="append", default=[], help="Add an include dir")
    p.add_argument(
        "-W",
        dest="warnings",
        action="append",
        default=[],
        help="Pass a -W warning flag to cc1 (e.g. -Wall, -Werror)",
    )
    p.add_argument(
        "-f",
        dest="features",
        action="append",
        default=[],
        help="Pass a -f compiler feature flag to cc1",
    )
    p.add_argument(
        "--print-stage",
        action="append",
        default=[],
        choices=("i", "s"),
        help="Save .i (preprocessed) and/or .s (assembly) next to the output",
    )
    p.add_argument(
        "--no-line-info",
        action="store_true",
        help="Strip absolute paths from cpp0 #line directives (for reproducible builds)",
    )
    p.add_argument(
        "--compiler",
        choices=("cygnus-2.96", "sn-2.95.3-136"),
        default="cygnus-2.96",
        help=(
            "Which cc1 frontend to invoke. 'cygnus-2.96' "
            "(default) keeps today's behaviour; 'sn-2.95.3-136' dispatches "
            "to scripts/sn-cc-wrap.py for the sq-prologue group. cpp0 + "
            "ee-as stages stay shared."
        ),
    )
    return p.parse_args(argv)


def detect_language(src: Path, override: str | None) -> str:
    if override:
        return override
    ext = src.suffix.lower()
    if ext in (".cc", ".cpp", ".cxx", ".c++"):
        return "c++"
    if ext in (".c", ".i"):
        return "c"
    if ext in (".ii",):
        return "c++"
    die(f"cannot detect language for {src!r} (use -x c or -x c++)")
    return "c"  # unreachable, satisfies type checker


def _dispatch_sn(argv: list[str]) -> int:
    """Re-exec scripts/sn-cc-wrap.py with the same args (minus our
    ``--compiler`` flag, which sn-cc-wrap.py doesn't understand).

    The per-TU override lives in compile_config.json and is forwarded
    to *this* wrapper by ``compile.py::_cc``.  When the TU asks for SN,
    the cleanest dispatch is to hand the whole invocation to
    sn-cc-wrap.py — it already runs the same Cygnus cpp0 + Cygnus ee-as
    backend this wrapper does, and the cc1 stage is the only real
    difference (SN cc1.exe via wibo vs. Cygnus cc1).  Keeping the two
    wrappers as siblings (rather than inlining SN here) preserves
    sn-cc-wrap.py as the canonical SN entry point that
    ``scripts/setup_toolchain.sh`` § 5b's smoke test exercises.
    """
    sn_wrap = ROOT / "scripts" / "sn-cc-wrap.py"
    if not sn_wrap.exists():
        die(f"sn-cc-wrap.py missing at {sn_wrap} — run setup_toolchain.sh")
    # Strip --compiler=... / --compiler X tokens before forwarding.
    forwarded: list[str] = []
    skip = False
    for tok in argv:
        if skip:
            skip = False
            continue
        if tok == "--compiler":
            skip = True
            continue
        if tok.startswith("--compiler="):
            continue
        forwarded.append(tok)
    try:
        result = subprocess.run(
            [sys.executable, str(sn_wrap), *forwarded], check=False,
        )
    except FileNotFoundError as exc:
        die(f"sn-cc-wrap dispatch: missing binary {exc.filename!r}")
    return result.returncode


def main(argv: list[str]) -> int:
    args = parse_args(argv)

    if args.compiler == "sn-2.95.3-136":
        # Dispatch the SN path before any Cygnus-specific argument
        # validation so a TU opted into SN never trips this wrapper's
        # cygnus-flavoured checks.
        return _dispatch_sn(argv)

    if not args.c:
        die("only -c (compile-only) is supported; linking is handled by compile.py")

    if not args.input.exists():
        die(f"input not found: {args.input}")

    output = args.output or args.input.with_suffix(".o")
    output.parent.mkdir(parents=True, exist_ok=True)

    if not COMPILER.is_dir():
        die(f"toolchain missing: {COMPILER} (run scripts/setup_toolchain.sh)")

    language = detect_language(args.input, args.x)
    cc1_bin = CC1PLUS if language == "c++" else CC1

    src_ext = args.input.suffix.lower()
    is_assembly = src_ext == ".s"
    is_preprocessed = src_ext in (".i", ".ii")

    with tempfile.TemporaryDirectory(prefix="ee-cc-wrap.") as td:
        td_path = Path(td)
        stem = args.input.stem

        i_name = f"{stem}.i"
        s_name = f"{stem}.s"
        i_path = td_path / i_name
        s_path = td_path / s_name

        # We invoke cc1 and ee-as with cwd=td_path and pass *basenames*
        # (i_name, s_name) instead of absolute paths.  ee-as embeds the
        # .s filename into the .o's `.mdebug` section as a .file directive;
        # any path component (e.g. the random tempdir suffix) becomes part
        # of the .o byte stream and breaks build reproducibility across
        # invocations.  Passing a stable basename keeps `.mdebug` content
        # deterministic so `--reseed-expected` produces a stable baseline.
        # (Discovered when src/cod/000000.o diverged from its
        # expected/build mirror at offset 0x14d on every clean rebuild.)

        # Stage 1: preprocess (skipped for .s and .i inputs)
        if not is_assembly and not is_preprocessed:
            cpp_cmd = [
                str(CPP0),
                f"-lang-{language}",
                *SCE_EE_PREDEFINES,
                *(f"-D{d}" for d in args.defines),
                *(f"-U{u}" for u in args.undefines),
                *(f"-I{i}" for i in args.includes),
            ]
            if args.no_line_info:
                cpp_cmd.append("-P")
            cpp_cmd += [str(args.input), i_name]
            run(cpp_cmd, "cpp0", cwd=td_path)
        elif is_preprocessed:
            shutil.copy2(args.input, i_path)

        # Stage 2: compile (skipped for .s input)
        if not is_assembly:
            cc1_cmd = [
                str(cc1_bin),
                "-quiet",
                f"-lang-{language}",
                "-mips3",
                f"-O{args.optlevel}",
                f"-G{args.sdata_thresh}",
                *args.warnings,
                *args.features,
            ]
            if args.g:
                cc1_cmd.append("-gstabs")
            cc1_cmd += [i_name, "-o", s_name]
            run(cc1_cmd, "cc1", cwd=td_path)
        else:
            shutil.copy2(args.input, s_path)

        # Stage 3: assemble
        as_cmd = [
            str(EE_AS),
            "-EL",
            "-mips3",
            "-mcpu=5900",
            # -mabi=eabi makes ee-as emit ELF flag 0x4000 (eabi64), matching the
            # original SLUS_215.03 main ELF header flags (0x20924001).  Without
            # this we get 0x20920001 (no eabi64 bit) and objdiff scoring drifts.
            "-mabi=eabi",
            f"-G{args.sdata_thresh}",
        ]
        # Forward -I include search paths to ee-as too.  INCLUDE_ASM(folder,
        # name) expands to `.include "folder/name.s"`; ee-as resolves that
        # through its own -I list (same as cpp0's -I list for #include).
        # Standard gcc-driver behaviour; needed for carving where
        # `.include "nonmatching/<name>.s"` resolves under build/asm/.
        for inc in args.includes:
            as_cmd.append(f"-I{inc}")
        # Additionally pass the *launch cwd* (= compile.py's cwd, i.e. the
        # repo root) as an -I to ee-as only.  splat's auto-generated
        # `include/include_asm.h` emits `.include "include/labels.inc"` and
        # `.include "include/macro.inc"` — paths that assume the assembler
        # runs with cwd=base_path (the splat convention).  We deliberately
        # run ee-as with cwd=tempdir to stabilize `.mdebug`'s `.file`
        # directive, which breaks that cwd-relative resolution.
        # Adding the launch cwd to ee-as's search path restores splat's
        # assumption without polluting cpp0's #include search path, and
        # without requiring a hand-edit of `include/include_asm.h` that
        # splat would stomp on every `splat split`.
        as_cmd.append(f"-I{LAUNCH_CWD}")
        if args.g:
            as_cmd.append("--gstabs")
        as_cmd += [s_name, "-o", str(output)]
        run(as_cmd, "ee-as", cwd=td_path)

        # Optional: side-export intermediates for diff sessions
        if "i" in args.print_stage and not is_assembly:
            shutil.copy2(i_path, output.with_suffix(".i"))
        if "s" in args.print_stage and not is_assembly:
            shutil.copy2(s_path, output.with_suffix(".s"))

    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
