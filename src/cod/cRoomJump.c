/* TU: cRoomJump - recovered C++ class. */
#include "include_asm.h"

typedef struct {
    unsigned char unk[0x5B4]; short field_5B4; unsigned char pad0[4];
    unsigned char field_5BA; unsigned char pad1[5];
    float field_5C0; float field_5C4; float field_5C8; unsigned char pad2[4]; float field_5D0;
} CGRoomJump_t;
extern float *func_002BEB00(void *a0, int a1, unsigned char a2);
extern CGRoomJump_t D_007474A0;

__attribute__((section(".text.cRoomJump_setNextPos")))
void cRoomJump_setNextPos(void *a0, unsigned short a1, unsigned char a2, float *a3)
{
    float *src; float w; int idx = a1 & 0xFFFF;
    src = func_002BEB00(a0, idx, a2);
    if (src != 0) {
        D_007474A0.field_5C0 = src[0]; D_007474A0.field_5C4 = src[1]; D_007474A0.field_5C8 = src[2];
        w = src[3];
        if (w < -3.1415927410125732f) { D_007474A0.field_5D0 = w * 0.01745329238474369f; }
        else if (w > 3.1415927410125732f) { D_007474A0.field_5D0 = w * 0.01745329238474369f; }
        else { D_007474A0.field_5D0 = w; }
    } else {
        D_007474A0.field_5C0 = 0; D_007474A0.field_5C4 = 0; D_007474A0.field_5C8 = 0; D_007474A0.field_5D0 = 0;
    }
    if (a3 != 0) {
        float t0 = D_007474A0.field_5C0;
        float t1 = D_007474A0.field_5C4;
        float t2 = D_007474A0.field_5C8;
        float t3 = D_007474A0.field_5D0;
        a3[0] = t0;
        a3[1] = t1;
        a3[2] = t2;
        a3[3] = t3;
    }
    D_007474A0.field_5B4 = (short)idx;
    D_007474A0.field_5BA = 0;
}
