#include "godhand/vu0.h"

/* func_002FFAD0 — object constructor: InitObject base, set the vtable pointer
 * at 0xF0, zero a quadword at 0x2B0.  sn-2.95.3-136 (sq $s0 prologue). */

extern void *InitObject_2FBCC8(void *);
extern int D_0044E238;

__attribute__((section(".text.func_002FFAD0")))
void *func_002FFAD0(void *a0) {
    if (a0) {
        InitObject_2FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044E238;
        VU0_SQC2_VF0(a0, 0x2B0);
    }
    return a0;
}
