#include "godhand/vu0.h"

/* capVu0LengthAB — 3D distance between a0 and a1: length of (a0 - a1) via the
 * VU0 Q/sqrt pipeline. vsqrt emitted as its exact .word. */

__attribute__((section(".text.capVu0LengthAB")))
float capVu0LengthAB(void *a0, void *a1) {
    float r;
    int t;
    VU0_LQC2(4, a0, 0);
    VU0_LQC2(5, a1, 0);
    VU0_VSUB_XYZ(4, 4, 5);
    VU0_VMUL_XYZ(4, 4, 4);
    VU0_VADDY_X(4, 4);
    VU0_VADDZ_X(4, 4, 4);
    __asm__ __volatile__(".set push\n.set noreorder\n.word 0x4A0403BD\n.set pop\n"); /* vsqrt Q, $vf4x */
    VU0_VWAITQ();
    VU0_VADDQ_X(4, 0);
    __asm__ __volatile__("qmfc2.ni %0, $vf4" : "=r"(t));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(r) : "r"(t));
    return r;
}
