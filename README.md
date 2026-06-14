# godhand-recomp

Matching decompilation of **God Hand** (PS2, 2006, Clover Studio / Capcom),
orchestrated by the [pi coding agent]. The build targets the NTSC-U retail
master (`SLUS-21503`) from one source tree.

| key | serial | region | disc | boot ELF | status |
|-----|--------|--------|------|----------|--------|
| `us` | SLUS-21503 | NTSC-U | 1.00 | `SLUS_215.03` | matching (primary) |

The build is **byte-identical to the retail boot ELF** (`elf_sha256` in
[`config/versions.json`](./config/versions.json)) and carries the active C
decompilation. Omitting `--version` reproduces the original build byte-for-byte.

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

# 7. Run the unit tests (parsers, carve splitter, ELF reglue). Wall time < 1 s.
.venv/bin/python -m pytest tests/
```

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

## Measuring progress

Progress is measured two complementary ways:

- **`matched_code_percent` / `matched_functions`** — the fine-grained metric.
  [objdiff](https://github.com/encounter/objdiff) diffs every compiled unit
  against the frozen retail-disassembly target and counts the `.text` bytes (in
  real C units) that compile byte-identical to retail. The objdiff project
  (`objdiff.json`) and report (`progress/report.json`):

  ```bash
  python compile.py --setup                  # build units + write objdiff.json
  scripts/progress.sh                         # -> progress/report.json + headline
  ```

- **Full-ELF byte identity** — the binary pass/fail gate. The build checks the
  built ELF's sha256 against the retail boot ELF. The empty-carve baseline
  already passes it at 0% C; as functions are carved to C it stays green only
  while every carved function reproduces retail exactly, so 100% matched code ⇒
  a byte-identical ELF.

The two are complementary: objdiff shows *how far in* the decomp is; the sha256
gate shows whether the binary still reproduces.

**The worklist.** To know *how far there is to go*,
`scripts/function_atlas.py` aligns the function sequence of the master into a
single census — every function, grouped with a match tier:

```bash
python scripts/function_atlas.py             # -> progress/function_atlas.{json,summary.md}
```

`progress/function_atlas.summary.md` is the human-readable headline.

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
