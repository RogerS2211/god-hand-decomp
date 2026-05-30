#include "include_asm.h"

/* ── External forward declarations ──────────────────────────────────────── */
extern void func_0033E678(void);   /* target of Obj3290_Tramp_0033E678_9028 trampoline     */
extern void func_0033E690(void);   /* target of Obj3290_Tramp_0033E690_9040 trampoline     */
extern void func_0033BF18(void);   /* target of Obj3290_Tramp_0033BF18_9058 trampoline     */
extern void func_0033E6A8(void);   /* target of Obj3290_Tramp_0033E6A8_9070 trampoline     */
extern void func_0033E6B0(void);   /* target of Obj3290_Tramp_0033E6B0_9088 trampoline     */
extern void func_0033F130(void *a0); /* target of Obj3290_TrampViaA1_0033F130_90A0 (arg-reroute)*/
extern void func_003313F0(void);   /* target of Obj3290_Tramp_003313F0_9278 trampoline     */
extern void func_003313E0(void);   /* target of Obj3290_Tramp_003313E0_9298 trampoline     */

/* ── External global ─────────────────────────────────────────────────────── */
extern int D_003D1400;   /* word-sized global; setter Obj3290_SetGlobal_D003D1400          */

/* ────────────────────────────────────────────────────────────────────────── */
/* call_chain — 6 functions (deferred)                    */
/* ────────────────────────────────────────────────────────────────────────── */

/* func_003290B8: 0x100 B, complex multi-jal init; calls func_003A50B4 ×2,
 * func_00330E70, func_00330318 ×2, func_00330580, func_00333E68, j func_00333E88 */
INCLUDE_ASM("nonmatching", func_003290B8);

/* func_003291B8: 0x5C B, branched call: lw args from *a0, jal func_00333CE0 */
INCLUDE_ASM("nonmatching", func_003291B8);

/* func_003292D8: 0x118 B, multi-jal init; calls func_00330E70, func_00330318 ×2,
 * func_00330580, func_00335218, func_00335248, func_00333F60, j func_00333F80 */
INCLUDE_ASM("nonmatching", func_003292D8);

/* func_00329438: 0x58 B, wraps func_0033E6A8 + func_00329490 + func_0033E6B0 */
INCLUDE_ASM("nonmatching", func_00329438);

/* func_003297A8: 0x48 B, wraps func_0033E6A8 + func_003297F0 + func_0033E6B0 */
INCLUDE_ASM("nonmatching", func_003297A8);

/* func_003297F0: 0x54 B, call func_00329490 then func_00336BA8 if result non-null */
INCLUDE_ASM("nonmatching", func_003297F0);

/* ────────────────────────────────────────────────────────────────────────── */
/* addiu-only / no-jr-ra stubs — unrepresentable in C (INCLUDE_ASM)          */
/* ────────────────────────────────────────────────────────────────────────── */

/* func_00329218: 0x44 B; 9×(addiu $sp,+0x10; nop) + 3×(addiu $sp,+0x30;nop) —
 * pure addiu-only epilogue fragments, no jr $ra; cannot be expressed as C   */
INCLUDE_ASM("nonmatching", func_00329218);

/* func_00329270: 0x4 B; lw $v0,0x30($v1) — no jr $ra, 1-insn fallthrough   */
INCLUDE_ASM("nonmatching", func_00329270);

/* func_00329290: 0x4 B; addiu $sp,$sp,0x10 — no jr $ra, addiu-only stub    */
INCLUDE_ASM("nonmatching", func_00329290);

/* func_003292B0: 0x28 B; 2×(addiu $sp,+0x10;nop) then real accessor body —
 * dead addiu prefix makes the function body unrepresentable in C             */
INCLUDE_ASM("nonmatching", func_003292B0);

/* func_003293F0: 0x44 B; addiu stubs interspersed with lw/sw, no jr $ra     */
INCLUDE_ASM("nonmatching", func_003293F0);

/* ────────────────────────────────────────────────────────────────────────── */
/* Accessor byte-matches — 9 functions                                        */
/* ────────────────────────────────────────────────────────────────────────── */

/* Obj3290_Tramp_0033E678_9028: addiu sp,-0x10; sd ra; ld ra; j func_0033E678; addiu sp,+0x10 */
__attribute__((section(".text.Obj3290_Tramp_0033E678_9028")))
void Obj3290_Tramp_0033E678_9028(void) { func_0033E678(); }

/* Obj3290_Tramp_0033E690_9040: addiu sp,-0x10; sd ra; ld ra; j func_0033E690; addiu sp,+0x10 */
__attribute__((section(".text.Obj3290_Tramp_0033E690_9040")))
void Obj3290_Tramp_0033E690_9040(void) { func_0033E690(); }

/* Obj3290_Tramp_0033BF18_9058: addiu sp,-0x10; sd ra; ld ra; j func_0033BF18; addiu sp,+0x10 */
__attribute__((section(".text.Obj3290_Tramp_0033BF18_9058")))
void Obj3290_Tramp_0033BF18_9058(void) { func_0033BF18(); }

/* Obj3290_Tramp_0033E6A8_9070: addiu sp,-0x10; sd ra; ld ra; j func_0033E6A8; addiu sp,+0x10 */
__attribute__((section(".text.Obj3290_Tramp_0033E6A8_9070")))
void Obj3290_Tramp_0033E6A8_9070(void) { func_0033E6A8(); }

/* Obj3290_Tramp_0033E6B0_9088: addiu sp,-0x10; sd ra; ld ra; j func_0033E6B0; addiu sp,+0x10 */
__attribute__((section(".text.Obj3290_Tramp_0033E6B0_9088")))
void Obj3290_Tramp_0033E6B0_9088(void) { func_0033E6B0(); }

/* Obj3290_TrampViaA1_0033F130_90A0: addiu sp,-0x10; daddu $a0,$a1,$zero; sd ra; ld ra;
 *               j func_0033F130; addiu sp,+0x10
 * Routes second argument ($a1) to func_0033F130 as first argument ($a0). */
__attribute__((section(".text.Obj3290_TrampViaA1_0033F130_90A0")))
void Obj3290_TrampViaA1_0033F130_90A0(void *a0, void *a1) { func_0033F130(a1); }

/* Obj3290_SetGlobal_D003D1400: lui $v0,%hi(D_003D1400); jr $ra; sw $a0,%lo(D_003D1400)($v0)
 * 3-insn setter: stores word $a0 to global D_003D1400 (sw in delay slot). */
__attribute__((section(".text.Obj3290_SetGlobal_D003D1400")))
void Obj3290_SetGlobal_D003D1400(int a0) { D_003D1400 = a0; }

/* Obj3290_Tramp_003313F0_9278: addiu sp,-0x10; sd ra; ld ra; j func_003313F0; addiu sp,+0x10 */
__attribute__((section(".text.Obj3290_Tramp_003313F0_9278")))
void Obj3290_Tramp_003313F0_9278(void) { func_003313F0(); }

/* Obj3290_Tramp_003313E0_9298: addiu sp,-0x10; sd ra; ld ra; j func_003313E0; addiu sp,+0x10 */
__attribute__((section(".text.Obj3290_Tramp_003313E0_9298")))
void Obj3290_Tramp_003313E0_9298(void) { func_003313E0(); }
