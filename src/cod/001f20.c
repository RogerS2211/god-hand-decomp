#include "include_asm.h"

/* -- PERMANENT (bnel/beql) — stay in monolithic asm/cod/000000 ------------ */
/* func_001F20F8 (beql+bnel, 0x324 B) stays in monolithic — PERMANENT.      */
/* func_001F2428 (bnel, 0x110 B) stays in monolithic — PERMANENT.           */
/* func_001F2540 (beql+bnel, 0x108 B) stays in monolithic — PERMANENT.      */
/* func_001F2650 (bnel, 0x40 B) stays in monolithic — PERMANENT.            */

/* -- Ghidra fragment (no jr $ra) — stay in monolithic asm/cod/000000 ------ */
/* func_001F26F0 (5 insn, no jr $ra) stays in monolithic — FRAGMENT.        */
/* func_001F27A8 (1 insn, no jr $ra) stays in monolithic — FRAGMENT.        */

/* -- Accessor C bodies (5) — jr $ra; nop empty functions ------------------ */

/* jr $ra; nop */
__attribute__((section(".text.Obj1F20_NoOp_20F0")))
void Obj1F20_NoOp_20F0(void) {}

/* jr $ra; nop */
__attribute__((section(".text.Obj1F20_NoOp_2420")))
void Obj1F20_NoOp_2420(void) {}

/* jr $ra; nop */
__attribute__((section(".text.Obj1F20_NoOp_2538")))
void Obj1F20_NoOp_2538(void) {}

/* jr $ra; nop */
__attribute__((section(".text.Obj1F20_NoOp_2648")))
void Obj1F20_NoOp_2648(void) {}

/* jr $ra; nop */
__attribute__((section(".text.Obj1F20_NoOp_2690")))
void Obj1F20_NoOp_2690(void) {}

/* -- Call-chain (nonmatching) --------------------------------------------- */
INCLUDE_ASM("nonmatching", func_001F2698);
INCLUDE_ASM("nonmatching", func_001F2708);
INCLUDE_ASM("nonmatching", func_001F27B0);
