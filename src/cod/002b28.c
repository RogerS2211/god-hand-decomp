/* Struct: CGObj2B28_t — u16 pair at +0x34/+0x38, field +0x8C (CopyU16/SetField34). */
#include "include_asm.h"

/* ── call-chain (3) — save $ra, call sub-function, return 0 ─────────── */

INCLUDE_ASM("nonmatching", func_002B2A30);
INCLUDE_ASM("nonmatching", func_002B2A58);

/* ── accessor leaves (14) ────────────────────────────────────────────── */

/*
 * func_002B2AE8 — 0x1C B (7 insns)
 * addiu v1,2; daddu v0,0; sb v1,A4; sb 0,3C; sb v1,70; jr; delay:sw 0,18
 * Store order and register assignment (v1 for constant, then v0 clobber) not
 * reproducible from straightforward C with -O2; leave as nonmatching.
 */
INCLUDE_ASM("nonmatching", func_002B2AE8);

/*
 * func_002B2B78 — 0x30 B (12 insns)
 * addiu v1,4; addiu v0,2; sb v1,A4; sb v0,70; sw 0,18; daddu v0,0;
 * lw v1,8C; lhu a1,2(v1); sb 0,3C; sh a1,94; jr; delay:sh 0,96
 * Uses v1 for const-4 and v0 for const-2 (compiler assigns v0 to return val
 * later via daddu); register allocation order not reproduced by naive C.
 */
INCLUDE_ASM("nonmatching", func_002B2B78);

/*
 * func_002B2BA8 — 0x30 B (12 insns)
 * Same shape as func_002B2B78 but A4=5; same register-allocation mismatch.
 */
INCLUDE_ASM("nonmatching", func_002B2BA8);

/*
 * Obj2B28_SetField34_To1_ReturnZero — 0x10 B (4 insns)
 * addiu v1,1; daddu v0,0; jr; delay:sw v1,0x34
 * Sets *(int*)(a0+0x34)=1; returns 0.
 */
__attribute__((section(".text.Obj2B28_SetField34_To1_ReturnZero")))
int Obj2B28_SetField34_To1_ReturnZero(char *a0) {
    *(int *)(a0 + 0x34) = 1;
    return 0;
}

/*
 * Obj2B28_SetField34_To2_ReturnZero — 0x10 B (4 insns)
 * addiu v1,2; daddu v0,0; jr; delay:sw v1,0x34
 * Sets *(int*)(a0+0x34)=2; returns 0.
 */
__attribute__((section(".text.Obj2B28_SetField34_To2_ReturnZero")))
int Obj2B28_SetField34_To2_ReturnZero(char *a0) {
    *(int *)(a0 + 0x34) = 2;
    return 0;
}

/*
 * Obj2B28_ReturnZero_F68 — 0x8 B (2 insns)
 * jr $ra; delay:daddu v0,0
 * Returns 0 (no side effects).
 */
__attribute__((section(".text.Obj2B28_ReturnZero_F68")))
int Obj2B28_ReturnZero_F68(char *a0) { return 0; }

/*
 * Obj2B28_ReturnZero_F70 — 0x8 B (2 insns)
 * jr $ra; delay:daddu v0,0
 * Returns 0 (no side effects).
 */
__attribute__((section(".text.Obj2B28_ReturnZero_F70")))
int Obj2B28_ReturnZero_F70(char *a0) { return 0; }

/*
 * Obj2B28_ReturnZero_F78 — 0x8 B (2 insns)
 * jr $ra; delay:daddu v0,0
 * Returns 0 (no side effects).
 */
__attribute__((section(".text.Obj2B28_ReturnZero_F78")))
int Obj2B28_ReturnZero_F78(char *a0) { return 0; }

/* ── call-chain (cont.) ──────────────────────────────────────────────── */

INCLUDE_ASM("nonmatching", func_002B2F80);

/* ── accessor leaves (cont.) ─────────────────────────────────────────── */

/*
 * Obj2B28_ReturnZero_FA8 — 0x8 B (2 insns)
 * jr $ra; delay:daddu v0,0
 * Returns 0 (no side effects).
 */
__attribute__((section(".text.Obj2B28_ReturnZero_FA8")))
int Obj2B28_ReturnZero_FA8(char *a0) { return 0; }

/*
 * func_002B2FB0 — 0x20 B (8 insns)
 * lw a1,8C; daddu v0,0; lw v1,14; lbu a2,2(a1);
 * ori v1,v1,0x200; sw v1,14; jr; delay:sb a2,0x31
 * Expected loads 0x8C ptr into a1 BEFORE loading 0x14 flags into v1.
 * Compiler produces the reverse order; leave as nonmatching.
 */
INCLUDE_ASM("nonmatching", func_002B2FB0);

/*
 * Obj2B28_ReturnZero_FD0 — 0x8 B (2 insns)
 * jr $ra; delay:daddu v0,0
 * Returns 0 (no side effects).
 */
__attribute__((section(".text.Obj2B28_ReturnZero_FD0")))
int Obj2B28_ReturnZero_FD0(char *a0) { return 0; }

/*
 * Obj2B28_CopyU16_8C2_To38_ReturnZero — 0x14 B (5 insns)
 * lw v1,8C; daddu v0,0; lhu a1,2(v1); jr; delay:sh a1,0x38
 * Copies u16 from *(p_8C)+2 to *(u16*)(a0+0x38); returns 0.
 */
__attribute__((section(".text.Obj2B28_CopyU16_8C2_To38_ReturnZero")))
int Obj2B28_CopyU16_8C2_To38_ReturnZero(char *a0) {
    *(unsigned short *)(a0 + 0x38) = *(unsigned short *)(*(int *)(a0 + 0x8C) + 2);
    return 0;
}

/*
 * Obj2B28_ReturnZero_FF0 — 0x8 B (2 insns)
 * jr $ra; delay:daddu v0,0
 * Returns 0 (no side effects).
 */
__attribute__((section(".text.Obj2B28_ReturnZero_FF0")))
int Obj2B28_ReturnZero_FF0(char *a0) { return 0; }

/*
 * Obj2B28_ReturnZero_FF8 — 0x8 B (2 insns)
 * jr $ra; delay:daddu v0,0
 * Returns 0 (no side effects).
 */
__attribute__((section(".text.Obj2B28_ReturnZero_FF8")))
int Obj2B28_ReturnZero_FF8(char *a0) { return 0; }
