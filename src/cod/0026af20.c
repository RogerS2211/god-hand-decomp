/* SN ProDG ee-gcc 2.95.3 matched TU. */
/* src/cod/0026af.c — SetOrientByType_26AF20: 11-way effect-parameter loader.
 *
 * switch(a2) over a small set (0..10, case 0 == default) fills a 7-word stack
 * buffer (2x sqc2 $vf0 zero at 0x0/0x10) with per-case float literals (decoded
 * inline) + a count, then calls func_001CF160(a1, a0, count, buf, buf+0x10).
 * Early-out when a1 == 0.
 *
 * NON_MATCHING partial.  Default `us` build uses the byte-exact
 * `#else INCLUDE_ASM` carve (sha256 unchanged); `us-nm` scores this clean-C.
 * Exact match owed (sn-2.95.3-136): the residual is multi-point shared-tail
 * merges (sw zero packed into branch delay slots) + an $f0-$f4 constant-
 * materialisation schedule that clean C doesn't reproduce — the least
 * converged of the round.  Permuter-pending.  Uses macro.inc so the switch
 * jump-table head labels stay global for the rodata table referencing them
 * (carve folds the text out; --strip-all => sha256 unaffected). */
#define INCLUDE_ASM_USE_MACRO_INC 1
#include "include_asm.h"
#include "godhand/vu0.h"

extern int func_001CF160();

#ifdef NON_MATCHING
__attribute__((section(".text.SetOrientByType_26AF20")))
void SetOrientByType_26AF20(void *a0, int a1, unsigned int a2) {
    void *a3 = a0;
    float buf[7];   /* sp[0..0x18] */
    int count;
    if (a1 == 0) {
        return;
    }
    VU0_SQC2_VF0(buf, 0x0);
    VU0_SQC2_VF0(buf, 0x10);
    switch (a2) {
    case 0:
    default:
        buf[0] = -0.36f;          /* 0xBEB851EC */
        buf[1] = 0.43f;           /* 0x3EDC28F6 */
        buf[2] = -0.17f;          /* 0xBE2E147B */
        buf[4] = 1.5707964f;      /* 0x3FC90FDB (0x10) */
        buf[6] = 0.69813168f;     /* 0x3F32B8C2 (0x18) */
        *(int *)((char *)buf + 0x14) = 0;
        count = 2;
        break;
    case 8:
        buf[0] = 0.01f;           /* 0x3C23D70A */
        buf[1] = 0.15f;           /* 0x3E19999A */
        buf[2] = -0.17f;          /* 0xBE2E147B */
        buf[4] = 1.5707964f;      /* 0x3FC90FDB */
        buf[6] = 0.610865235f;    /* 0x3F1C61AA */
        *(int *)((char *)buf + 0x14) = 0;
        count = 2;
        break;
    case 1:
        buf[0] = 0.71f;           /* 0x3F35C28F */
        buf[1] = -0.044f;         /* 0xBD343958 */
        buf[2] = -0.054f;         /* 0xBD5D2F1B */
        buf[5] = -0.52359879f;    /* 0xBF060A92 (0x14) */
        *(int *)((char *)buf + 0x10) = 0;
        *(int *)((char *)buf + 0x18) = 0;
        count = 0x10;
        break;
    case 10:
        buf[0] = 0.1f;            /* 0x3DCCCCCD */
        buf[1] = -0.027f;         /* 0xBCDD2F1B */
        buf[2] = 0.01f;           /* 0x3C23D70A */
        buf[5] = 1.5707964f;      /* 0x3FC90FDB (0x14) */
        *(int *)((char *)buf + 0x10) = 0;
        *(int *)((char *)buf + 0x18) = 0;
        count = 0x10;
        break;
    case 2:
        buf[1] = 0.0974999964f;   /* 0x3DC7AE14 */
        buf[2] = 0.0189999994f;   /* 0x3C9BA5E3 */
        *(int *)((char *)buf + 0x0) = 0;
        *(int *)((char *)buf + 0x10) = 0;
        *(int *)((char *)buf + 0x14) = 0;
        count = 4;
        break;
    case 3:
        buf[0] = -0.2f;           /* 0xBE4CCCCD */
        buf[1] = -0.1f;           /* 0xBDCCCCCD */
        buf[2] = 0.08f;           /* 0x3DA3D70A */
        buf[4] = 2.70526028f;     /* 0x402D22FC (0x10) */
        buf[6] = 0.69813168f;     /* 0x3F32B8C2 (0x18) */
        *(int *)((char *)buf + 0x14) = 0;
        count = 0xA;
        break;
    case 9:
        buf[0] = 0.435f;          /* 0x3EDEB852 */
        buf[1] = -0.037f;         /* 0xBD178D50 */
        buf[2] = 0.296999991f;    /* 0x3E981062 */
        buf[5] = -0.785398185f;   /* 0xBF490FDB (0x14) */
        buf[6] = -3.14159274f;    /* 0xC0490FDB (0x18) */
        *(int *)((char *)buf + 0x10) = 0;
        count = 0x10;
        break;
    case 4:
        *(int *)((char *)buf + 0x0) = 0;
        *(int *)((char *)buf + 0x4) = 0;
        *(int *)((char *)buf + 0x8) = 0;
        *(int *)((char *)buf + 0x10) = 0;
        *(int *)((char *)buf + 0x14) = 0;
        count = 4;
        break;
    case 5:
        *(int *)((char *)buf + 0x0) = 0;
        *(int *)((char *)buf + 0x4) = 0;
        *(int *)((char *)buf + 0x8) = 0;
        *(int *)((char *)buf + 0x10) = 0;
        *(int *)((char *)buf + 0x14) = 0;
        count = 2;
        break;
    case 6:
        *(int *)((char *)buf + 0x0) = 0;
        *(int *)((char *)buf + 0x4) = 0;
        *(int *)((char *)buf + 0x8) = 0;
        *(int *)((char *)buf + 0x10) = 0;
        *(int *)((char *)buf + 0x14) = 0;
        count = 4;
        break;
    case 7:
        *(int *)((char *)buf + 0x0) = 0;
        *(int *)((char *)buf + 0x4) = 0;
        *(int *)((char *)buf + 0x8) = 0;
        *(int *)((char *)buf + 0x10) = 0;
        *(int *)((char *)buf + 0x14) = 0;
        count = 2;
        break;
    }
    *(int *)((char *)buf + 0x18) = 0;
    func_001CF160(a1, a3, count, buf, (char *)buf + 0x10);
}
#else
INCLUDE_ASM("nonmatching", SetOrientByType_26AF20);
/* Re-export the switch jump-table head label the .rodata table references
 * across the .o boundary (the labels.inc-assembled carve marks jlabels
 * local).  --strip-all => no effect on the final ELF bytes / sha256. */
__asm__(".globl .L0026AF5C\n");
#endif
