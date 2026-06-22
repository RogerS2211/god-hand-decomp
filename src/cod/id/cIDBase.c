/* TU: cIDBase [id] - recovered C++ class. */
extern int *D_003C2384;
extern void func_002A9DF8(int a0);
extern void cIDBase_resetAnim(int a0);

__attribute__((section(".text.cIDBase_initialize")))
int cIDBase_initialize(int a0, int a1, int a2)
{
    int r;
    func_002A9DF8(a0);
    *(int*)(a0 + 0x10) = a2;
    *(char*)(a0 + 0x46) = 6;
    *(int*)(a0 + 0x14) = a1;
    r = func_002ACD78(*D_003C2384, a1, a2 + 1);
    if (r == 0)
        return 0;
    if (cIDBase_setWorkFromData(a0, r) != 0)
        cIDBase_resetAnim(a0);
    return 1;
}

__attribute__((section(".text.cIDBase_restartAnim")))
void cIDBase_restartAnim(void *a0) {
    cIDBase_resetAnim(a0);
    *(char *)((char *)a0 + 0x1C) = 1;
}
#include "include_asm.h"

INCLUDE_ASM("nonmatching", cIDBase);

INCLUDE_ASM("nonmatching", cIDBase_setDispFamily);

INCLUDE_ASM("nonmatching", cIDBase_move);

INCLUDE_ASM("nonmatching", cIDBase_trans);
