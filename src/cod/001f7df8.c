#include "godhand/vu0.h"

/* func_001F7DF8 — 3D length of vector a0: sqrt(x*x + y*y + z*z) via the VU0
 * Q/sqrt pipeline. vsqrt emitted as its exact .word (ee-as encodes it
 * differently from retail). */

__attribute__((section(".text.func_001F7DF8")))
float func_001F7DF8(void *a0) {
    float r;
    int t;
    VU0_LQC2(4, a0, 0);
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
