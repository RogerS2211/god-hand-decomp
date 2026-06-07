/* TU: cOl29 [object] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cOl29_setOpen")))
void cOl29_setOpen(unsigned char *a0)
{
    if (a0[0x764] == 0) {
        a0[0x2F7] = 0;
        a0[0x2F5] = 0;
        a0[0x2F6] = 0;
        a0[0x2F4] = 1;
    }
}

__attribute__((section(".text.cOl29_setClose")))
void cOl29_setClose(unsigned char *a0)
{
    if (a0[0x764] == 1) {
        a0[0x2F7] = 0;
        a0[0x2F5] = 0;
        a0[0x2F6] = 0;
        a0[0x2F4] = 2;
    }
}

__attribute__((section(".text.cOl29_isOpen")))
unsigned char cOl29_isOpen(unsigned char *a0) {
    return a0[0x764];
}

INCLUDE_ASM("nonmatching", cOl29_setOpenFix);

INCLUDE_ASM("nonmatching", cOl29_setCloseFix);
