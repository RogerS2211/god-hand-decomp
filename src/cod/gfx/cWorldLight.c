/* TU: cWorldLight [gfx] - recovered C++ class. */
#include "include_asm.h"

/* cWorldLight_Set_LightData — sn-2.95.3-136.
 * EE gcc: `long long` is a 128-bit (quadword) type, so a 0x70-byte light
 * record is long long[7]. */
typedef struct { long long qw[7]; } LightData;    /* 0x70-byte light record */
extern void cWorldLight_Light_curent_set2(void *a0, int a1);
extern unsigned int D_00747A84;

INCLUDE_ASM("nonmatching", cWorldLight_Light_curent_set);

__attribute__((section(".text.cWorldLight_Set_LightData")))
int cWorldLight_Set_LightData(void *a0, void *a1)
{
    LightData *src;
    LightData *base;
    LightData *dst;
    int idx;

    if (*(unsigned short *)((char *)a1 + 0x2) == 0)
        return 0;
    idx = *(int *)((char *)a0 + 0x78);
    if (idx >= 0x100)
        return 0;

    src = (LightData *)a1;
    base = (LightData *)a0;
    dst = (LightData *)((char *)&base[idx] + 0x80);
    *dst = *src;

    *(int *)((char *)a0 + 0x78) = *(int *)((char *)a0 + 0x78) + 1;

    if ((D_00747A84 & 0x8000000) == 0)
        cWorldLight_Light_curent_set2(a0, *(int *)((char *)a0 + 0x16288));
    return 1;
}
