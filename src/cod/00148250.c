#include "godhand/vu0.h"

/* func_00148250 — initialise a 4x4 transform: lay down an identity basis via
 * vmove/vmr32 (rows at 0x0/0x10/0x20/0x30), then set the diagonal to (a, b,
 * 1.0) at 0x0/0x14/0x28 and zero the remaining cells.  The trailing zero-store
 * block is written in the store-rotation pre-image order (0x3C written last so
 * the scheduler rotates it to the front). */

__attribute__((section(".text.func_00148250")))
void func_00148250(void *a0, float a, float b) {
    VU0_VMOVE_XYZW(4, 0);
    VU0_VMR32_XYZW(5, 4);
    VU0_VMR32_XYZW(6, 5);
    VU0_VMR32_XYZW(7, 6);
    VU0_SQC2(4, a0, 0x30);
    VU0_SQC2(5, a0, 0x20);
    VU0_SQC2(6, a0, 0x10);
    VU0_SQC2(7, a0, 0x0);
    *(float *)((char *)a0 + 0x0) = a;
    *(float *)((char *)a0 + 0x14) = b;
    *(float *)((char *)a0 + 0x28) = 1.0f;
    *(int *)((char *)a0 + 0x4) = 0;
    *(int *)((char *)a0 + 0x8) = 0;
    *(int *)((char *)a0 + 0xC) = 0;
    *(int *)((char *)a0 + 0x10) = 0;
    *(int *)((char *)a0 + 0x18) = 0;
    *(int *)((char *)a0 + 0x1C) = 0;
    *(int *)((char *)a0 + 0x20) = 0;
    *(int *)((char *)a0 + 0x24) = 0;
    *(int *)((char *)a0 + 0x2C) = 0;
    *(int *)((char *)a0 + 0x30) = 0;
    *(int *)((char *)a0 + 0x34) = 0;
    *(int *)((char *)a0 + 0x38) = 0;
    *(int *)((char *)a0 + 0x3C) = 0;
}
