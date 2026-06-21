#include "godhand/vu0.h"

/* capVu0MagnitudeXZ — XZ-plane distance between a0 and a1: sqrt of the squared
 * distance, computed on VU0 (the Q/sqrt pipeline) and returned as a float.
 * ee-as encodes `vsqrt Q, $vf4x` differently from retail, so it is emitted as
 * its exact .word. */

__attribute__((section(".text.capVu0MagnitudeXZ")))
float capVu0MagnitudeXZ(void *a0, void *a1) {
    float r;
    int t;
    VU0_LQC2(4, a0, 0);
    VU0_LQC2(5, a1, 0);
    VU0_VSUB_XZ(4, 4, 5);
    VU0_VMUL_XZ(4, 4, 4);
    VU0_VADDZ_X(4, 4, 4);
    __asm__ __volatile__(".set push\n.set noreorder\n.word 0x4A0403BD\n.set pop\n"); /* vsqrt Q, $vf4x */
    VU0_VWAITQ();
    VU0_VADDQ_X(4, 0);
    __asm__ __volatile__("qmfc2.ni %0, $vf4" : "=r"(t));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(r) : "r"(t));
    return r;
}
