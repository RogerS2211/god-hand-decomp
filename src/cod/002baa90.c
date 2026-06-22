#include "godhand/vu0.h"

/* func_002BAA90 — copy one quadword from a1+0x110 to a0, return a0. */

__attribute__((section(".text.func_002BAA90")))
void *func_002BAA90(void *a0, void *a1) {
    a1 = (char *)a1 + 0x110;
    VU0_LQC2(4, a1, 0);
    VU0_SQC2(4, a0, 0);
    return a0;
}
