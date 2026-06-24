/* TU: cCockPlBar [casino] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cCockPlBar_initData")))
void cCockPlBar_initData(int a0) {
    int *p = *(int **)((char *)a0 + 0x80);
    ((void (*)())*(int *)((char *)p + 0x1C))(a0 + *(short *)((char *)p + 0x18));
}

