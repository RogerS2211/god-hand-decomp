#include "godhand/vu0.h"

/* capVu0Length — 3D length of vector a0: sqrt(x*x + y*y + z*z) via the VU0
 * Q/sqrt pipeline. vsqrt emitted as its exact .word (ee-as encodes it
 * differently from retail). */

__attribute__((section(".text.capVu0Length")))
float capVu0Length(void *a0) {
    float r;
    int t;
    VU0_LQC2(4, a0, 0);
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
