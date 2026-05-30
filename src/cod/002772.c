#include "godhand/vu0.h"

#include "include_asm.h"
/* Sibling init helper — shared with R-VU0 and R-VU0-2 (same
 * func_0028EB00 instance).  Declared `extern void` to accept any
 * single-arg object pointer.
 */
extern void func_0028EB00(void *obj);

/* Vtable pointer (loaded into obj+0x214 by func_002772A8).
 * Lives in .rodata at 0x00447BA0 as a sequence of `.word` function
 * pointers.  Declared `extern int` per the vtable-pointer-store
 * convention (the `int **` LHS cast pattern from R-VU0 / R-VU0-2).
 */
extern int D_00447BA0;

/* Type-name string (loaded into obj+0x4AC by func_002772A8).
 * Lives in .rodata at 0x00447B88; the per-rep type-info asciz
 * label (typical 5-7 byte name + NUL).
 */
extern int D_00447B88;

/* func_002772A8 — sq + VU0 object constructor (76 B / 19 insns); see file header.
 *
 * Retail (asm/cod/000000.s, 0x002772A8..0x002772F3, 76 B):
 *
 *   addiu  $sp, $sp, -0x20
 *   sq     $s0, 0x10($sp)        # sq callee-save
 *   sd     $ra, 0x0($sp)
 *   jal    func_0028EB00
 *    daddu $s0, $a0, $zero       # delay: save obj
 *   lui    $v1, %hi(D_00447BA0)
 *   addiu  $v1, $v1, %lo(D_00447BA0)
 *   sw     $v1, 0x214($s0)       # vtable
 *   sqc2   $vf0, 0x1530($s0)
 *   sqc2   $vf0, 0x1540($s0)
 *   sqc2   $vf0, 0x1550($s0)
 *   lui    $v1, %hi(D_00447B88)
 *   daddu  $v0, $s0, $zero       # return value = obj
 *   addiu  $v1, $v1, %lo(D_00447B88)
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
INCLUDE_ASM("nonmatching", func_002772A8);

