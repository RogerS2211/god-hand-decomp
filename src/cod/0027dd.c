#include "godhand/vu0.h"

#include "include_asm.h"
extern void func_0028EB00(void *obj);

/* Vtable pointer (loaded into obj+0x214). Lives in .rodata at 0x004483A8. */
extern int D_004483A8;

/* Type-name string (loaded into obj+0x4AC). Lives in .rodata at 0x004482B0. */
extern int D_004482B0;

/* func_0027DD88 — sq + VU0 object constructor with loop tail (140 B / 35 insns); see file header.
 *
 * Retail (asm/cod/000000.s, 0x0027DD88..0x0027DE13, 140 B):
 *
 *   addiu  $sp, $sp, -0x20
 *   sq     $s0, 0x10($sp)
 *   sd     $ra, 0x0($sp)
 *   jal    func_0028EB00
 *    daddu $s0, $a0, $zero
 *   lui    $v1, %hi(D_004483A8)
 *   addiu  $v1, $v1, %lo(D_004483A8)
 *   sw     $v1, 0x214($s0)
 *   sqc2   $vf0, 0x1530($s0)
 *   sqc2   $vf0, 0x1540($s0)
 *   sqc2   $vf0, 0x1550($s0)
 *   sqc2   $vf0, 0x1590($s0)
 *   sqc2   $vf0, 0x15A0($s0)
 *   sqc2   $vf0, 0x1610($s0)
 *   addiu  $a0, $zero, -0x1            # sentinel value held in $a0 across loop
 *   addiu  $v0, $s0, 0x1630            # p = obj + 0x1630
 *   addiu  $v1, $zero, 0x2B            # counter i = 0x2B (43)
 *   nop                                # .align 2 pad
 *  .L0027DDD0:
 *   sqc2   $vf0, 0x0($v0)
 *   sqc2   $vf0, 0x10($v0)
 *   sqc2   $vf0, 0x30($v0)
 *   sqc2   $vf0, 0x40($v0)
 *   sqc2   $vf0, 0x50($v0)
 *   sqc2   $vf0, 0x80($v0)
 *   addiu  $v1, $v1, -0x1              # i--
 *   bne    $v1, $a0, .L0027DDD0        # while (i != -1)
 *    addiu $v0, $v0, 0xA0              # delay: p += 0xA0
 *   lui    $v1, %hi(D_004482B0)
 *   daddu  $v0, $s0, $zero
 *   addiu  $v1, $v1, %lo(D_004482B0)
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
INCLUDE_ASM("nonmatching", func_0027DD88);

