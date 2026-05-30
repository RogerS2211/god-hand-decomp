#include "include_asm.h"
#include "godhand/vu0.h"

/* Sibling init helper called from func_0027B768. */
extern void func_0028EB00(void *obj);

/* Vtable pointer (loaded into obj+0x214 by func_0027B768).
 * Lives in .rodata at 0x004481A8 as a sequence of `.word`
 * function pointers.  Declared `extern int` (matches the
 * `int **` LHS cast convention used by `src/cod/001b0b70.c`
 * for the same vtable-pointer-store shape — see
 * `func_001B0B70`).  See asm/data/cod/31B580.rodata.s.
 */
extern int D_004481A8;

/* Type-name string (loaded into obj+0x4AC by func_0027B768).
 * Lives in .rodata at 0x004480E0 as `.asciz "cEm63"`. */
extern int D_004480E0;

/* func_0027B768 — object constructor; calls init helper, sets
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
/* REGRESSED to nonmatching: the byte-match required a
 * forced-register pin (`register ... __asm__("$N")`), which is not a
 * real C match.  Reverted to INCLUDE_ASM pending an authentic re-match
 * (restructure -> decomp-permuter -> C++ TU).  Retail asm + matching
 * analysis preserved in the comments above for the retry. */
INCLUDE_ASM("nonmatching", func_0027B768);

