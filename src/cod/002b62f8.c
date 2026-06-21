#include "godhand/vu0.h"

/* func_002B62F8 — copy one quadword from a1+0x30 to a0, return a0. */

__attribute__((section(".text.func_002B62F8")))
void *func_002B62F8(void *a0, void *a1) {
    a1 = (char *)a1 + 0x30;
    VU0_LQC2(4, a1, 0);
    VU0_SQC2(4, a0, 0);
    return a0;
}
