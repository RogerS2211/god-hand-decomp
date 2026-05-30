#include "godhand/vu0.h"

#include "include_asm.h"
extern void func_0028EB00(void *obj);

/* Vtable pointer (loaded into obj+0x214). Lives in .rodata at 0x00448598. */
extern int D_00448598;

/* Type-name string (loaded into obj+0x4AC). Lives in .rodata at 0x004484B0. */
extern int D_004484B0;

/* func_0027EE68 — sq + VU0 object constructor (84 B / 21 insns); see file header.
 *
 * Retail (asm/cod/000000.s, 0x0027EE68..0x0027EEBB, 84 B):
 *
 *   addiu  $sp, $sp, -0x20
 *   sq     $s0, 0x10($sp)
 *   sd     $ra, 0x0($sp)
 *   jal    func_0028EB00
 *    daddu $s0, $a0, $zero
 *   lui    $v1, %hi(D_00448598)
 *   addiu  $v1, $v1, %lo(D_00448598)
 *   sw     $v1, 0x214($s0)
 *   sqc2   $vf0, 0x1530($s0)
 *   sqc2   $vf0, 0x1540($s0)
 *   sqc2   $vf0, 0x1550($s0)
 *   sqc2   $vf0, 0x1590($s0)
 *   sqc2   $vf0, 0x15A0($s0)
 *   lui    $v1, %hi(D_004484B0)
 *   daddu  $v0, $s0, $zero
 *   addiu  $v1, $v1, %lo(D_004484B0)
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
INCLUDE_ASM("nonmatching", func_0027EE68);

