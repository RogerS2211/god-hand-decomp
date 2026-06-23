#include "godhand/vu0.h"

/* capVu0MagnitudeSqXZ — squared distance between a0 and a1 in the XZ plane:
 * d = a0 - a1; returns d.x*d.x + d.z*d.z (computed on VU0, returned via the
 * COP2->GPR->FPU move chain). */

__attribute__((section(".text.capVu0MagnitudeSqXZ")))
float capVu0MagnitudeSqXZ(void *a0, void *a1) {
    float r;
    int t;
    VU0_LQC2(4, a0, 0);
    VU0_LQC2(5, a1, 0);
    VU0_VSUB_XZ(4, 4, 5);
    VU0_VMUL_XZ(4, 4, 4);
    VU0_VADDZ_X(4, 4, 4);
    VU0_QMFC2_NI(t, 4);
    VU0_MTC1(r, t);
    return r;
}
