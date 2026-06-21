#include "godhand/vu0.h"

/* func_002BA488 — copy one quadword from the D_00747B00 constant to a0,
 * return a0. */

extern char D_00747B00[];

__attribute__((section(".text.func_002BA488")))
void *func_002BA488(void *a0) {
    VU0_LQC2(4, D_00747B00, 0);
    VU0_SQC2(4, a0, 0);
    return a0;
}
