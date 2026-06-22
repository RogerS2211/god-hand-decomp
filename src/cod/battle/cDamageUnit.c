/* TU: cDamageUnit [battle] - recovered C++ class. */
#include "godhand/vu0.h"

__attribute__((section(".text.cDamageUnit_SetDamageCollActive")))
void cDamageUnit_SetDamageCollActive(int a0, int a1) {
    int node = *(int*)(a0 + 0x3C);
    if (node == 0) return;
    do {
        int *p = *(int**)(node + 0x28);
        if (a1 == 1) {
            *p = *p | 2;
        } else {
            *p = *p & 0xFFFFFFFD;
        }
        node = *(int*)(node + 0x24);
    } while (node != 0);
}

__attribute__((section(".text.cDamageUnit_SetDamageCollOffset")))
void cDamageUnit_SetDamageCollOffset(void *a0, void *a1) {
    int *s0 = *(int **)((char*)a0 + 0x3C);
    while (s0) {
        void *v0 = *(void **)((char*)s0 + 0x28);
        cCollisionShape_setOffsetPos(*(void **)((char*)v0 + 0x34), a1);
        s0 = *(int **)((char*)s0 + 0x24);
    }
}
