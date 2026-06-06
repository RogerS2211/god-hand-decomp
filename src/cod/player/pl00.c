/* TU: pl00 [player] - recovered C++ class. */
extern void func_0012C418(void);
#include "include_asm.h"

__attribute__((section(".text.pl00_CannonGameMode")))
void pl00_CannonGameMode(void *a0, int a1) {
    if (a1) {
        *(unsigned char*)((char*)a0+0x2F4) = 6;
        *(float*)((char*)a0+0x54C) = 5.0f;
        *(unsigned char*)((char*)a0+0x2F5) = 0;
        *(unsigned char*)((char*)a0+0x2F6) = 0;
        *(unsigned char*)((char*)a0+0x2F7) = 0;
    } else {
        func_0012C418();
    }
}

__attribute__((section(".text.pl00_ckMotionCam")))
int pl00_ckMotionCam(char *a0) {
    int v = *(int*)(a0 + 0x15F4) & 0x2;
    return v != 0;
}

__attribute__((section(".text.pl00_setIgnition")))
void pl00_setIgnition(void *a0, float *a1, float f12) {
    float *v0 = (float*)((char*)a0+0x660);
    if (v0 != a1) {
        *v0 = *a1;
        v0[1] = a1[1];
        v0[2] = a1[2];
    }
    *(float*)((char*)a0+0x670) = f12;
    *(unsigned char*)((char*)a0+0x2F5) = 0x34;
    *(unsigned char*)((char*)a0+0x2F4) = 0;
    *(unsigned char*)((char*)a0+0x2F6) = 0;
    *(unsigned char*)((char*)a0+0x2F7) = 0;
}

__attribute__((section(".text.pl00_setPyramidIn")))
void pl00_setPyramidIn(char *a0) {
    *(unsigned char*)(a0 + 0x2F4) = 0;
    *(unsigned char*)(a0 + 0x2F5) = 0x36;
    *(unsigned char*)(a0 + 0x2F6) = 0;
    *(unsigned char*)(a0 + 0x2F7) = 0;
}
