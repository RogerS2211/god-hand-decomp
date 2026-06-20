#include "include_asm.h"

/* ── PERMANENT (1 via this TU) — bc1tl+fp-heavy, 0 VU0 — ee-as safe ──── */

/* func_0015F0B8: bnel+beql+bc1tl+fp-heavy, 0 VU0 insns, 0x1DC B.
 * Assembled via ee-as through this TU's INCLUDE_ASM. bc1tl does not
 * trigger VU0 pipeline nop insertion. */
INCLUDE_ASM("permanent", func_0015F0B8);

/* ── CALL-CHAIN (1) — jal, hardcoded args — nonmatching ───────────────── */

/* func_0015F2B0: addiu $sp,-0x10; addiu $a2,1; sd $ra; daddu $a3,0;
 *               addiu $t0,8; jal Gp_draw_poly4; addiu $t1,2; ld $ra; jr; addiu $sp,0x10
 *               0x28 B — hardcoded-arg call chain, INCLUDE_ASM pending match */
INCLUDE_ASM("nonmatching", func_0015F2B0);

/* ── ACCESSOR (4 remaining) — SP-trampoline stubs, no jr $ra ───────────── */

/* func_0015F0B0: addiu $sp, $sp, 0x100  (1 insn, no jr $ra, 0x4 B)
 *               Stack-adjustment trampoline; trailing nop (0x5F0B4) in retail.
 *               Cannot be expressed as a standard C function. */
INCLUDE_ASM("nonmatching", func_0015F0B0);

/* func_0015F298: addiu $sp, $sp, 0x30; nop; addiu $sp, $sp, 0x120
 *               (3 insns, net +0x150 stack adjustment, no jr $ra, 0xC B)
 *               Cannot be expressed as a standard C function. */
INCLUDE_ASM("nonmatching", func_0015F298);

/* func_0015F2D8: addiu $sp, $sp, 0x50  (1 insn, no jr $ra, 0x4 B)
 *               Cannot be expressed as a standard C function. */
INCLUDE_ASM("nonmatching", func_0015F2D8);

/* func_0015F6F0: addiu $sp, $sp, 0x80; nop; addiu $sp, $sp, 0x180
 *               (3 insns, net +0x200 stack adjustment, no jr $ra, 0xC B)
 *               Cannot be expressed as a standard C function. */
INCLUDE_ASM("nonmatching", func_0015F6F0);
