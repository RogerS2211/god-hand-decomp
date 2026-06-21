#include "godhand/vu0.h"

/* func_0030A348 — VU0 3D dot product: returns dot(*a0, *a1) as a float
 * (vmul.xyz then horizontal add via vaddy/vaddz, result moved out through
 * qmfc2/mtc1). */

__attribute__((section(".text.func_0030A348")))
float func_0030A348(void *a0, void *a1) {
    float r;
    int t;
    VU0_LQC2(4, a0, 0);
    VU0_LQC2(5, a1, 0);
    VU0_VMUL_XYZ(5, 4, 5);
    VU0_VADDY_X(5, 5);
    VU0_VADDZ_X(5, 5, 5);
    __asm__ __volatile__(".set push\n.set noreorder\nqmfc2.ni %0, $vf5\n.set pop\n" : "=r"(t));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(r) : "r"(t));
    return r;
}
