/* TU: cObjSimple - recovered C++ class. */
#include "include_asm.h"

extern void EmClothInit(int a0, void *a1, void *a2, void *a3);
extern void func_002DF938(void *a0, void *a1);

__attribute__((section(".text.cObjSimple_SetPendulum")))
void cObjSimple_SetPendulum(void *a0, int a1, void *a2) {
    *(int *)((char *)a0 + 0x1394) = a1;
    *(unsigned char *)((char *)a0 + 0x1390) = 1;
    EmClothInit(a1, a0, (char *)a0 + 0x13A0, (char *)a0 + 0x2F20);
    if (a2) {
        func_002DF938(a2, (char *)a0 + 0x2F20);
    }
}
