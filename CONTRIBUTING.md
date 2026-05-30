# Contributing to god-hand-decomp

Thanks for helping decompile **God Hand**. This is a *matching* decomp: the bar
for any contribution is that the compiled output is **byte-identical** to the
retail binary, verified with [objdiff](https://github.com/encounter/objdiff).
You don't need PS2 or reverse-engineering experience to start — just patience
and a willingness to read assembly.

By contributing you agree your work is your own and is offered under the same
preservation/education/non-commercial-research terms described in the
[README's Legal section](README.md#legal). **Never** commit game assets, ripped
data, ROMs/ISOs, SDK binaries, or any copyrighted material.

## 1. One-time setup

You must own a copy of the game and dump it yourself.

```bash
# Place your dumped disc at the repo root as 'God Hand (USA).iso', then:
./scripts/extract_iso.sh        # carve disc_extract/SLUS_215.03 (+ overlay tables)
./scripts/setup_toolchain.sh    # vendor ee-gcc 2.96 + SN ee-gcc + dvp-as + m2c
python compile.py --setup       # generate objdiff.json from the linker map
python compile.py               # full build — should complete cleanly
```

Verify your boot ELF is the right one before doing anything else:

```
sha256(disc_extract/SLUS_215.03) == 1742f95bef65bdb2aa57b7a77df4ac7619a092e9646e1ea325bc32ec8a64f3cd
```

If that hash differs, your dump is wrong — stop, nothing else will match.

## 2. Pick a function

Open the visual tracker ([`docs/progress.html`](docs/progress.html)) or the live
[decomp.dev](https://decomp.dev) page and look for a translation unit that is
**partially** matched — those have the most low-hanging functions. Good first
targets are small leaf functions (no calls) in a unit that is already mostly
done.

```bash
# List remaining (still INCLUDE_ASM'd) functions for a unit:
scripts/checks/units.sh
# or inspect a single unit's source:
$EDITOR src/cod/<addr>.c
```

Each `src/cod/<addr>.c` file holds one carved address range. Unmatched functions
appear as `INCLUDE_ASM(...)` stubs that pull in the raw `asm/` disassembly;
your job is to replace a stub with C that compiles to the same bytes.

## 3. The matching loop

```bash
# Compile just your unit (no link) and open the objdiff diff for it:
python compile.py --single-file src/cod/<addr>.c
scripts/checks/diff.sh src/cod/<addr>        # interactive objdiff TUI

# Or get a one-shot score for the unit:
scripts/checks/score.sh src/cod/<addr>
```

Iterate: write/adjust C → recompile → read the diff → repeat until the function
is 100 %. Useful helpers:

- **`m2c`** (vendored in `tools/`) gives a first-pass C decompilation to start from.
- **`decomp-permuter`** (`permuter_settings.toml` is preconfigured) brute-forces
  equivalent C variations when you're close but not exact.
- **`ctx.h`** holds shared typedefs so m2c output compiles; it is matching-only
  and never linked, so you may add context typedefs there freely.
- Some functions need the **SN ProDG `ee-gcc` 2.95.3** compiler rather than the
  default Cygnus 2.96 (e.g. retail prologues that use the `sq` instruction for
  callee-saved registers). Opt a TU in via `compile_config.json`; see existing
  entries for the format.

A function is "done" only when objdiff shows it 100 % matched. Do **not** commit
"pseudo-matches" that rely on instruction shapes the original compiler wouldn't emit.

## 4. Naming & conventions

- **Files:** one TU per carved range, `src/cod/<addr>.c`. Don't rename existing TUs.
- **Functions/symbols:** if you can identify a function's purpose, name it and add
  the mapping to `config/symbol_addrs.txt`; otherwise leave the address-anchored
  name. Renames belong in their own commit.
- **Structs:** field offsets in matched C are exact ground truth. If you work out
  a struct's layout, document it in a short comment above the function rather than
  inventing speculative names.
- **Style:** match the surrounding code. Decomp C is not idiomatic C — readability
  is secondary to matching; keep the variable/casting shapes the compiler needs.

## 5. Before you open a PR

Run the relevant gates (all fast):

```bash
python compile.py                                  # full build still links
python -m pytest tests/test_compile.py tests/test_carver.py
scripts/checks/diff.sh src/cod/<addr>              # your unit is still matched
python tools/gen_progress_page.py                  # refresh docs/ tracker + badges
```

Then:

1. Branch from `main`, keep the change focused (one unit / one logical change).
2. In the PR description, state which functions newly match and paste the objdiff
   score before/after.
3. Commit the refreshed `progress/report.json` and `docs/` if your change moved
   the numbers.
4. Commit messages: short imperative subject, e.g.
   `match func_00359218 in src/cod/func_00359218`.

CI ([`.github/workflows/progress.yml`](.github/workflows/progress.yml)) uploads
the progress report on every push so decomp.dev (and the badges) stay current.

## 6. Questions

Open an issue. Toolchain quirks and design rationale are documented in the
relevant `scripts/` and `config/` files; skim those first.

Happy matching.
