#include "godhand/vu0.h"

#include "include_asm.h"
extern void func_0028EB00(void *obj);

/* Vtable pointer (loaded into obj+0x214). Lives in .rodata at 0x0044A528. */
extern int D_0044A528;

/* Type-name string (loaded into obj+0x4AC). Lives in .rodata at 0x0044A510. */
extern int D_0044A510;

/* func_0028E018 — sq + VU0 + byte-store object constructor (80 B / 20 insns); see file header.
 *
 * Retail (asm/cod/000000.s, 0x0028E018..0x0028E067, 80 B):
 *
 *   addiu  $sp, $sp, -0x20
 *   sq     $s0, 0x10($sp)
 *   sd     $ra, 0x0($sp)
 *   jal    func_0028EB00
 *    daddu $s0, $a0, $zero
 *   lui    $v1, %hi(D_0044A528)
 *   addiu  $a0, $s0, 0x1510                # pointer-temp: a0 = obj + 0x1510
 *   addiu  $v1, $v1, %lo(D_0044A528)
 *   sw     $v1, 0x214($s0)                 # vtable store
 *   sqc2   $vf0, 0x1520($s0)
 *   addiu  $v1, $zero, 0xFF                # v1 reused for 0xFF immediate
 *   lui    $v0, %hi(D_0044A510)            # type-name LUI staged early (interleaves with sb)
 *   sb     $v1, 0x31($a0)                  # byte store at obj+0x1541
 *   addiu  $v0, $v0, %lo(D_0044A510)
 *   sw     $v0, 0x4AC($s0)                 # type-name store
 *   daddu  $v0, $s0, $zero                 # return value = obj
 *   ld     $ra, 0x0($sp)
 *   lq     $s0, 0x10($sp)
 *   jr     $ra
 *    addiu $sp, $sp, 0x20
 */
/* REGRESSED to nonmatching: the byte-match required a
 * forced-register pin (`register ... __asm__("$N")`), which is not a
 * real C match.  Reverted to INCLUDE_ASM pending an authentic re-match
 * (restructure -> decomp-permuter -> C++ TU).  Retail asm + matching
 * analysis preserved in the comments above for the retry. */
INCLUDE_ASM("nonmatching", func_0028E018);

