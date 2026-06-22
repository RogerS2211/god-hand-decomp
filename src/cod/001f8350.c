#include "godhand/vu0.h"

/* func_001F8350 — VU0 3x3 matrix x vector via the COP2 accumulator:
 * *a0 = (mat a1) * (vec a2), with the vector's x/y/z broadcast across the
 * three matrix rows (vmulax / vmadday / vmaddz). */

__attribute__((section(".text.func_001F8350")))
void func_001F8350(void *a0, void *a1, void *a2) {
    VU0_LQC2(4, a2, 0);
    VU0_LQC2(5, a1, 0);
    VU0_LQC2(6, a1, 0x10);
    VU0_LQC2(7, a1, 0x20);
    VU0_VMULAX_XYZW(5, 4);
    VU0_VMADDAY_XYZW(6, 4);
    VU0_VMADDZ_XYZW(8, 7, 4);
    VU0_SQC2(8, a0, 0);
}
