#include "godhand/vu0.h"

/* func_0012E5C8 — object constructor: set the vtable pointer at 0x198, zero a
 * block of quadwords (0x30..0x160) and several head words, return the object.
 * sn-2.95.3-136 (return-value move scheduled to match; cygnus swaps it). */

extern int D_0041D540;

__attribute__((section(".text.func_0012E5C8")))
void *func_0012E5C8(void *a0) {
    *(int **)((char *)a0 + 0x198) = &D_0041D540;
    VU0_SQC2_VF0(a0, 0x30);
    VU0_SQC2_VF0(a0, 0x40);
    VU0_SQC2_VF0(a0, 0x50);
    VU0_SQC2_VF0(a0, 0x90);
    VU0_SQC2_VF0(a0, 0xA0);
    VU0_SQC2_VF0(a0, 0xB0);
    VU0_SQC2_VF0(a0, 0xC0);
    VU0_SQC2_VF0(a0, 0xD0);
    VU0_SQC2_VF0(a0, 0xE0);
    VU0_SQC2_VF0(a0, 0xF0);
    VU0_SQC2_VF0(a0, 0x100);
    VU0_SQC2_VF0(a0, 0x120);
    VU0_SQC2_VF0(a0, 0x130);
    VU0_SQC2_VF0(a0, 0x150);
    VU0_SQC2_VF0(a0, 0x160);
    *(int *)((char *)a0 + 0x0) = 0;
    *(int *)((char *)a0 + 0x4) = 0;
    *(int *)((char *)a0 + 0x8) = 0;
    *(int *)((char *)a0 + 0x14) = 0;
    *(int *)((char *)a0 + 0xC) = 0;
    *(int *)((char *)a0 + 0x18) = 0;
    *(int *)((char *)a0 + 0x1C) = 0;
    *(int *)((char *)a0 + 0x190) = 0;
    *(int *)((char *)a0 + 0x194) = 0;
    return a0;
}
