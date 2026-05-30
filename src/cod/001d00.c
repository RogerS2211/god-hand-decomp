/* Struct: CGObj1D00_t — own fields +0x664/+0x665/+0x668; embeds shared CGStateBlock4 at +0x2F4 (shares the +0x2F4..+0x2F7 {reset,state,substate,arg} block with CGUnk_0010B5C8_t — likely a common CG base class). */
#include "include_asm.h"

/* ── PERMANENT (6) — fp-heavy / bnel — stay in monolithic asm/cod/000000 ── */
/* func_001D0090 (fp-heavy+bnel, 0x78 B) — PERMANENT */
/* func_001D0108 (fp-heavy, 0x38 B) — PERMANENT */
/* func_001D0140 (fp-heavy+bnel, 0x100 B) — PERMANENT */
/* func_001D0240 (fp-heavy+bnel, 0x100 B) — PERMANENT */
/* func_001D0340 (fp-heavy+bnel, 0xC8 B) — PERMANENT */
/* func_001D0408 (fp-heavy+bnel, 0xC8 B) — PERMANENT */

/* ── Group A: 6-insn, a0[2F7]=0, a0[2F6]=0 (5 functions) ────────────────── */
/* C order: 2F4, 2F5=V, 2F6, 2F7 → ASM: li; sb 2F7; sb v0·2F5; sb 2F4; jr; delay:2F6 */

/* addiu v0,6; sb zero,2F7; sb v0,2F5; sb zero,2F4; jr; delay:sb zero,2F6 */
__attribute__((section(".text.Obj1D00_ClearState_6")))
void Obj1D00_ClearState_6(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 6;
    a0[0x2F6] = 0;
    a0[0x2F7] = 0;
}

/* addiu v0,7; sb zero,2F7; sb v0,2F5; sb zero,2F4; jr; delay:sb zero,2F6 */
__attribute__((section(".text.Obj1D00_ClearState_7")))
void Obj1D00_ClearState_7(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0;
    a0[0x2F7] = 0;
}

/* addiu v0,8; sb zero,2F7; sb v0,2F5; sb zero,2F4; jr; delay:sb zero,2F6 */
__attribute__((section(".text.Obj1D00_ClearState_8")))
void Obj1D00_ClearState_8(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 8;
    a0[0x2F6] = 0;
    a0[0x2F7] = 0;
}

/* addiu v0,9; sb zero,2F7; sb v0,2F5; sb zero,2F4; jr; delay:sb zero,2F6 */
__attribute__((section(".text.Obj1D00_ClearState_9")))
void Obj1D00_ClearState_9(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 9;
    a0[0x2F6] = 0;
    a0[0x2F7] = 0;
}

/* addiu v0,0xA; sb zero,2F7; sb v0,2F5; sb zero,2F4; jr; delay:sb zero,2F6 */
__attribute__((section(".text.Obj1D00_ClearState_A")))
void Obj1D00_ClearState_A(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 0xA;
    a0[0x2F6] = 0;
    a0[0x2F7] = 0;
}

/* ── Group D: 6-insn, a0[2F5]=a0[2F6]=6, a0[2F7]=a1 (1 function) ────────── */
/* C order: 2F5, 2F7, 2F6, 2F4 → ASM: li; sb a1·2F7; sb v0·2F6; sb 0·2F4; jr; delay:v0·2F5 */

/* addiu v0,6; sb a1,2F7; sb v0,2F6; sb zero,2F4; jr; delay:sb v0,2F5 */
__attribute__((section(".text.Obj1D00_SetState6_Variant6_a1")))
void Obj1D00_SetState6_Variant6_a1(char *a0, int a1) {
    a0[0x2F5] = 6;
    a0[0x2F7] = a1;
    a0[0x2F6] = 6;
    a0[0x2F4] = 0;
}

/* ── Group B: 8-insn, a0[2F7]=a1 (9 functions) ──────────────────────────── */
/* C order: 2F7=a1, 2F5=V, 2F6=W, 2F4=0 → ASM: li v0; li v1; sb a1·2F7; sb v0·2F5; sb v1·2F6; jr; delay:2F4 */

/* addiu v0,6; addiu v1,2; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_6_2_a1")))
void Obj1D00_SetState_6_2_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 6;
    a0[0x2F6] = 2;
    a0[0x2F4] = 0;
}

/* addiu v0,6; addiu v1,4; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_6_4_a1")))
void Obj1D00_SetState_6_4_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 6;
    a0[0x2F6] = 4;
    a0[0x2F4] = 0;
}

/* addiu v0,6; addiu v1,0xC; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_6_C_a1")))
void Obj1D00_SetState_6_C_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 6;
    a0[0x2F6] = 0xC;
    a0[0x2F4] = 0;
}

/* addiu v0,6; addiu v1,8; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_6_8_a1")))
void Obj1D00_SetState_6_8_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 6;
    a0[0x2F6] = 8;
    a0[0x2F4] = 0;
}

/* addiu v0,6; addiu v1,0xE; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_6_E_a1")))
void Obj1D00_SetState_6_E_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 6;
    a0[0x2F6] = 0xE;
    a0[0x2F4] = 0;
}

/* addiu v0,7; addiu v1,0xA; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_A_a1")))
void Obj1D00_SetState_7_A_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0xA;
    a0[0x2F4] = 0;
}

/* addiu v0,7; addiu v1,0xC; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_C_a1")))
void Obj1D00_SetState_7_C_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0xC;
    a0[0x2F4] = 0;
}

/* addiu v0,7; addiu v1,0xE; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_E_a1")))
void Obj1D00_SetState_7_E_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0xE;
    a0[0x2F4] = 0;
}

/* addiu v0,7; addiu v1,0x1A; sb a1,2F7; sb v0,2F5; sb v1,2F6; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_1A_a1")))
void Obj1D00_SetState_7_1A_a1(char *a0, int a1) {
    a0[0x2F7] = a1;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0x1A;
    a0[0x2F4] = 0;
}

/* ── Group C: 8-insn, a0[2F7]=0 (11 functions) ──────────────────────────── */
/* C order: 2F4=0, 2F5=V, 2F6=W, 2F7=0 → ASM: li v0; li v1; sb v0·2F5; sb v1·2F6; sb 0·2F7; jr; delay:2F4 */

/* addiu v0,6; addiu v1,0xA; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_6_A")))
void Obj1D00_SetState_6_A(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 6;
    a0[0x2F6] = 0xA;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,2; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_2")))
void Obj1D00_SetState_7_2(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 2;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,4; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_4")))
void Obj1D00_SetState_7_4(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 4;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,6; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_6")))
void Obj1D00_SetState_7_6(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 6;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,8; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_8")))
void Obj1D00_SetState_7_8(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 8;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,0x10; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_10")))
void Obj1D00_SetState_7_10(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0x10;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,0x12; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_12")))
void Obj1D00_SetState_7_12(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0x12;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,0x14; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_14")))
void Obj1D00_SetState_7_14(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0x14;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,0x16; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_16")))
void Obj1D00_SetState_7_16(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0x16;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,0x18; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_18")))
void Obj1D00_SetState_7_18(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0x18;
    a0[0x2F7] = 0;
}

/* addiu v0,7; addiu v1,0x1C; sb v0,2F5; sb v1,2F6; sb zero,2F7; jr; delay:2F4 */
__attribute__((section(".text.Obj1D00_SetState_7_1C")))
void Obj1D00_SetState_7_1C(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0x1C;
    a0[0x2F7] = 0;
}

/* ── Group E: 2-insn getters (2 functions) ───────────────────────────────── */
/* jr ra; lbu v0, offset(a0) */

/* jr ra; lbu v0, 0x664(a0) */
__attribute__((section(".text.Obj1D00_GetField_664")))
int Obj1D00_GetField_664(char *a0) {
    return (unsigned char)a0[0x664];
}

/* jr ra; lbu v0, 0x665(a0) */
__attribute__((section(".text.Obj1D00_GetField_665")))
int Obj1D00_GetField_665(char *a0) {
    return (unsigned char)a0[0x665];
}

/* ── Group F: BRANCHED-LEAF (1 function) ─────────────────────────────────── */
/* Obj1D00_TickTimer_668: pre-store + blez.
 *
 * Retail uses `blez v0, L` with `sw v0` in the always-executed delay slot.
 * Without -freorder-blocks the compiler emits `bgtz` (forward-to-return0);
 * with -freorder-blocks it reverses the block order, producing `blez`
 * (forward-to-return1, fall-through-to-return0) matching the retail.
 * -freorder-blocks is added globally to c_flags in compile_config.json
 * (follow-up); all other C-compiled functions are unaffected
 * (verified: same bytes with or without -freorder-blocks for all 28
 * previously matched functions in this TU and all other C TUs).
 *
 * Retail asm (0x24 B, 9 insns):
 *   lw v0, 0x668(a0); subu v0, v0, a1
 *   blez v0, L           ; delay slot: sw v0, 0x668(a0) — ALWAYS executes
 *   jr ra; daddu v0, 0, 0  ; return 0 (val > 0 fall-through)
 *   L: sw zero, 0x668(a0); jr ra; addiu v0, 0, 1  ; return 1
 */
__attribute__((section(".text.Obj1D00_TickTimer_668")))
int Obj1D00_TickTimer_668(char *a0, int a1) {
    int val = *(int *)(a0 + 0x668) - a1;
    *(int *)(a0 + 0x668) = val;
    if (val <= 0) { *(int *)(a0 + 0x668) = 0; return 1; }
    return 0;
}
