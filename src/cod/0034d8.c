/* Struct: CGObj34D8_t — vec3 at +0x24 (CopyVec3); reaches +0x1F44 — likely an accessor view into a large entity object. */
#include "include_asm.h"

/* ── Forward declarations for external called functions ──────────────────── */
extern void func_003394A0(void);
extern void func_00339520(void);
extern void func_003571D0(void);
extern void func_0034D048(void);
extern void func_0034D068(void);
extern void func_0033B658(void);
extern void func_0033B670(void);
extern int  func_0034CA00(char *a0, int a1, int a2);

/* Internal forward decl (func_0034DD58 is defined later in this TU
 * but called by Obj34D8_Thunk_DD58 which appears first) */
extern void func_0034DD58(char *a0);

/* ── Extern globals ───────────────────────────────────────────────────────── */
extern char *D_003EE0B8;   /* set by Obj34D8_SetGlobalEE0B8_IfField48 */

/* ── INCLUDE_ASM("nonmatching") — complex call-chain / jalr / odd ─────────── */
INCLUDE_ASM("nonmatching", sfhds_AnlyAudio);
INCLUDE_ASM("nonmatching", sfhds_AnlyVideo);
INCLUDE_ASM("nonmatching", func_0034DA50);
INCLUDE_ASM("nonmatching", func_0034DA88);

/* ── Obj34D8_CopyVec3_From98_To934: copy 3 words via intermediate pointer ───────────────── */
/* addiu a1,a0,0x98; addiu a0,a0,0x90C; lw v0,4(a1); sw v0,0x24(a0);
 * lw v1,8(a1); sw v1,0x28(a0); lw v0,0xC(a1); jr $ra; sw v0,0x2C(a0) */
__attribute__((section(".text.Obj34D8_CopyVec3_From98_To934")))
void Obj34D8_CopyVec3_From98_To934(char *a0) {
    char *a1 = a0 + 0x98;
    a0 += 0x90C;
    *(int *)(a0 + 0x24) = *(int *)(a1 + 4);
    *(int *)(a0 + 0x28) = *(int *)(a1 + 8);
    *(int *)(a0 + 0x2C) = *(int *)(a1 + 0xC);
}

/* ── Obj34D8_GetTri78_Times100: branched index calc — if a0+0x78==0 return 0 else idx ── */
/* addiu a0,0x78; lw v1,0(a0); beqz v1,.L[delay:v0=0];
 * lw v1,4(a0); lw a0,8(a0); v0=v1*100+a0; jr; nop */
__attribute__((section(".text.Obj34D8_GetTri78_Times100")))
int Obj34D8_GetTri78_Times100(char *a0) {
    int v1;
    int base;
    a0 += 0x78;
    if (*(int *)a0 == 0) return 0;
    v1 = *(int *)(a0 + 4);
    base = *(int *)(a0 + 8);
    return v1 * 100 + base;
}

/* ── func_0034DB20: PERMANENT (bnel) ─────────────────────────────────────── */
INCLUDE_ASM("permanent", func_0034DB20);

/* ── func_0034DB48: single addiu $v0,$v0,0 — no jr $ra; unrepresentable ──── */
INCLUDE_ASM("nonmatching", func_0034DB48);

/* ── Cmp_a1_Eq_0x37B0: equality test a1 == 0x37B0 ───────────────────────────── */
/* xori v0,a1,0x37B0; jr $ra; sltiu v0,v0,1 */
__attribute__((section(".text.Cmp_a1_Eq_0x37B0")))
int Cmp_a1_Eq_0x37B0(int a0, int a1) {
    return a1 == 0x37B0;
}

/* ── INCLUDE_ASM("nonmatching") — call_chain (jal + bnel) ────────────────── */
INCLUDE_ASM("nonmatching", func_0034DB60);
INCLUDE_ASM("nonmatching", func_0034DBC8);

/* ── Obj34D8_ClearTwoWords_1FC: zero two words at a0+0x1FC / a0+0x200 ───────────────── */
/* addiu a0,a0,0x1FC; sw zero,4(a0); jr $ra; sw zero,0(a0) */
__attribute__((section(".text.Obj34D8_ClearTwoWords_1FC")))
void Obj34D8_ClearTwoWords_1FC(char *a0) {
    a0 += 0x1FC;
    *(int *)(a0 + 0) = 0;
    *(int *)(a0 + 4) = 0;
}

/* ── func_0034DC98: PERMANENT (bgezl loop) ───────────────────────────────── */
INCLUDE_ASM("permanent", func_0034DC98);

/* ── Obj34D8_Thunk_DD58: j-thunk → func_0034DD58 (5-insn trampoline) ─────────── */
__attribute__((section(".text.Obj34D8_Thunk_DD58")))
void Obj34D8_Thunk_DD58(char *a0) { func_0034DD58(a0); }

/* ── func_0034DD58: zero 5 words — compiler reorders; use nonmatching ─────── */
/* sw zero,0x10(a0); sw zero,0(a0); sw zero,4(a0); sw zero,8(a0);
 * jr $ra; sw zero,0xC(a0) */
INCLUDE_ASM("nonmatching", func_0034DD58);

/* ── INCLUDE_ASM("nonmatching") — call_chain + jalr-leaf ─────────────────── */
INCLUDE_ASM("nonmatching", func_0034DD70);
INCLUDE_ASM("nonmatching", func_0034DDE0);

/* ── INCLUDE_ASM("nonmatching") — call_chain with tail-j ─────────────────── */
INCLUDE_ASM("nonmatching", func_0034DE20);

/* ── Obj34D8_SetFields_0_4: store a2→a0+4, a1→a0+0 ─────────────────────────────── */
/* sw a2,4(a0); jr $ra; sw a1,0(a0) */
__attribute__((section(".text.Obj34D8_SetFields_0_4")))
void Obj34D8_SetFields_0_4(char *a0, int a1, int a2) {
    *(int *)(a0) = a1;
    *(int *)(a0 + 4) = a2;
}

/* ── Obj34D8_SetGlobalEE0B8_IfField48: branched set of D_003EE0B8 ───────────────────────────── */
/* beqz a0,.end[delay:v0=-1]; lw v1,0x48(a0); beqz v1,.end[delay:lui v1,hi];
 * daddu v0,0,0; sw a0,%lo(D_003EE0B8)(v1); .end: jr $ra; nop */
__attribute__((section(".text.Obj34D8_SetGlobalEE0B8_IfField48")))
int Obj34D8_SetGlobalEE0B8_IfField48(char *a0) {
    if (!a0) return -1;
    if (!*(int *)(a0 + 0x48)) return -1;
    D_003EE0B8 = a0;
    return 0;
}

/* ── Thunk_func_003394A0: j-thunk → func_003394A0 ─────────────────────────────── */
__attribute__((section(".text.Thunk_func_003394A0")))
void Thunk_func_003394A0(void) { func_003394A0(); }

/* ── Thunk_func_00339520: j-thunk → func_00339520 ─────────────────────────────── */
__attribute__((section(".text.Thunk_func_00339520")))
void Thunk_func_00339520(void) { func_00339520(); }

/* ── Call_3571D0_Then_4D048: jal func_003571D0 + j func_0034D048 ─────────────────── */
__attribute__((section(".text.Call_3571D0_Then_4D048")))
void Call_3571D0_Then_4D048(void) {
    func_003571D0();
    func_0034D048();
}

/* ── Thunk_func_0034D068: j-thunk → func_0034D068 ─────────────────────────────── */
__attribute__((section(".text.Thunk_func_0034D068")))
void Thunk_func_0034D068(void) { func_0034D068(); }

/* ── NoOp_DF58: void return (jr $ra; nop) ───────────────────────────── */
__attribute__((section(".text.NoOp_DF58")))
void NoOp_DF58(void) {}

/* ── NoOp_DF60: void return (jr $ra; nop) ───────────────────────────── */
__attribute__((section(".text.NoOp_DF60")))
void NoOp_DF60(void) {}

/* ── Thunk_func_0033B658: j-thunk → func_0033B658 ─────────────────────────────── */
__attribute__((section(".text.Thunk_func_0033B658")))
void Thunk_func_0033B658(void) { func_0033B658(); }

/* ── Thunk_func_0033B670: j-thunk → func_0033B670 ─────────────────────────────── */
__attribute__((section(".text.Thunk_func_0033B670")))
void Thunk_func_0033B670(void) { func_0033B670(); }

/* ── Return-0 accessors ─────────────────────────────────────────────────── */
__attribute__((section(".text.ReturnZero_DF98")))
int ReturnZero_DF98(void) { return 0; }

__attribute__((section(".text.ReturnZero_DFA0")))
int ReturnZero_DFA0(void) { return 0; }

/* ── Obj34D8_Call4CA00_With1F44_ReturnZero: call func_0034CA00(a0, *(a0+0x1F44), 1) + return 0 ──── */
/* addiu a2,0,1; sd $ra; jal func_0034CA00[delay:lw a1,0x1F44(a0)];
 * daddu v0,0,0; ld $ra; jr $ra; addiu $sp */
__attribute__((section(".text.Obj34D8_Call4CA00_With1F44_ReturnZero")))
int Obj34D8_Call4CA00_With1F44_ReturnZero(char *a0) {
    func_0034CA00(a0, *(int *)(a0 + 0x1F44), 1);
    return 0;
}

/* ── More return-0 accessors ─────────────────────────────────────────────── */
__attribute__((section(".text.ReturnZero_DFD0")))
int ReturnZero_DFD0(void) { return 0; }

__attribute__((section(".text.ReturnZero_DFD8")))
int ReturnZero_DFD8(void) { return 0; }

__attribute__((section(".text.ReturnZero_DFE0")))
int ReturnZero_DFE0(void) { return 0; }

__attribute__((section(".text.ReturnZero_DFE8")))
int ReturnZero_DFE8(void) { return 0; }

__attribute__((section(".text.ReturnZero_DFF0")))
int ReturnZero_DFF0(void) { return 0; }

__attribute__((section(".text.ReturnZero_DFF8")))
int ReturnZero_DFF8(void) { return 0; }
