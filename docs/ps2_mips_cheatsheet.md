# PS2 / EE MIPS cheatsheet

A quick reference for reading the disassembly and matched C in this repo. The PS2's
Emotion Engine is a MIPS R5900 (MIPS III + custom 128-bit multimedia ops).

## Registers (o32-ish EE ABI)

| Reg | Name | Role |
|-----|------|------|
| `$0` | zero | always 0 |
| `$2-$3` | v0-v1 | return values |
| `$4-$7` | a0-a3 | first 4 integer args |
| `$8-$15`, `$24-$25` | t0-t9 | caller-saved temporaries |
| `$16-$23` | s0-s7 | callee-saved |
| `$28` | gp | global pointer (small data) |
| `$29` | sp | stack pointer |
| `$30` | fp/s8 | frame pointer / saved |
| `$31` | ra | return address |
| `$f0-$f31` | — | FPU (COP1) single-precision floats |

Decomp C uses `a0, a1, …` as parameter names and `v0, …` / `temp_*` for locals,
mirroring the register the compiler assigned.

## Common idioms

- **Delay slots:** the instruction after a branch/jump (`jal`, `b`, `jr`) executes
  *before* the branch takes effect. spimdisasm shows it indented after the branch.
- **Function call:** `jal target` (sets `ra`), args in `a0-a3`, return in `v0`.
  Tail call: `j target` with no `ra` save.
- **Field access:** `lw v0, 0x90(a0)` = `v0 = *(int*)(a0 + 0x90)` → in C often
  `*(int*)((char*)a0 + 0x90)` or a struct field.
- **Float compare/branch:** `c.lt.s`/`c.eq.s` set the FPU condition flag; `bc1t`/`bc1f`
  branch on it.
- **Small constants:** `addiu`, `ori`, `lui`+`ori` for 32-bit immediates.
- **`nop` padding:** TU/function boundaries are padded to 0x10 with `nop`
  (`0x00000000`).

## Matching workflow

- A function "matches" when its compiled `.o` is byte-identical to retail. The whole
  ELF links byte-identical to retail regardless of how much is decompiled (undecompiled
  functions are `INCLUDE_ASM`'d, emitting retail bytes).
- Use `objdiff` (config in `objdiff.json`) to compare your build against the target
  per function. `scripts/checks/build.sh` is the byte-identity gate.

## Toolchain

- Compilers (per-TU, recorded in the carve records): `cygnus-2.96` (default),
  `sn-2.95.3-136` (SN ProDG cc1, `sq`-prologue group), and `ee-2.9-991111`
  (older Sony/Cygnus cc1 for the statically-linked newlib — 64-bit `sd`
  callee-saves in 16-byte slots). The original game mixed all three.
- Flags: `-O2 -G0` with per-TU overrides recorded in `compile_config.json`.
