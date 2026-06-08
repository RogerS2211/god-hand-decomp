/* SN ProDG ee-gcc 2.95.3 matched TU. */
/* src/cod/0027ea.c — ForwardAnimParamPairByIndex_27EA50: 50-way move-data field selector.
 *
 * switch(a1) over 0..49 (case 0 == default) picks a pair of field offsets
 * off the move-data block *(a0+0x304), then the shared tail calls
 * func_002A8578(a0, base+v1, base+a0v, 0.0f, 0xA, 0, 0).
 *
 * NON_MATCHING partial.  Default `us` build uses the byte-exact
 * `#else INCLUDE_ASM` carve (sha256 unchanged); `us-nm` scores this clean-C.
 * Exact match owed (sn-2.95.3-136): the prologue + dispatch + case 0 (first
 * 0x54 B) are already byte-exact; the residual is a single per-case
 * 2-register-nibble swap (retail loads case values into $v1/$a0 and adds the
 * base at the merge; clean C loads into $a1/$a2 and adds in place) — a
 * textbook reg-alloc permutation.  Permuter-pending; this is the strongest
 * close of the round.  Uses macro.inc so the switch jump-table head labels
 * stay global for the rodata table that references them (the carve folds the
 * function text out of the monolithic; --strip-all => sha256 unaffected). */
#define INCLUDE_ASM_USE_MACRO_INC 1
#include "include_asm.h"

extern void func_002A8578(void *a0, void *a1, void *a2, float f, int a3, int t0, int t1);

#ifdef NON_MATCHING
__attribute__((section(".text.ForwardAnimParamPairByIndex_27EA50")))
void ForwardAnimParamPairByIndex_27EA50(void *a0, unsigned int a1) {
    int g;
    int v1, a0v;
    switch (a1) {
    default:
    case 0:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xC);
        a0v = *(int *)((char *)g + 0x10);
        break;
    case 1:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x14);
        a0v = *(int *)((char *)g + 0x18);
        break;
    case 2:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x14);
        a0v = *(int *)((char *)g + 0x18);
        break;
    case 3:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x50);
        a0v = *(int *)((char *)g + 0x54);
        break;
    case 4:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x1C);
        a0v = *(int *)((char *)g + 0x20);
        break;
    case 5:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x1C);
        a0v = *(int *)((char *)g + 0x24);
        break;
    case 6:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x28);
        a0v = *(int *)((char *)g + 0x2C);
        break;
    case 7:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x68);
        a0v = *(int *)((char *)g + 0x6C);
        break;
    case 8:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x68);
        a0v = *(int *)((char *)g + 0x70);
        break;
    case 9:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x98);
        a0v = *(int *)((char *)g + 0x9C);
        break;
    case 10:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x98);
        a0v = *(int *)((char *)g + 0xA0);
        break;
    case 11:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xA4);
        a0v = *(int *)((char *)g + 0xA8);
        break;
    case 12:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xA4);
        a0v = *(int *)((char *)g + 0xAC);
        break;
    case 13:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xB0);
        a0v = *(int *)((char *)g + 0xB4);
        break;
    case 14:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xB0);
        a0v = *(int *)((char *)g + 0xB8);
        break;
    case 15:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xD4);
        a0v = *(int *)((char *)g + 0xD8);
        break;
    case 16:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xD4);
        a0v = *(int *)((char *)g + 0xDC);
        break;
    case 17:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x40);
        a0v = *(int *)((char *)g + 0x44);
        break;
    case 18:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x74);
        a0v = *(int *)((char *)g + 0x78);
        break;
    case 19:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x74);
        a0v = *(int *)((char *)g + 0x7C);
        break;
    case 20:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x80);
        a0v = *(int *)((char *)g + 0x84);
        break;
    case 21:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x88);
        a0v = *(int *)((char *)g + 0x8C);
        break;
    case 22:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x90);
        a0v = *(int *)((char *)g + 0x94);
        break;
    case 23:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x48);
        a0v = *(int *)((char *)g + 0x4C);
        break;
    case 24:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x170);
        a0v = *(int *)((char *)g + 0x174);
        break;
    case 25:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x178);
        a0v = *(int *)((char *)g + 0x17C);
        break;
    case 26:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x180);
        a0v = *(int *)((char *)g + 0x184);
        break;
    case 27:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x188);
        a0v = *(int *)((char *)g + 0x18C);
        break;
    case 28:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x30);
        a0v = *(int *)((char *)g + 0x34);
        break;
    case 29:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x38);
        a0v = *(int *)((char *)g + 0x3C);
        break;
    case 30:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x148);
        a0v = *(int *)((char *)g + 0x14C);
        break;
    case 31:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x150);
        a0v = *(int *)((char *)g + 0x154);
        break;
    case 32:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x158);
        a0v = *(int *)((char *)g + 0x15C);
        break;
    case 33:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x160);
        a0v = *(int *)((char *)g + 0x164);
        break;
    case 34:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x168);
        a0v = *(int *)((char *)g + 0x16C);
        break;
    case 35:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xE0);
        a0v = *(int *)((char *)g + 0xE4);
        break;
    case 36:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xE8);
        a0v = *(int *)((char *)g + 0xEC);
        break;
    case 37:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xF0);
        a0v = *(int *)((char *)g + 0xF4);
        break;
    case 38:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0xF8);
        a0v = *(int *)((char *)g + 0xFC);
        break;
    case 39:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x100);
        a0v = *(int *)((char *)g + 0x104);
        break;
    case 40:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x108);
        a0v = *(int *)((char *)g + 0x10C);
        break;
    case 41:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x110);
        a0v = *(int *)((char *)g + 0x114);
        break;
    case 42:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x118);
        a0v = *(int *)((char *)g + 0x11C);
        break;
    case 43:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x120);
        a0v = *(int *)((char *)g + 0x124);
        break;
    case 44:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x128);
        a0v = *(int *)((char *)g + 0x12C);
        break;
    case 45:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x130);
        a0v = *(int *)((char *)g + 0x134);
        break;
    case 46:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x138);
        a0v = *(int *)((char *)g + 0x13C);
        break;
    case 47:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x140);
        a0v = *(int *)((char *)g + 0x144);
        break;
    case 48:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x58);
        a0v = *(int *)((char *)g + 0x5C);
        break;
    case 49:
        g = *(int *)((char *)a0 + 0x304);
        v1 = *(int *)((char *)g + 0x60);
        a0v = *(int *)((char *)g + 0x64);
        break;
    }
    func_002A8578(a0, (void *)(v1 + g), (void *)(a0v + g), 0.0f, 0xA, 0, 0);
}
#else
INCLUDE_ASM("nonmatching", ForwardAnimParamPairByIndex_27EA50);
/* Re-export the switch jump-table head label the .rodata table references
 * across the .o boundary (the labels.inc-assembled carve marks jlabels
 * local).  --strip-all => no effect on the final ELF bytes / sha256. */
__asm__(".globl .L0027EA80\n");
#endif
