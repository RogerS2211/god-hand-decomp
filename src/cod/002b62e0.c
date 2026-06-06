/* SN ProDG ee-gcc 2.95.3 matched TU. */

#include "godhand/vu0.h"

__attribute__((section(".text.CopyVec16From20_B62E0")))
void *CopyVec16From20_B62E0(void *a0, char *a1)
{
    a1 += 0x20;
    VU0_LQC2(4, a1, 0);
    VU0_SQC2(4, a0, 0);
    return a0;
}
