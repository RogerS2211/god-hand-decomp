#include "godhand/vu0.h"

/* func_001FC7C8 — constructor-style init: zero-fills two quadwords (0x0, 0x10),
 * sets 0x2C = -1 and zeroes the surrounding fields, returns the object.
 * sn-2.95.3-136 (cygnus schedules the return-value move late). */

__attribute__((section(".text.func_001FC7C8")))
void *func_001FC7C8(void *a0) {
    VU0_SQC2_VF0(a0, 0x0);
    VU0_SQC2_VF0(a0, 0x10);
    *(short *)((char *)a0 + 0x2C) = -1;
    *(int *)((char *)a0 + 0x28) = 0;
    *(signed char *)((char *)a0 + 0x2E) = 0;
    *(int *)((char *)a0 + 0x20) = 0;
    *(int *)((char *)a0 + 0x24) = 0;
    return a0;
}
