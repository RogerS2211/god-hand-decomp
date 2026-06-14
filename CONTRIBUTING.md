# Contributing — a human's guide to godhand-recomp

This is a **matching decompilation** of *God Hand* (PS2, 2006, Clover Studio /
Capcom). The job is to rewrite the game's machine code as C/C++ that, when
compiled with the original toolchain, produces **byte-for-byte the same** boot
ELF and `.rel` overlays as the retail disc.

Most of the day-to-day driving here runs through an orchestration loop (see
[`AGENTS.md`](./AGENTS.md) / [`ORIENT.md`](./ORIENT.md)), but every step it
takes is a plain command you can run by hand. This document is the
human-facing version of that workflow: how to set up, how to take one function
from "raw asm" to "byte-identical match", and the handful of rules that keep
the build honest.

> **Status.** The repo is solo/private right now and not yet taking outside
> pull requests (see the README). This guide documents the workflow so you can
> reproduce it locally, follow along, and so it's ready the day the project
> opens up. If you want to help and the door is still closed, open an issue
> first.

---

## 1. The mental model (read this before anything else)

You are not "porting" or "rewriting" the game in the loose sense. You are
**reproducing the exact bytes** the original compiler emitted. Two ideas drive
everything:

- **The ratchet.** There is one number that only ever goes up:
  `matched_code_percent` — the fraction of `.text` bytes that compile
  *byte-identical* to retail. Every commit must keep the build reproducing
  retail (`scripts/session_check.sh` enforces this). You never land a change
  that lowers the number or breaks the build.

- **Carving.** The whole game starts as one giant disassembly
  (`asm/cod/000000.s`, the "monolithic"). Functions are pulled out one at a
  time. Until a function is matched, the C source `#include`s its raw assembly
  via `INCLUDE_ASM(...)`. When you match it, the `INCLUDE_ASM` line is replaced
  by real C. This is called **carving** a function.

A function is **matched** when the compiler, fed your C with the project's
exact flags, emits the identical machine code. Not "equivalent" — *identical*,
down to register allocation and instruction order. That's the bar.

You'll see two related metrics:

| Metric | What it means |
|---|---|
| `matched_code_percent` | % of `.text` bytes byte-identical to retail (the ratchet) |
| `matched_functions` | count of functions that match |
| full-ELF sha256 gate | pass/fail: does the whole built ELF still equal retail? |

Current state lives in [`STATE.md`](./STATE.md) (auto-generated — don't
hand-edit the numbers).

---

## 2. One-time setup

You need your own legally-dumped NTSC-U disc. **No game data ships in this
repo** and none should ever be committed.

> **Nix users (optional):** run `nix develop` first — it provisions the compiler,
> wibo, objdiff, and the cross-binutils for you (subsuming step 2 below and the
> step-3 host package), so `setup_toolchain.sh` then only sets up the venv, the
> Python tools, the assembler patches, and the git hooks. See
> [README → Nix dev environment](./README.md#nix-dev-environment-optional). The
> steps below otherwise work unchanged.

```bash
# 1. Put your own dump at the repo root as 'God Hand (USA).iso'.
./scripts/extract_iso.sh            # extracts + sha256-verifies the boot ELF

# 2. Vendor the SCE PS2 SDK 3.0.20 toolchain (ee-gcc 2.96 + SN linker + dvp-as),
#    plus splat / m2c / objdiff / asm-differ / decomp-permuter:
./scripts/setup_toolchain.sh

# 3. One-time host dependency (assembler used by the build):
paru -S mipsel-linux-gnu-binutils   # or your distro's equivalent

# 4. Generate the asm split + objdiff scoring project:
.venv/bin/python compile.py --setup

# 5. Build (an empty matching link to start — every byte comes from re-assembled asm):
.venv/bin/python compile.py         # default version is 'us'

# 6. Sanity-check the tooling:
.venv/bin/python -m pytest tests/   # parsers, carve splitter, mappers — wall < 1 s
.venv/bin/python tools/m2c/m2c.py --help
```

After step 5 you should have a `build/SLUS_215.03.elf` whose sha256 equals the
retail boot ELF. If that holds, your environment is correct. (An "empty" build
already reproduces retail.)

**A note on `.venv`.** All Python tooling runs under the repo's virtualenv.
Prefix Python commands with `.venv/bin/python` (the examples below sometimes
drop it for brevity).

---

## 3. The lay of the land

You'll touch these constantly:

| Path | What it is |
|---|---|
| `asm/cod/000000.s` | the **monolithic** — raw disassembly of the whole game, with retail bytes embedded in each instruction comment |
| `src/cod/*.c` | decompiled C. Each file is a translation unit (TU) holding one or more functions. |
| `include/` | shared headers: `sce/` (SDK), `cri/`, `capcom/`, `gh/` (game) |
| `compile_config.json` | the build manifest: which functions are carved, which compiler each TU uses, per-TU flags |
| `config/symbol_addrs.txt` | name → address map (seeded from Ghidra); where you record names you learn |
| `expected/build/*.o` | the objdiff *target* — disassembled-from-retail object files |
| `compile.py` | the build entry point |
| `objdiff.json` | objdiff scoring project (per-`.o` byte diff) |

These you'll read for orientation:

- [`STATE.md`](./STATE.md) — current truth dashboard
- [`DECISIONS.md`](./DECISIONS.md) — locked architectural decisions (don't relitigate)
- [`STRUCTS.md`](./STRUCTS.md) — known struct layouts
- [`CONTEXT.md`](./CONTEXT.md) — domain glossary
- [`notes/`](./notes/) — recon reports and retros (the "why" behind everything)

**Search hygiene — important.** The repo root holds multi-GB artefacts (the
ISO, `tools/`, `build/`, `asm/`). **Never** run `find /`, `find ~`, or
`grep -r` above the project. Use `git grep` / `rg` from the project root (both
respect `.gitignore` and skip the heavy trees), or `scripts/proj-find.sh` if
you need `find`. This rule is load-bearing — see
[`AGENTS.md`](./AGENTS.md#filesystem-search-hygiene--non-negotiable).

---

## 4. The per-function workflow

This is the core loop. The goal: take one function from `INCLUDE_ASM` to a
byte-identical C match.

### Step 0 — pick a target

Good first targets are **small leaf functions** (no calls, simple control
flow): getters/setters, small constructors, math helpers. Avoid huge
dispatchers and anything with VU0 microcode or 64-bit runtime shifts until
you're comfortable — those hit toolchain-fidelity walls (see
[`STATE.md`](./STATE.md)).

To browse the worklist, the function atlas census is the map:

```bash
.venv/bin/python scripts/function_atlas.py     # -> progress/function_atlas.summary.md
```

Pick a `func_XXXXXXXX` name (the address-based default name) or a name from
`config/symbol_addrs.txt`.

### Step 1 — look at what you're matching

The retail bytes and disassembly for any function come straight out of the
monolithic. The fast oracle dumps them for you:

```bash
.venv/bin/python scripts/score_candidate.py func_002772A8 --asm-only
```

This prints the exact retail instructions and their little-endian bytes — this
is your target. (In `asm/cod/000000.s` the same function lives between
`glabel func_002772A8` and `endlabel func_002772A8`; the 3rd field of each
`/* ... */` comment is the raw retail bytes.)

### Step 2 — first-pass C with m2c

`m2c` turns MIPS back into rough C. It won't match, but it gives you the
shape — control flow, struct offsets, call signatures:

```bash
.venv/bin/python tools/m2c/m2c.py --target mipsee-gcc-c <asm-for-the-function>
```

Clean it up: name the locals, replace raw offsets with struct field accesses
(`STRUCTS.md` and Ghidra help here), declare the externs it references.

**Large or jump-table-heavy function?** Don't hand-feed m2c the raw monolithic —
use `scripts/m2c_prep.py <func> --casts`, which auto-discovers and reassembles
the jump tables, injects the labels splat omits, restores raw-encoded COP1/COP2
ops, and emits a compilable house-style C body in one step. It also warns you
about two gotchas (the carve `.globl` re-export for rodata-referenced
jump-table labels, and objdiff's inability to score multi-thousand-insn
functions).

### Step 3 — score it, fast

`score_candidate.py` is your inner loop. It compiles **just that one function**
with the project's exact flags and tells you MATCH / NO-MATCH in ~0.3 s,
without a full relink and without touching any tracked file:

```bash
.venv/bin/python scripts/score_candidate.py func_002772A8 my_candidate.c
# exit 0 = MATCH, 1 = bytes differ, 2 = compile error
```

Some functions were built with a different compiler in the SDK. If you're not
sure which, let the scorer try both:

```bash
.venv/bin/python scripts/score_candidate.py func_002772A8 my_candidate.c --try-both
# compilers: cygnus-2.96 (the default catch-all) and sn-2.95.3-136 (sq-prologue functions, etc.)
```

(There's an address-band heuristic for which compiler a function wants — see
the notes referenced from `compile_config.json` and `src/cod/002772.c`'s
header comment for a worked example.)

### Step 4 — when it's close, diff to see *what's* off

If the bytes differ, see exactly where. objdiff gives a per-instruction diff
against the retail target:

```bash
# unit = the TU path minus its extension, symbol = the function name
tools/objdiff-cli diff -p . -u src/cod/002772 func_002772A8
```

`asm-differ` (in `tools/asm-differ/`) is the interactive sibling if you prefer
a scrolling side-by-side.

Read the diff structurally. A different register or a reordered load almost
always means the **C structure** is wrong, not that you need to fight the
compiler. Common fixes: reorder local declarations, store an address directly
instead of through a temp, fix a return-value's liveness, get a cast right.

### Step 5 — brute-force the last mile with decomp-permuter

When you're *close* (right instructions, wrong order/registers), let the
permuter mutate your C looking for a byte-identical arrangement:

```bash
# import your scratch into a permuter workdir, then run it
tools/decomp-permuter/import.py ...        # uses permuter_settings.toml
tools/decomp-permuter/permuter.py <workdir>
```

`permuter_settings.toml` is already wired to the project's `ee-gcc 2.96`
flags. The permuter is for closing gaps, not for generating matches from
scratch.

### Step 6 — integrate and commit

When `score_candidate.py` says MATCH, land it. The integrator carves the
function (adds the `carved_funcs` entry, swaps the `INCLUDE_ASM` for your C),
reseeds the objdiff target, and re-verifies the full ELF still equals retail:

```bash
.venv/bin/python scripts/integrate_match.py func_002772A8 my_candidate.c
```

Or do integrate + verify + commit in one gated step (this is what the agents
use — it refuses on a dirty tree, runs the cheat-detector and byte-match gate,
runs the fast `session_check` subset, and prints the new commit sha):

```bash
scripts/match_and_commit.sh func_002772A8 my_candidate.c
```

Before you consider the work done, run the full session check:

```bash
scripts/session_check.sh
```

It must exit clean. It builds the ELF, verifies the sha256 ratchet, checks the
objdiff score didn't drop, validates the carve, and runs the forced-register
guard.

---

## 5. The rules (these are non-negotiable)

1. **Honor the ratchet.** Never commit something that lowers
   `matched_code_percent` or breaks the build. `scripts/session_check.sh` is
   the gate.

2. **No forced registers.** Do **not** use
   `register T x __asm__("$N");` to force the compiler's hand. A register-only
   diff means your C structure is wrong — fix the structure, run the permuter,
   and if it still won't match, ship an honest `INCLUDE_ASM("nonmatching", ...)`.
   A pinned pseudo-match is *not* a match, and `scripts/check_forced_regs.py`
   hard-fails any pin (the allowlist is kept empty). See
   [`src/cod/002772.c`](./src/cod/002772.c) for a function that was correctly
   *regressed* back to nonmatching rather than pinned.

3. **Name what you understand, in the same commit.** Names don't affect the
   ratchet but they *are* most of the deliverable (and what makes the PC port
   possible). If you figure out what a function, global, or struct is,
   propagate the name into `config/symbol_addrs.txt`, the C source,
   `carved_funcs`, and Ghidra — together, in the commit that matched it. See
   `DECISIONS.md`.

4. **Don't relitigate locked decisions.** Read [`DECISIONS.md`](./DECISIONS.md)
   before proposing an architectural change. If you hit a genuinely new fork,
   add a proposal there *before* implementing.

5. **One focused change per commit.** Prefix the commit subject with the task
   or context tag in brackets, e.g. `[func-match] func_002772A8: …`. Don't
   sneak unrelated "small fixes" into a match commit.

6. **A non-matching decomp is still progress.** If a function resists matching,
   landing readable `INCLUDE_ASM("nonmatching", name)` C with the structure and
   names figured out is valuable — it can be ratcheted to matching later, and
   it feeds the port. Honest beats fake.

---

## 6. Measuring progress

```bash
scripts/progress.sh                      # regenerate report + print headline
.venv/bin/python scripts/render_state.py # refresh STATE.md's metric block
```

Never hand-type the matched percentage into `STATE.md` — regenerate it. (The
old hand-edited dashboard once reported four different numbers for the same
metric; that's why it's generated now.)

---

## 7. Quick reference

| You want to… | Command |
|---|---|
| See a function's retail bytes/disasm | `score_candidate.py <name> --asm-only` |
| First-pass C from asm | `tools/m2c/m2c.py --target mipsee-gcc-c <asm>` |
| Test a candidate (fast, no relink) | `score_candidate.py <name> cand.c [--try-both]` |
| See *where* the bytes differ | `tools/objdiff-cli diff -p . -u <tu> <name>` |
| Close the last mile | `tools/decomp-permuter/permuter.py <workdir>` |
| Integrate a match | `integrate_match.py <name> cand.c` |
| Integrate + verify + commit | `scripts/match_and_commit.sh <name> cand.c` |
| Pre-commit gate | `scripts/session_check.sh` |
| Build the ELF | `compile.py` |
| Build one TU only | `compile.py --single-file src/cod/<x>.c` |
| Progress headline | `scripts/progress.sh` |
| Browse the worklist | `scripts/function_atlas.py` |

---

## 8. Where to go deeper

- [`README.md`](./README.md) — project overview, goals, legal
- [`ORIENT.md`](./ORIENT.md) — full orientation contract (what the agents follow)
- [`program.md`](./program.md) — the success spec and milestones
- [`notes/`](./notes/) — every recon report and retro; the project's memory

Welcome aboard. Match one small function end-to-end first — it teaches the
whole loop in an afternoon.
