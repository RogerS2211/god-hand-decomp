/* TU: cOm5a [object] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cOm5a_isOpen")))
unsigned char cOm5a_isOpen(unsigned char *a0) {
    return a0[0x60D];
}

INCLUDE_ASM("nonmatching", cOm5a_setOpenFix);

INCLUDE_ASM("nonmatching", cOm5a_setCloseFix);

__attribute__((section(".text.cOm5a_setFaceClose")))
void cOm5a_setFaceClose(int *a0) {
    int p;
    a0[0x182] = 2;
    a0[0x181] = 0;
    p = a0[0x189];
    if (p != 0) {
        cDamageUnit_SetDamageCollActive(p, 0);
    }
}

