#include "godhand/vu0.h"

/* func_0030A4E8 — VU0 scalar*vector (broadcast): *a0 = *a1 * s (xyzw). */

__attribute__((section(".text.func_0030A4E8")))
void func_0030A4E8(void *a0, void *a1, float s) {
    VU0_LQC2(4, a1, 0);
    VU0_LOAD_SCALAR(5, s);
    VU0_VMULX_XYZW(6, 4, 5);
    VU0_SQC2(6, a0, 0);
}
