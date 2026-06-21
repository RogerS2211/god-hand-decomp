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
    __asm__ __volatile__(".set push\n.set noreorder\n.word 0x4BCC61FF\n.set pop\n"); /* vclipw.xyz $vf12, $vf12w */
    VU0_VNOP();
    VU0_VNOP();
    VU0_VNOP();
    VU0_SQC2(12, a0, 0);
    VU0_VNOP();
    __asm__ __volatile__(".set push\n.set noreorder\ncfc2.ni %0, $vi18\n.set pop\n" : "=r"(r));
    return r;
}
