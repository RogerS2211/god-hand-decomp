#include "godhand/vu0.h"

#include "include_asm.h"
/* Sibling init helper called from func_0028B0F0.  Same helper used by
 * func_0027B768 (see src/cod/0027b7.c).  Declared `extern void` to
 * accept any single-arg object pointer.
 */
extern void func_0028EB00(void *obj);

/* Vtable pointer (loaded into obj+0x214 by func_0028B0F0).
 * Lives in .rodata at 0x0044A408 as a sequence of `.word` function
 * pointers (asm/data/cod/31B580.rodata.s line 222913).  Declared as
 * `extern int` matching the project's vtable-pointer-store convention
 * (the `int **` LHS cast pattern from src/cod/001b0b70.c::func_001B0B70
 * + src/cod/0027b7.c::func_0027B768).
 */
extern int D_0044A408;

/* Type-name string (loaded into obj+0x4AC by func_0028B0F0).
 * Lives in .rodata at 0x00448F30 as `.asciz "cEma6"` (6 bytes incl. NUL).
 */
extern int D_00448F30;

/* func_0028B0F0 — object constructor (88 B / 22 insns); see file header.
 *
 * Retail (asm/cod/000000.s, 0x0028B0F0..0x0028B147, 88 B):
 *
 *   addiu  $sp, $sp, -0x20
 *   sq     $s0, 0x10($sp)
 *   sd     $ra, 0x0($sp)
 *   jal    func_0028EB00
 *    daddu $s0, $a0, $zero      # delay slot: save obj
 *   lui    $v1, %hi(D_0044A408)
 *   addiu  $a0, $s0, 0x1510     # a0 = obj + 0x1510 (pointer temp)
 *   addiu  $v1, $v1, %lo(D_0044A408)
 *   sw     $v1, 0x214($s0)      # vtable
 *   sqc2   $vf0, 0x1520($s0)
 *   addiu  $v0, $zero, 0xFF
 *   sb     $v0, 0x31($a0)       # 0xFF at obj+0x1541
 *   sqc2   $vf0, 0x1590($s0)
 *   sqc2   $vf0, 0x1610($s0)
 *   lui    $v1, %hi(D_00448F30)
 *   daddu  $v0, $s0, $zero      # return value = obj
 *   addiu  $v1, $v1, %lo(D_00448F30)
 *   ld     $ra, 0x0($sp)
 *   sw     $v1, 0x4AC($s0)      # type-name
 *   lq     $s0, 0x10($sp)
 *   jr     $ra
 *    addiu $sp, $sp, 0x20
 */
/* Clean-C body kept behind NON_MATCHING; the #else INCLUDE_ASM fallback keeps the
 * default (byte-identical) build exact. scripts/score_nm.sh compiles this body and
 * scores it as a fuzzy partial in the published progress report. */
#ifdef NON_MATCHING
__attribute__((section(".text.func_0028B0F0")))
void *func_0028B0F0(void *obj) {
    int *vtable;
    int *type_name;
    unsigned char *p;

    func_0028EB00(obj);
    vtable = &D_0044A408;
    p = (unsigned char *)obj + 0x1510;
    *(int **)((char *)obj + 0x214) = vtable;
    VU0_SQC2_VF0(obj, 0x1520);
    p[0x31] = 0xFF;
    VU0_SQC2_VF0(obj, 0x1590);
    VU0_SQC2_VF0(obj, 0x1610);
    type_name = &D_00448F30;
    *(int **)((char *)obj + 0x4AC) = type_name;
    return obj;
}
#else
INCLUDE_ASM("nonmatching", func_0028B0F0);
#endif

