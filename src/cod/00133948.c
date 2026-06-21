#include "godhand/vu0.h"

/* func_00133948 — element-wise sort of two vectors: a1 = min(a1,a2),
 * a2 = max(a1,a2). */

__attribute__((section(".text.func_00133948")))
void func_00133948(void *a0, void *a1, void *a2) {
    (void)a0;
    VU0_LQC2(4, a1, 0);
    VU0_LQC2(5, a2, 0);
    VU0_VMINI_XYZW(6, 4, 5);
    VU0_VMAX_XYZW(7, 4, 5);
    VU0_SQC2(6, a1, 0);
    VU0_SQC2(7, a2, 0);
}
