/* TU: cOl26 [object] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cOl26_setOpen")))
void cOl26_setOpen(unsigned char *a0)
{
    if (a0[0x600] == 0) {
        a0[0x2F7] = 0;
        a0[0x2F5] = 0;
        a0[0x2F6] = 0;
        a0[0x2F4] = 1;
    }
}

__attribute__((section(".text.cOl26_isOpen")))
unsigned char cOl26_isOpen(unsigned char *a0) {
    return a0[0x600];
}
