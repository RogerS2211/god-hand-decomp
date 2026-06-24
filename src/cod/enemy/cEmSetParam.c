/* TU: cEmSetParam [enemy] - recovered C++ class. */
#include "include_asm.h"

INCLUDE_ASM("nonmatching", cEmSetParam_setEmAll);

INCLUDE_ASM("nonmatching", cEmSetParam_setEm);

extern int D_005E8658;

__attribute__((section(".text.cEmSetParam_updateSetDataRot")))
void cEmSetParam_updateSetDataRot(float f) {
    short *p = (short *)func_002BEF60(&D_005E8658);
    if (p != 0) {
        *(short *)((char *)p + 6) = (short)(int)(f * 57.2957763671875f);
    }
}


__attribute__((section(".text.cEmSetParam_updateSetDataAppPattern")))
void cEmSetParam_updateSetDataAppPattern(int a, int b, unsigned char c) {
    char *p = (char *)func_002BEF60(&D_005E8658);
    c = c & 0xFF;
    if (p != 0) {
        *(char *)(p + 0x10) = c;
    }
}


INCLUDE_ASM("nonmatching", cEmSetParam_getSetDataPos);
