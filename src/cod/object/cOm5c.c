/* TU: cOm5c [object] - recovered C++ class. */
extern void cOm59_setParent();
#include "include_asm.h"

__attribute__((section(".text.cOm5c_setArm")))
void cOm5c_setArm(int *a0, int a1, char *a2) {
    int *p;
    char *q;
    if (a2 == 0) {
        return;
    }
    if ((unsigned int)a1 >= 2) {
        return;
    }
    q = a2 + 0x100;
    p = *(int **)(a2 + 0xF0);
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    *(int *)(a2 + 0x100) = 0;
    *(int *)(q + 4) = 0;
    *(int *)(q + 8) = 0;
    cOm59_setParent(a2, a0, -1);
    *(int *)((char *)a0 + (a1 << 2) + 0x604) = (int)a2;
}
