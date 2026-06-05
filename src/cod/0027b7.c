#include "include_asm.h"
#include "godhand/vu0.h"

/* Sibling init helper called from InitObjVtable_27B768. */
extern void func_0028EB00(void *obj);

/* Vtable pointer (loaded into obj+0x214 by InitObjVtable_27B768).
 * Lives in .rodata at 0x004481A8 as a sequence of `.word`
 * function pointers.  Declared `extern int` (matches the
 * `int **` LHS cast convention used by `src/cod/001b0b70.c`
 * for the same vtable-pointer-store shape — see
 * `InitPilotVtable_1B0B70`).  See asm/data/cod/31B580.rodata.s.
 */
extern int D_004481A8;

/* Type-name string (loaded into obj+0x4AC by InitObjVtable_27B768).
 * Lives in .rodata at 0x004480E0 as `.asciz "cEm63"`. */
extern int D_004480E0;

/* InitObjVtable_27B768 — object constructor; calls init helper, sets
 * vtable + 6 quadword zero-inits + type-name pointer, returns
 * the object.  See file-level comment for the VU0 idiom and
 * the empirical findings on ee-as nop behaviour.
 *
 * Retail (asm/cod/000000.s, 0x0027B768..0x0027B7BF, 88 B):
 *
 *   addiu  $sp, $sp, -0x20
 *   sq     $s0, 0x10($sp)
 *   sd     $ra, 0x0($sp)
 *   jal    func_0028EB00
 *    daddu $s0, $a0, $zero       # delay slot: save obj
 *   lui    $v1, %hi(D_004481A8)
 *   addiu  $v1, $v1, %lo(D_004481A8)
 *   sw     $v1, 0x214($s0)
 *   sqc2   $vf0, 0x1530($s0)
 *   sqc2   $vf0, 0x1540($s0)
 *   sqc2   $vf0, 0x1550($s0)
 *   sqc2   $vf0, 0x1590($s0)
 *   sqc2   $vf0, 0x15A0($s0)
 *   sqc2   $vf0, 0x15C0($s0)
 *   lui    $v1, %hi(D_004480E0)
 *   daddu  $v0, $s0, $zero       # return value = obj
 *   addiu  $v1, $v1, %lo(D_004480E0)
 *   ld     $ra, 0x0($sp)
 *   sw     $v1, 0x4AC($s0)
 *   lq     $s0, 0x10($sp)
 *   jr     $ra
 *    addiu $sp, $sp, 0x20
 */
/* Clean-C body kept behind NON_MATCHING; the #else INCLUDE_ASM fallback keeps the
 * default (byte-identical) build exact. scripts/score_nm.sh compiles this body and
 * scores it as a fuzzy partial in the published progress report. */
#ifdef NON_MATCHING
__attribute__((section(".text.InitObjVtable_27B768")))
void *InitObjVtable_27B768(void *obj) {
    int *vtable;
    int *type_name;
    func_0028EB00(obj);
    vtable = &D_004481A8;
    *(int **)((char *)obj + 0x214) = vtable;
    VU0_SQC2_VF0(obj, 0x1530);
    VU0_SQC2_VF0(obj, 0x1540);
    VU0_SQC2_VF0(obj, 0x1550);
    VU0_SQC2_VF0(obj, 0x1590);
    VU0_SQC2_VF0(obj, 0x15A0);
    VU0_SQC2_VF0(obj, 0x15C0);
    type_name = &D_004480E0;
    *(int **)((char *)obj + 0x4AC) = type_name;
    return obj;
}
#else
INCLUDE_ASM("nonmatching", InitObjVtable_27B768);
#endif

