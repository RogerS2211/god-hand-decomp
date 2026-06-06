# Style & naming conventions

God Hand is a C++ game built with ee-gcc 2.95.3 / SN ProDG. The decomp recovers
real names where the retail binary's embedded symbol table provides them, and uses
descriptive placeholders elsewhere. Placeholders are always preferred over guessed
names.

## Files & translation units

- **One source file = one original translation unit.** A recovered C++ class is a
  TU, so it gets its own file named after the class: `src/cod/<family>/<Class>.c`
  (e.g. `src/cod/sound/cSnd.c`, `src/cod/system/cCoreSave.c`).
- Functions not yet attributed to a recovered class live in **address-bucket files**
  `src/cod/<addr>.c`, named by the lowest carved address they contain.
- Subsystem **families** group related classes:
  `battle camera casino enemy event gfx id object player sound system ui`.
- Each recovered-class file opens with a one-line banner:
  `/* TU: <Class> [<family>] - recovered C++ class. */`.

## Names

| Kind | Convention | Example |
|------|------------|---------|
| Class method | `Class_method` (a valid C identifier) | `cSnd_BgmEvAllSuspend` |
| Free function | bare recovered name | `chack_point_line` |
| Overload collision | append the 6-hex address tail | `cEmWrap_setPos_2959B0` |
| Unrecovered function | descriptive `<Verb><Noun>` or `func_<addr>` | `ClearFields_13F2F8` |
| Global data | `g`-prefixed where known, else `D_<addr>` | `D_0044BED0` |
| Static / file-local | `s`-prefixed where known | `sFrameCount` |
| Struct / typedef | PascalCase | `CGUnk_00180310_t` |

## Hard rules

- **Byte-identity is the gate.** Every change must keep the linked ELF byte-identical
  to retail (`scripts/checks/build.sh`); matched C emits matching bytes, INCLUDE_ASM
  emits retail bytes, so the tracker can never be inflated.
- A confident recovered name supersedes an invented one; otherwise leave the existing
  name. Never invent a class/method name the binary doesn't attest.
- Keep source ASCII (the ee-gcc 2.95 toolchain is fed plain-ASCII source).
