/* TU: cOl1b [object] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cOl1b_setClose")))
void cOl1b_setClose(unsigned char *a0)
{
    unsigned char v = a0[0x601];
    if (v == 1) {
        a0[0x600] = v;
        a0[0x2F4] = 2;
        a0[0x2F5] = 0;
        a0[0x2F6] = 0;
        a0[0x2F7] = 0;
    }
}

__attribute__((section(".text.cOl1b_isActive")))
int cOl1b_isActive(char *a0) {
    return (unsigned char)a0[0x600];
}
