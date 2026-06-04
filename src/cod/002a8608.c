/* SN ProDG ee-gcc 2.95.3 matched TU. */
/* src/cod/002a86.c — func_002A8608: 6-arg actor-spawn / move setup wrapper.
 *
 * Builds a 0x7C-byte stack descriptor (3x sqc2 $vf0 zero-quads at 0x10/0x20/
 * 0x60, floats initialised to 1.0, sentinel bytes, scratch ints cleared),
 * writes t0 -> *(a0+0x574) and a3 -> *(u16*)(a0+0x570), then dispatches to
 * func_00306528(a1, a2, src, &desc, a3, a0) on the t1!=0 / t1==0 branch.
 * Hot: 180 call sites via func_0021A538's siblings.
 *
 * NON_MATCHING partial.  Default `us` build uses the byte-exact
 * `#else INCLUDE_ASM` carve (sha256 unchanged); `us-nm` scores this clean-C.
 * Exact match owed (sn-2.95.3-136): the residual is a stack base-pointer /
 * temp register-allocation + immediate-folding permutation.  Two real bugs
 * fixed during recovery: a3 is `int` (retail does no sign-extend), and the
 * sqc2 $vf0 zero-quad idiom is correct (objdump mislabels the identical
 * bytes as `sdc2 $0`).  Permuter-pending. */
#include "include_asm.h"
#include "godhand/vu0.h"

extern int func_00306528();

#ifdef NON_MATCHING
typedef struct {
    float f00;      /* 0x00 */
    float f04;      /* 0x04 */
    float f08;      /* 0x08 */
    float f0C;      /* 0x0C */
    char  q10[0x10];/* 0x10 sqc2 */
    char  q20[0x10];/* 0x20 sqc2 */
    float f30;      /* 0x30 */
    float f34;      /* 0x34 */
    float f38;      /* 0x38 */
    float f3C;      /* 0x3C */
    float f40;      /* 0x40 */
    int   i44;      /* 0x44 */
    int   i48;      /* 0x48 */
    signed char b4C;/* 0x4C */
    signed char b4D;/* 0x4D */
    signed char b4E;/* 0x4E */
    signed char b4F;/* 0x4F */
    int   i50;      /* 0x50 */
    char  pad54[0xC];/* 0x54 */
    char  q60[0x10];/* 0x60 sqc2 */
    short h70;      /* 0x70 */
    short h72;      /* 0x72 */
    signed char b74;/* 0x74 */
    char  pad75[3]; /* 0x75 */
    int   i78;      /* 0x78 */
} S;

__attribute__((section(".text.func_002A8608")))
void func_002A8608(void *a0, int a1, void *a2, int a3, int t0, void *t1) {
    S s;
    s.f00 = 1.0f;
    s.f04 = 1.0f;
    s.f08 = 1.0f;
    s.f0C = 1.0f;
    VU0_SQC2_VF0(&s, 0x10);
    VU0_SQC2_VF0(&s, 0x20);
    s.f30 = 1.0f;
    s.f3C = 1.0f;
    s.f34 = 1.0f;
    s.f38 = 1.0f;
    s.f40 = 1.0f;
    s.b4C = -1;
    s.b4F = 0xFF;
    s.i44 = 0;
    s.i48 = 0;
    s.b4D = 0;
    s.b4E = 0;
    s.i50 = 0;
    VU0_SQC2_VF0(&s, 0x60);
    *(int *)((char *)a0 + 0x574) = t0;
    s.h70 = 0;
    s.h72 = 0;
    s.b74 = 0;
    s.i78 = 0;
    *(unsigned short *)((char *)a0 + 0x570) = a3;
    if (t1 != 0) {
        if (a0 != 0) {
            s.f40 = *(float *)((char *)a0 + 0x114);
        }
        func_00306528(a1, a2, t1, &s, a3, a0);
    } else {
        if (a0 != 0) {
            if (*(unsigned short *)((char *)a0 + 0x434) & 2) {
                s.i48 |= 0x80;
                s.f40 = *(float *)((char *)a0 + 0x114);
            }
        }
        func_00306528(a1, a2, a0, &s, a3, a0);
    }
}
#else
INCLUDE_ASM("nonmatching", func_002A8608);
#endif
