#include "godhand/vu0.h"

/* func_00134430 — constructor-style init: zero-fills two quadwords (0x20, 0x30)
 * via sqc2 $vf0, sets a few fields, returns the object. */

__attribute__((section(".text.func_00134430")))
void *func_00134430(void *a0, int a1, int a2, float f) {
    VU0_SQC2_VF0(a0, 0x20);
    VU0_SQC2_VF0(a0, 0x30);
    *(int *)((char *)a0 + 0x0) = a1;
    *(int *)((char *)a0 + 0x8) = a2;
    *(float *)((char *)a0 + 0xC) = f;
    *(int *)((char *)a0 + 0x4) = 0;
    *(int *)((char *)a0 + 0x10) = 0;
    return a0;
}
