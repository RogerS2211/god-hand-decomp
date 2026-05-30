/* Struct: CGObj293_t — flag/counter object; byte & bitfield block +0x500..+0x55C, counters +0x5A0..+0x5A5 (SetByte/OrByte/IsByteSet/PostIncCounter). */
#include "include_asm.h"

/* -- 13 accessor leaves (matched) ----------------------------- */

/* lw $v0, 0x55C($a0); addiu $v1, $v0, 1; jr $ra; sw $v1, 0x55C($a0) */
__attribute__((section(".text.Obj293_PostIncCounter_55C")))
int Obj293_PostIncCounter_55C(char *arg0) {
    int v = *(int *)(arg0 + 0x55C);
    *(int *)(arg0 + 0x55C) = v + 1;
    return v;
}

/* addiu $v0, $zero, 2; jr $ra; sb $v0, 0x53A($a0) */
__attribute__((section(".text.Obj293_SetByte_53A_2")))
void Obj293_SetByte_53A_2(char *arg0) { arg0[0x53A] = 2; }

/* addiu $v0, $zero, 0x3C; jr $ra; sb $v0, 0x53B($a0) */
__attribute__((section(".text.Obj293_SetByte_53B_3C")))
void Obj293_SetByte_53B_3C(char *arg0) { arg0[0x53B] = 0x3C; }

/* lb $v0, 0x53B($a0); jr $ra; sltu $v0, $zero, $v0 */
__attribute__((section(".text.Obj293_IsByteSet_53B")))
int Obj293_IsByteSet_53B(char *arg0) { return arg0[0x53B] != 0; }

/* addiu $v0, $zero, 2; jr $ra; sb $v0, 0x53C($a0) */
__attribute__((section(".text.Obj293_SetByte_53C_2")))
void Obj293_SetByte_53C_2(char *arg0) { arg0[0x53C] = 2; }

/* lb $v0, 0x53C($a0); jr $ra; sltu $v0, $zero, $v0 */
__attribute__((section(".text.Obj293_IsByteSet_53C")))
int Obj293_IsByteSet_53C(char *arg0) { return arg0[0x53C] != 0; }

/* addiu $v0, $zero, 2; jr $ra; sb $v0, 0x53D($a0) */
__attribute__((section(".text.Obj293_SetByte_53D_2")))
void Obj293_SetByte_53D_2(char *arg0) { arg0[0x53D] = 2; }

/* lb $v0, 0x53D($a0); jr $ra; sltu $v0, $zero, $v0 */
__attribute__((section(".text.Obj293_IsByteSet_53D")))
int Obj293_IsByteSet_53D(char *arg0) { return arg0[0x53D] != 0; }

/* jr $ra; lw $v0, 0x500($a0) */
__attribute__((section(".text.Obj293_GetWord_500")))
int Obj293_GetWord_500(char *arg0) { return *(int *)(arg0 + 0x500); }

/* func_00293138 (fp+bnel, 376 insn) stays in monolithic — PERMANENT. */

/* lbu $v0, 0x5A3($a0); or $v0, $v0, $a1; jr $ra; sb $v0, 0x5A3($a0) */
__attribute__((section(".text.Obj293_OrByte_5A3")))
void Obj293_OrByte_5A3(unsigned char *arg0, unsigned int arg1) {
    arg0[0x5A3] |= arg1;
}

/* sb $zero, 0x5A0($a0); jr $ra; sb $zero, 0x5A3($a0)
 * Note: ee-gcc 2.96's delay-slot scheduler chooses the wrong store
 * (it moves the FIRST store into the delay slot, giving 0x5A3 first
 * + 0x5A0 in delay) when both stores are simple `arg0[N] = 0;`.
 * Swapping the source order convinces the scheduler to land on the
 * retail shape (0x5A0 first, 0x5A3 in delay slot).  Verified by
 * byte-equal sha256 against `disc_extract/SLUS_215.03`. */
__attribute__((section(".text.Obj293_ClearBytes_5A0_5A3")))
void Obj293_ClearBytes_5A0_5A3(char *arg0) {
    arg0[0x5A3] = 0;
    arg0[0x5A0] = 0;
}

/* lbu $v0, 0x5A4($a0); or $v0, $v0, $a1; jr $ra; sb $v0, 0x5A4($a0) */
__attribute__((section(".text.Obj293_OrByte_5A4")))
void Obj293_OrByte_5A4(unsigned char *arg0, unsigned int arg1) {
    arg0[0x5A4] |= arg1;
}

/* lbu $v0, 0x5A5($a0); ori $v0, $v0, 0x1; jr $ra; sb $v0, 0x5A5($a0) */
__attribute__((section(".text.Obj293_OrByte_5A5_1")))
void Obj293_OrByte_5A5_1(unsigned char *arg0) { arg0[0x5A5] |= 1; }

/* func_00293760 (jump-table, 24 insn) stays in monolithic — PERMANENT.
 * 5-case computed-goto via D_0044A7B0; carving would orphan the local
 * .L00293794 / .L00293A14 / .L002941C0 / .L00294308 labels referenced
 * by the rodata switch table.  Registered under the new `jump-table`
 * permanent class (jump-table).  Re-expressing it as a `switch`
 * body is a future follow-up. */

/* func_002937C0 (fp+bnel, 288 insn) stays in monolithic — PERMANENT. */

/* func_00293C40 (fp+bnel, 530 insn) stays in monolithic — PERMANENT. */
