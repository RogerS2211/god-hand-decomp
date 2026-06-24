/* TU: cCamManager [camera] - recovered C++ class. */
#include "include_asm.h"

extern int D_005CAFF0;

__attribute__((section(".text.cCamManager_setPlCamera")))
void cCamManager_setPlCamera(int *a0, unsigned char a1)
{
    if (a0[0x1028/4] != 1 && a0[0x1028/4] != 0x10) {
        if (a1) {
            func_00138CA8(a0, a0, D_005CAFF0, a1);
        }
        a0[0x102C/4] = a0[0x1028/4];
        a0[0xFF0/4] = D_005CAFF0;
        D_005CAFF0 = (int)a0;
        a0[0x1028/4] = 1;
    }
}


__attribute__((section(".text.cCamManager_setMotCamera")))
void cCamManager_setMotCamera(char *a0, unsigned char a1)
{
    if (*(int *)(a0 + 0x1028) != 4 && *(int *)(a0 + 0x1028) != 0x10) {
        if (a1) {
            func_00138CA8(a0, a0 + 0x530, D_005CAFF0, a1);
        }
        *(int *)(a0 + 0x102C) = *(int *)(a0 + 0x1028);
        *(int *)(a0 + 0xFF0) = D_005CAFF0;
        D_005CAFF0 = (int)(a0 + 0x530);
        *(int *)(a0 + 0x1028) = 4;
    }
}


__attribute__((section(".text.cCamManager_setSubScrCamera")))
void cCamManager_setSubScrCamera(char *a0, unsigned char a1)
{
    if (*(int *)(a0 + 0x1028) != 0x80 && *(int *)(a0 + 0x1028) != 0x10) {
        if (a1) {
            func_00138CA8(a0, a0 + 0xC90, D_005CAFF0, a1);
        }
        *(int *)(a0 + 0x102C) = *(int *)(a0 + 0x1028);
        *(int *)(a0 + 0xFF0) = D_005CAFF0;
        D_005CAFF0 = (int)(a0 + 0xC90);
        cCamera_reset(a0 + 0xC90);
        *(int *)(a0 + 0x1028) = 0x80;
    }
}

