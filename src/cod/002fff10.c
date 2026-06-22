#include "godhand/vu0.h"

/* func_002FFF10 — object constructor (InitObject + vtable@0xF0 + zero 0x2D0). */

extern void *InitObject_2FBCC8(void *);
extern int D_0044F308;

__attribute__((section(".text.func_002FFF10")))
void *func_002FFF10(void *a0) {
    if (a0) {
        InitObject_2FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044F308;
        VU0_SQC2_VF0(a0, 0x2D0);
    }
    return a0;
}
