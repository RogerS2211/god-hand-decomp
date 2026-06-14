# godhand-recomp

Matching decompilation of **God Hand** (PS2, 2006, Clover Studio / Capcom),
orchestrated by the [pi coding agent]. The build targets **all three regional
masters** from one source tree, selected by a short version key.

| key | serial | region | disc | boot ELF | status |
|-----|--------|--------|------|----------|--------|
| `us` | SLUS-21503 | NTSC-U | 1.00 | `SLUS_215.03` | matching (primary) |
| `eu` | SLES-54490 | PAL | 1.00 | `SLES_544.90` | byte-identical + 533 ported funcs |
| `jp` | SLPM-66550 | NTSC-J | 1.01 | `SLPM_665.50` | byte-identical + 538 ported funcs |

All three build **byte-identical to their retail boot ELF** (`elf_sha256` in
[`config/versions.json`](./config/versions.json)). `us` carries the active C
decompilation; `eu`/`jp` are byte-identical empty-carve baselines that the
[cross-version port tooling](#multi-version-support) fills in from the matched
`us` C. The same compiler/SDK built all three, so a matched `us` function is
the same machine code on the siblings — see [`MULTIVERSION.md`](./MULTIVERSION.md).

See [`program.md`](./program.md) for the success spec and the `notes/`
directory for the recon report.

## Goals

1. Produce C/C++ that compiles back into a byte-identical `SLUS_215.03` plus
   matching `.rel` overlays, using the original SCE PS2 SDK 3.0.20 toolchain.
2. From the same source tree, build a **native PC port** with a thin platform
   abstraction layer (SDL, modern graphics API, modern audio).
3. Drive the per-function matching loop with an orchestration layer that
   runs parallel attempts and ratchets git on a single matched-code metric.

## How it works (the orchestration model)

```
┌─────────────────────────────────────────────────────────────────┐
│  outer loop  ── reads program.md, picks next function/REL,     │
│                  spawns worktree workers, integrates results,   │
│                  ratchets git on matched_text_percent           │
└────────────────────────┬────────────────────────────────────────┘
                         │ per-function
                         ▼
┌─────────────────────────────────────────────────────────────────┐
│  inner loop  ── per-function: m2c → edit → compile/view asm →   │
│                  objdiff → decomp-permuter → matched or          │
│                  escalated                                       │
└────────────────────────┬────────────────────────────────────────┘
                         │
                         ▼
┌─────────────────────────────────────────────────────────────────┐
│  splat + ee-gcc 2.96 + dvp-as + ee-ld + objdiff + asm-differ    │
│  ground truth: disc_extract/SLUS_215.03 (sha256 1742f95b…f3cd)  │
└─────────────────────────────────────────────────────────────────┘
```

The inspirations are explicit:
- [decomp.me](https://decomp.me) — collaborative matching scratches model
- a single-metric git ratchet — every commit only ever raises matched code
- [recvx-decomp](https://github.com/fmil95/recvx-decomp) — PS2 matching-decomp template (same era, same publisher)

## Layout

```
.
├── God Hand (USA).iso       your own dump, gitignored
├── disc_extract/             extracted boot ELF + tables, gitignored except hashes
├── program.md                research spec / success ratchet
├── notes/                    recon, design decisions, retros
├── config/
│   ├── SLUS_215.03.yaml      splat config
│   ├── SLUS_215.03.lcf       ee-ld linker script
│   ├── symbol_addrs.txt      seeded from Ghidra
│   └── reloc_addrs.txt
├── compiler/                 ee-gcc 2.96 + SN linker, vendored, gitignored
├── tools/                    splat, m2c, asm-differ, objdiff, decomp-permuter
├── src/                      decompiled C/C++
├── include/                  shared headers (sce/, cri/, capcom/, gh/)
├── asm/                      splat output, INCLUDE_ASM'd from src
├── bin/                      splat data dumps
├── expected/                 disassembled-from-original .o files (objdiff target)
├── build/                    compile output (.o, .elf, .map), gitignored
├── ghidra/                   local Ghidra project for static analysis, gitignored
├── scripts/                  small utilities (iso extraction, afs reader, …)
├── .pi/
│   ├── agents/               custom decomp-* workers (scout, worker, oracle, integrator)
│   ├── chains/               saved orchestration workflows
│   └── extensions/           tools wrapping the GhidraMCP HTTP API
├── compile.py                top-level build entry point
└── objdiff.json              objdiff project (per-.o scoring)
```

## Setup (will be filled in once toolchain is vendored)

```bash
# 1. Place your own dumped ISO at the repo root as 'God Hand (USA).iso'.
#    Expected sha256: TBD (matches NTSC-U serial SLUS-21503).
# 2. Extract the boot ELF:
./scripts/extract_iso.sh

# 3. Vendor the SCE PS2 SDK 3.0.20 toolchain (ee-gcc 2.96 + SN linker + dvp-as):
./scripts/setup_toolchain.sh

# 4. Install Python build deps (splat, etc.):
pip install -r scripts/requirements.txt

# 5. Generate the asm split + objdiff project:
python compile.py --setup

# 6. Build the project (empty matching link to start):
python compile.py            # default version is 'us'

# 7. Run the unit tests (parsers, carve splitter, ELF reglue, cross-version
#    mapper, cross-region atlas). Wall time < 1 s.
.venv/bin/python -m pytest tests/
```

Add `--version eu` / `--version jp` to any `compile.py` invocation to target a
sibling (the registry in `config/versions.json` resolves the per-version
config). Omitting `--version` reproduces the original `us` build byte-for-byte.

## Nix dev environment (optional)

`nix develop` provisions a sealed toolchain (compiler, wibo, objdiff,
cross-binutils, python, node). It is **additive** to
`scripts/setup_toolchain.sh`: the shellHook symlinks the pinned blobs into the
exact gitignored paths the script already guards, so the script skips the blob
fetches and only does the venv, Python tools, assembler patches, and git hooks.

- **Linux (x86_64 or ARM):** `nix develop`, then `./scripts/setup_toolchain.sh`
  (the blobs are already provisioned), then `python compile.py`. On x86_64 the
  i386 compiler blobs run natively; on ARM they run transparently under
  `qemu-i386` (wired into the shell).
- **Without Nix:** install the host prereqs and run `./scripts/setup_toolchain.sh`
  as before, then `python compile.py`.
- **macOS:** the compiler is an i386-Linux binary, so run the Linux flow inside a
  `linux/amd64` container:

  ```bash
  docker run --platform linux/amd64 -v "$PWD":/src -w /src nixos/nix \
    nix develop --extra-experimental-features 'nix-command flakes' --command bash
  ```

## Multi-version support

One source tree builds all three regional masters. Full architecture is in
[`MULTIVERSION.md`](./MULTIVERSION.md); the short version:

```bash
./scripts/extract_iso.sh --version eu        # extract that region's boot ELF (hash-checked)
python compile.py --version eu               # build it
scripts/checks/build_version.sh eu           # build + verify vs retail (full-ELF sha256)
scripts/checks/build_all_versions.sh         # build + verify every bootstrapped version
python scripts/bootstrap_version.py <key>    # bring up a brand-new region from its ELF
```

**Cross-version porting.** Because all three were built with the same
compiler/SDK, a function matched on `us` is — modulo relocations — the same
machine code on `eu`/`jp`. `scripts/port_version.py` finds each `us` function's
sibling counterpart by a **relocation-masked opcode signature** and writes:

```bash
python scripts/port_version.py --version eu  # -> config/eu/symbol_addrs.txt + progress/port_plan.eu.json
```

`config/<ver>/symbol_addrs.txt` maps the canonical `us` name to the sibling's
address; `progress/port_plan.<ver>.json` reports how many matched functions are
landable on the sibling. A function that matches `us` but has **no** sibling
counterpart is a strong overfit signal and is flagged rather than ported.

## Measuring progress

Progress is measured per version, the same way for all three:

- **`matched_code_percent` / `matched_functions`** — the fine-grained metric.
  [objdiff](https://github.com/encounter/objdiff) diffs every compiled unit
  against the frozen retail-disassembly target and counts the `.text` bytes (in
  real C units) that compile byte-identical to retail. Each version has its own
  objdiff project (`objdiff.json` for `us`, `config/<ver>/objdiff.json` for the
  siblings) and report (`progress/report.<ver>.json`):

  ```bash
  python compile.py --version eu --setup     # build units + write config/eu/objdiff.json
  scripts/progress.sh --version eu           # -> progress/report.eu.json + headline
  scripts/checks/progress_all.sh             # one-screen dashboard across all versions
  ```

- **Full-ELF byte identity** — the binary pass/fail gate. `build_version.sh`
  checks the built ELF's sha256 against the retail boot ELF. The empty-carve
  baselines already pass it at 0% C; as functions are carved to C it stays green
  only while every carved function reproduces retail exactly, so 100% matched
  code ⇒ a byte-identical ELF.

The two are complementary: objdiff shows *how far in* the decomp is; the sha256
gate shows whether the binary still reproduces. The shared compiler also makes
progress *transferable* — porting matched `us` C lifts the siblings' numbers
without re-decompiling.

**The worklist (cross-region function atlas).** To know *how far there is to
go* across all three masters at once, `scripts/function_atlas.py` aligns the
function sequences of every region (anchored address-order alignment) into a
single census — every function, grouped into a cross-region equivalence class
with a match tier, plus the genuine per-region deltas:

```bash
python scripts/function_atlas.py             # -> progress/function_atlas.{json,summary.md}
```

It currently maps **11113 / 11144** eu and **11115 / 11115** jp functions to
their `us` counterpart — ~**11,200 distinct logical functions** across all three
masters, of which **10979** land byte-exact in both siblings with only a name +
address remap (1727 of them already decompiled).
`progress/function_atlas.summary.md` is the human-readable headline; see
[`MULTIVERSION.md`](./MULTIVERSION.md#cross-region-function-atlas-the-worklist)
for the method.

**Porting is real and byte-verified.** A cross-version *data* map
(`scripts/data_map.py`) re-points the `D_*`/`jtbl_*` symbols a matched function
touches, and `scripts/land_verify.py` lands matched `us` C onto a sibling while
keeping only the TUs that hold the **full-ELF build byte-identical to retail**.
Once **boundary-safe carving** removed the linker's carve-unit alignment trap
(a one-line `SUBALIGN(8)` in the build-time linker script), this carried
**533 functions onto eu and 538 onto jp** straight from the `us` C — no
re-decompilation — lifting both siblings to ~0.75–0.86% matched code (see
[`MULTIVERSION.md`](./MULTIVERSION.md#verified-landing)).

## Contributing

Solo / private right now — not yet accepting external contributors. Will revisit
once the build is reproducible and the orchestration loop is stable.

## Legal

This repository contains no copyrighted Capcom or Sony assets. The boot ELF
hash recorded in the recon notes identifies the legitimately-dumped NTSC-U
retail disc, but no game data is distributed here. The original SCE PS2 SDK binaries used for matching builds
are not redistributed in this repo; the setup script downloads them from
public archives maintained by the PS2 decomp community.

Trademarks of *God Hand*, *Clover Studio*, and *Capcom* belong to their
respective holders. This project is for preservation, education, and
non-commercial research.

[pi coding agent]: https://github.com/Earendil-Works/pi
