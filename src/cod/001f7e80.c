#include "godhand/vu0.h"

/* func_001F7E80 — XZ-plane distance between a0 and a1: sqrt of the squared
 * distance, computed on VU0 (the Q/sqrt pipeline) and returned as a float.
 * ee-as encodes `vsqrt Q, $vf4x` differently from retail, so it is emitted as
 * its exact .word. */

__attribute__((section(".text.func_001F7E80")))
float func_001F7E80(void *a0, void *a1) {
    float r;
    int t;
    VU0_LQC2(4, a0, 0);
    VU0_LQC2(5, a1, 0);
    VU0_VSUB_XZ(4, 4, 5);
    VU0_VMUL_XZ(4, 4, 4);
    VU0_VADDZ_X(4, 4, 4);
    VU0_VSQRT_Q_VF4X();
    VU0_VWAITQ();
    VU0_VADDQ_X(4, 0);
    VU0_QMFC2_NI(t, 4);
    VU0_MTC1(r, t);
    return r;
}
