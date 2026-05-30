#include "godhand/vu0.h"

#include "include_asm.h"
/* Sibling init helper — shared with R-VU0, R-VU0-2, R-VU0-3 (same
 * func_0028EB00 instance). */
extern void func_0028EB00(void *obj);

/* Vtable pointer (loaded into obj+0x214 by func_00278068).
 * Lives in .rodata at 0x00447D48 as a sequence of `.word` function
 * pointers.  Declared `extern int` per the vtable-pointer-store
 * convention (the `int **` LHS cast pattern from R-VU0 / R-VU0-2 /
 * R-VU0-3).
 */
extern int D_00447D48;

/* Type-name string (loaded into obj+0x4AC by func_00278068).
 * Lives in .rodata at 0x00447CB0; the per-rep type-info asciz
 * label (typical 5-7 byte name + NUL).
 */
extern int D_00447CB0;

/* func_00278068 — sq + VU0 object constructor (84 B / 21 insns); see file header.
 *
 * Retail (asm/cod/000000.s, 0x00278068..0x002780BB, 84 B):
 *
 *   addiu  $sp, $sp, -0x20
 *   sq     $s0, 0x10($sp)        # sq callee-save
 *   sd     $ra, 0x0($sp)
 *   jal    func_0028EB00
 *    daddu $s0, $a0, $zero       # delay: save obj
 *   lui    $v1, %hi(D_00447D48)
 *   addiu  $v1, $v1, %lo(D_00447D48)
 *   sw     $v1, 0x214($s0)       # vtable
 *   sqc2   $vf0, 0x1530($s0)
 *   sqc2   $vf0, 0x1540($s0)
 *   sqc2   $vf0, 0x1550($s0)
 *   sqc2   $vf0, 0x1590($s0)
 *   sqc2   $vf0, 0x15A0($s0)
 *   lui    $v1, %hi(D_00447CB0)
 *   daddu  $v0, $s0, $zero       # return value = obj
 *   addiu  $v1, $v1, %lo(D_00447CB0)
 *   ld     $ra, 0x0($sp)
 *   sw     $v1, 0x4AC($s0)       # type-name
 *   lq     $s0, 0x10($sp)
 *   jr     $ra
 *    addiu $sp, $sp, 0x20
 */
/* REGRESSED to nonmatching: the byte-match required a
 * forced-register pin (`register ... __asm__("$N")`), which is not a
 * real C match.  Reverted to INCLUDE_ASM pending an authentic re-match
 * (restructure -> decomp-permuter -> C++ TU).  Retail asm + matching
 * analysis preserved in the comments above for the retry. */
INCLUDE_ASM("nonmatching", func_00278068);

