#include "godhand/vu0.h"

/* func_002FFB38 — object constructor (InitObject + vtable@0xF0 + zero 0x2C0,
 * then word-zero 0x2B0). */

extern void *InitObject_2FBCC8(void *);
extern int D_0044E538;

__attribute__((section(".text.func_002FFB38")))
void *func_002FFB38(void *a0) {
    if (a0) {
        InitObject_2FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044E538;
        VU0_SQC2_VF0(a0, 0x2C0);
        *(int *)((char *)a0 + 0x2B0) = 0;
    }
    return a0;
}
