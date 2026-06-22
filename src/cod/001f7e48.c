#include "godhand/vu0.h"

/* func_001F7E48 — 3D distance between a0 and a1: length of (a0 - a1) via the
 * VU0 Q/sqrt pipeline. vsqrt emitted as its exact .word. */

__attribute__((section(".text.func_001F7E48")))
float func_001F7E48(void *a0, void *a1) {
    float r;
    int t;
    VU0_LQC2(4, a0, 0);
    VU0_LQC2(5, a1, 0);
    VU0_VSUB_XYZ(4, 4, 5);
    VU0_VMUL_XYZ(4, 4, 4);
    VU0_VADDY_X(4, 4);
    VU0_VADDZ_X(4, 4, 4);
    VU0_VSQRT_Q_VF4X();
    VU0_VWAITQ();
    VU0_VADDQ_X(4, 0);
    VU0_QMFC2_NI(t, 4);
    VU0_MTC1(r, t);
    return r;
}
