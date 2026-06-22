#include "godhand/vu0.h"

/* func_001F7ED8 — VU0 vector add: *a0.xyz = *a1.xyz + *a2.xyz.
 * Compiled with sn-2.95.3-136 (the VU0/sq family compiler). */

__attribute__((section(".text.func_001F7ED8")))
void func_001F7ED8(void *a0, void *a1, void *a2) {
    VU0_LQC2(4, a1, 0);
    VU0_LQC2(5, a2, 0);
    VU0_VADD_XYZ(4, 4, 5);
    VU0_SQC2(4, a0, 0);
}
