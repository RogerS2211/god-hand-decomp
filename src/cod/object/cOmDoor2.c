/* TU: cOmDoor2 [object] - recovered C++ class. */

__attribute__((section(".text.cOmDoor2_setOpen")))
void cOmDoor2_setOpen(int a0) {
    if (*(unsigned char*)((char*)a0 + 0x774) == 0) {
        *(unsigned char*)((char*)a0 + 0x2F4) = 1;
        *(unsigned char*)((char*)a0 + 0x2F5) = 0;
        *(unsigned char*)((char*)a0 + 0x2F6) = 0;
        *(unsigned char*)((char*)a0 + 0x2F7) = 0;
    }
}

__attribute__((section(".text.cOmDoor2_setClose")))
void cOmDoor2_setClose(int a0) {
    if (*(unsigned char*)((char*)a0 + 0x774) == 1) {
        *(unsigned char*)((char*)a0 + 0x2F4) = 2;
        *(unsigned char*)((char*)a0 + 0x2F5) = 0;
        *(unsigned char*)((char*)a0 + 0x2F6) = 0;
        *(unsigned char*)((char*)a0 + 0x2F7) = 0;
    }
}
#include "include_asm.h"

INCLUDE_ASM("nonmatching", cOmDoor2_setOpenFix);

INCLUDE_ASM("nonmatching", cOmDoor2_setCloseFix);

INCLUDE_ASM("nonmatching", cOmDoor2_setOpenType);
