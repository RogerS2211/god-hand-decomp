#include "godhand/vu0.h"

/* func_002FFFE0 — object constructor (InitObject + vtable@0xF0 + zero 0x2B0). */

extern void *InitObject_2FBCC8(void *);
extern int D_0044F598;

__attribute__((section(".text.func_002FFFE0")))
void *func_002FFFE0(void *a0) {
    if (a0) {
        InitObject_2FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044F598;
        VU0_SQC2_VF0(a0, 0x2B0);
    }
    return a0;
}
