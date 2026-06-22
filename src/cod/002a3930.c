#include "godhand/vu0.h"

/* func_002A3930 — VU0 matrix * vector with W-clip, using the matrix already
 * resident in $vf4..$vf7 (set by a prior call); loads only the vector (a1),
 * transforms, vclipw, stores to a0, returns the clip flags from $vi18. */

__attribute__((section(".text.func_002A3930")))
int func_002A3930(void *a0, void *a1) {
    int r;
    VU0_LQC2(8, a1, 0);
    VU0_VMULAX_XYZW(4, 8);
    VU0_VMADDAY_XYZW(5, 8);
    VU0_VMADDAZ_XYZW(6, 8);
    VU0_VMADDW_XYZW(12, 7, 0);
    VU0_VCLIPW_XYZ_VF12();
    VU0_VNOP();
    VU0_VNOP();
    VU0_VNOP();
    VU0_SQC2(12, a0, 0);
    VU0_VNOP();
    VU0_CFC2_NI(r, 18);
    return r;
}
