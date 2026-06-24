/* TU: cSaveLoad [system] - recovered C++ class. */
#include "include_asm.h"

INCLUDE_ASM("nonmatching", cSaveLoad_openSave);

extern int D_00747A84;

__attribute__((section(".text.cSaveLoad_openLoad")))
int cSaveLoad_openLoad(unsigned char *a0)
{
    int *p;
    if (func_002BF700(a0) == 0)
        return 0;
    func_002BF170(a0);
    p = &D_00747A84;
    p[1] |= 0x40000000;
    a0[3] = 0;
    a0[1] = 0;
    a0[2] = 0;
    a0[0] = 2;
    return 1;
}

