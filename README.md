# god-hand-decomp

[![Build](https://github.com/LucasPicoli/god-hand-decomp/actions/workflows/progress.yml/badge.svg)](https://github.com/LucasPicoli/god-hand-decomp/actions/workflows/progress.yml)
[![Code matched](https://decomp.dev/LucasPicoli/god-hand-decomp.svg?mode=shield&measure=fuzzy_match_percent&label=code%20matched)](https://decomp.dev/LucasPicoli/god-hand-decomp)
[![Fully linked](https://decomp.dev/LucasPicoli/god-hand-decomp.svg?mode=shield&measure=complete_code&label=fully%20linked)](https://decomp.dev/LucasPicoli/god-hand-decomp)
[![Functions matched](https://decomp.dev/LucasPicoli/god-hand-decomp.svg?mode=shield&measure=matched_functions&label=functions)](https://decomp.dev/LucasPicoli/god-hand-decomp)

A work-in-progress **matching decompilation** of **God Hand** — the 2006
PlayStation 2 brawler by **Clover Studio / Capcom** (NTSC-U, serial
`SLUS-21503`).

The goal is human-readable C that recompiles, with the GPL `ee-gcc` 2.96
toolchain, into a **byte-identical** `SLUS_215.03` boot ELF and
matching `.rel` overlays — the standard "matching decomp" bar, verified
function-by-function against the retail binary with [objdiff](https://github.com/encounter/objdiff).

> **No game data lives in this repository.** You supply your own legally-dumped
> disc. See [Legal](#legal).

## Progress

| Metric | Value |
| --- | --- |
| Code matched (fuzzy) | **3.61 %** |
| Code fully linked | **2.97 %** |
| Functions matched | **1,927 / 11,199** (17.21 %) |
| Data matched | **83.01 %** |
| Translation units | 3,605 |

> Three code axes, all from objdiff's report — the same three decomp.dev shows.
> **Code matched (fuzzy)** is `fuzzy_match_percent` (decomp.dev's "decompiled"
> headline); it includes plausible clean-C bodies kept behind a `NON_MATCHING`
> guard (the matching-decomp convention; see [CONTRIBUTING](CONTRIBUTING.md)).
> **Code fully linked** is `complete_code_percent` (decomp.dev's "fully linked") —
> the share of `.text` in TUs built *entirely* from source, i.e. decompiled and
> linked, not merely byte-matched in place. **Functions matched** is the strict
> 100 %-byte-exact count. Partials never inflate the latter two, and the default
> build stays byte-identical to retail regardless.

**Visual function tracker:** the live progress page — per-category rollup, a
per-unit tree, badges, and PR comments — is hosted on decomp.dev:
[**decomp.dev/LucasPicoli/god-hand-decomp**](https://decomp.dev/LucasPicoli/god-hand-decomp).
It ingests [`progress/report.json`](progress/report.json) (uploaded by
`.github/workflows/progress.yml`), so it stays current on every push.

Regenerate the published report after a build:

```bash
scripts/score_nm.sh                 # regenerate progress/report.json (scored build)
```

## Quick start

You need Python 3.10+, the `mipsel-linux-gnu` binutils, and your own God Hand
(USA) disc image. The matching toolchain is Linux x86-64; **Windows** (via WSL2)
and **macOS** (via a Linux container/VM) are supported — see
[CONTRIBUTING.md § Platform support](CONTRIBUTING.md#platform-support).

```bash
# 1. Place your own dumped disc at the repo root as 'God Hand (USA).iso'.
#    The boot ELF it yields (disc_extract/SLUS_215.03, 3,607,008 B) must hash to
#    sha256 1742f95bef65bdb2aa57b7a77df4ac7619a092e9646e1ea325bc32ec8a64f3cd
./scripts/extract_iso.sh          # carve the boot ELF + overlay tables

# 2. Vendor the matching toolchain (ee-gcc 2.96 + SN ee-gcc + dvp-as + m2c).
./scripts/setup_toolchain.sh

# 3. Generate the asm split + objdiff project, then build.
python compile.py --setup         # (re)write objdiff.json from the linker map
python compile.py                 # build all .o + link the .elf

# 4. Diff a single object against the retail target.
python compile.py --single-file src/cod/000000.c
scripts/checks/diff.sh src/cod/000000             # objdiff TUI for one unit

# 5. Lock-in tests for the build helpers (sub-second).
python -m pytest tests/test_compile.py tests/test_carver.py
```

## Project layout

```
.
├── src/                decompiled C — recovered class TUs (src/cod/<family>/<Class>.c)
│                        + address-bucket files for the rest (src/cod/<addr>.c)
├── include/            shared headers (sce/, godhand/, macro/asm helpers)
├── asm/                splat-disassembled .s, INCLUDE_ASM'd from src (generated)
├── config/             splat configs, ee-ld linker scripts (.lcf), symbol/reloc tables
├── compile.py          build entry point (compile → assemble → link)
├── compile_config.json build manifest: per-TU carve schema consumed by compile.py
├── objdiff.json        objdiff project: per-object target ↔ base mapping + categories
├── progress/
│   ├── report.json     objdiff progress report (the file decomp.dev consumes)
│   ├── unit_names.json subsystem-folder display names for the decomp.dev tree
│   └── unit_part_funcs.json  carved-fragment → contained functions (names partN units)
├── docs/               MIPS cheatsheet, code style notes
├── scripts/            build, verification, and decomp tooling
│   └── checks/         CI-style gates (build, diff, splat, units, score, …)
├── tools/              objdiff-cli + splat extensions (splat_ext: sndata, …)
├── tests/              pytest suite for the build/decomp helpers
├── patches/            local patch for ee-as (R5900 short-loop errata)
├── ctx.h               m2c context typedefs (matching-only; never linked)
└── disc_extract/       boot ELF + overlay tables (gitignored; only rel/manifest.json kept)
```

## How matching works

```
splat ── carves the retail SLUS_215.03 ELF into per-address asm units
  │
  ▼
src/cod/<addr>.c ── INCLUDE_ASM'd stubs replaced, function by function, with C
  │
  ▼
compile.py ── ee-gcc 2.96 → .o ──► objdiff ──► byte-identical?  ──► commit
  │                                   │
  │                                   └─ not yet → m2c first pass / decomp-permuter / hand-tune
  ▼
progress/report.json ── regenerated → docs/ tracker → decomp.dev
```

Ground truth is the retail boot ELF (`disc_extract/SLUS_215.03`,
sha256 `1742f95b…f3cd`). A function counts only when its compiled bytes match
the target exactly. A small set of functions use the SN ProDG `ee-gcc` 2.95.3
compiler instead of Cygnus 2.96 (selected per-TU in `compile_config.json`) when
that is what the retail prologue requires.

## Progress reporting & decomp.dev

This repo follows the [decomp.dev](https://decomp.dev) model:

1. `progress/report.json` is an [objdiff](https://github.com/encounter/objdiff)
   report describing matched, fully-linked, and fuzzy code plus data/functions
   per unit (the three axes in the table above). It is committed so decomp.dev
   ingests it with zero build; `scripts/mark_complete.py` derives the
   fully-linked (`complete_code`) axis on every report regeneration.
2. The GitHub Actions workflow [`.github/workflows/progress.yml`](.github/workflows/progress.yml)
   uploads it as an artifact named `SLUS_215.03_report` on every push.

Before upload, the workflow applies a display-name remap
([`scripts/gen_unit_names.py`](scripts/gen_unit_names.py)) to a *copy* of the
report, so decomp.dev's file tree reads by subsystem (`enemy/`, `object/`,
`cri-middleware/`, …) instead of `asm/src/<addr>`. The committed report keeps
its `src/cod/<addr>` names, which the tracker tooling resolves to source files.

The un-decompiled monolith is carved into per-gap `asm/cod/000000.partN`
fragments; on their own these show as opaque part-index leaves. The remap names
each fragment after the function(s) it holds, via the committed
[`progress/unit_part_funcs.json`](progress/unit_part_funcs.json) manifest — which
records only the **start vaddrs** in each fragment (names are resolved from
`config/symbol_addrs.txt` at remap time, so the public report never shows a name
absent from public source). That manifest needs the (gitignored) monolithic asm
to build, so — like `report.json` — it is regenerated locally, not in CI. After
a carve changes, regenerate both in order:

```sh
python3 scripts/gen_part_funcs.py   # asm/cod/000000.s -> progress/unit_part_funcs.json
python3 scripts/gen_unit_names.py   # -> progress/unit_names.json (consumes the manifest)
```

Empty alignment-only gaps land in a `cod/_pad/` bucket; a fragment holding
several functions is named after its first and suffixed `(+n)`.

### Function categories

The objdiff project defines progress categories — `engine`, `cri-middleware`,
`sce-runtime`, `crt`, `unknown` — so progress can be reported per subsystem
rather than as one bar. [`progress/function_categories.json`](progress/function_categories.json)
maps game `.text` addresses to a category; `engine` (the game's own code, the
decomp target) is the default for any address not listed.

The non-engine categories cover code the game statically linked from standard
libraries / middleware / the C runtime. These are identified — not rewritten —
by relocation-masked instruction-signature analysis (confirmed byte-identical
modulo relocation); no third-party source is committed. Identified so far
(≈ **4.9 % of `.text`**, 837 functions):

| category | functions | % of `.text` |
|---|---:|---:|
| `cri-middleware` | 363 | 1.98 % |
| `sce-runtime` | 224 | 1.70 % |
| `crt` | 250 | 1.24 % |

This breakdown is rendered as category bars on the
[decomp.dev page](https://decomp.dev/LucasPicoli/god-hand-decomp).

The category axis is orthogonal to the matching/`permanent` axis: a function's
category says *what subsystem it belongs to*, independent of whether it is
matched or carried as `INCLUDE_ASM`. The companion
[`progress/library_identified.json`](progress/library_identified.json) is the
permanent-classification axis — the subset of identified library functions
carried as `INCLUDE_ASM` and treated as non-gating for decomp progress (they are
not the engine code the decomp targets).

objdiff's per-**unit** category bars are populated for the library functions that
are carved as standalone units — most of the identified set — so the
`cri-middleware` / `sce-runtime` / `crt` bars render on the tracker and decomp.dev.
The remainder (functions matched as C, plus a contiguous high-address
`libstdc++` iostream region not yet split out) still fall under `engine`; the table
above (from `function_categories.json`) remains the source of truth for the full
identified set until a per-symbol carve pass splits the rest into their own units.

## Contributing

Pick an unmatched function, make it byte-match, send a PR. The full workflow —
choosing a target, the objdiff loop, naming/struct conventions, and what a good
PR looks like — is in **[CONTRIBUTING.md](CONTRIBUTING.md)**.

## Legal

This repository contains **no copyrighted Capcom or Sony assets** and
distributes **no game data**. The boot-ELF hash recorded above merely
identifies the legitimately-dumped NTSC-U retail disc so contributors can verify
they have the right image — you must dump your own copy.

The matching build uses the GCC-based **ee-gcc** compiler (Cygnus 2.96 and SN
ProDG 2.95.3), which is free software under the GNU GPL;
`scripts/setup_toolchain.sh` fetches it from the decompilation community's
public compiler collection ([decompme/compilers](https://github.com/decompme/compilers)).
**No proprietary Sony/SCE PS2 SDK code, headers, or libraries are used or
distributed** — un-decompiled functions are emitted as raw bytes from your own
disc dump via `INCLUDE_ASM`, and the headers under `include/` are the
project's own.

The decompiled C is derived, by hand and tooling, from a binary you own, for the
purposes of **preservation, education, and non-commercial research**.
*God Hand*, *Clover Studio*, and *Capcom* are trademarks of their respective
holders; this project is not affiliated with or endorsed by them.

## Acknowledgements

Built on the shoulders of the decomp community:
[objdiff](https://github.com/encounter/objdiff) &
[decomp.dev](https://decomp.dev) (Luke Street),
[splat](https://github.com/ethteck/splat),
[m2c](https://github.com/matt-kempster/m2c),
[decomp-permuter](https://github.com/simonlindholm/decomp-permuter),
[decomp.me](https://decomp.me), and the
[recvx-decomp](https://github.com/fmil95/recvx-decomp) PS2 template.
