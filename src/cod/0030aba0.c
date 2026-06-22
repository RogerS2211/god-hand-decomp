#include "godhand/vu0.h"

/* func_0030ABA0 — VU0 scalar*vector, xyz only, in place: a0.xyz = a1.xyz * s. */

__attribute__((section(".text.func_0030ABA0")))
void func_0030ABA0(void *a0, void *a1, float s) {
    VU0_LQC2(4, a1, 0);
    VU0_LOAD_SCALAR(5, s);
    VU0_VMULX_XYZ(4, 4, 5);
    VU0_SQC2(4, a0, 0);
}
