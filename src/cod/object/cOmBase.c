/* TU: cOmBase [object] - recovered C++ class. */

extern char D_005CAE50[];
extern void func_001331B8(char *a0, long a1, int a2);

__attribute__((section(".text.cOmBase_setMeshDispFromLayer")))
void cOmBase_setMeshDispFromLayer(void *a0, int a1, int a2) {
    char *v1 = (char *)cModel_getMeshPtr(a0, 0);
    if (v1 != 0) {
        do {
            if (*(unsigned char *)(v1 + 0x40C) == a1) {
                if (a2 == 1) {
                    *(int *)(v1 + 0x380) &= 0xFFFFFFFE;
                } else {
                    *(int *)(v1 + 0x380) |= 1;
                }
            }
            v1 = *(char **)(v1 + 0x404);
        } while (v1 != 0);
    }
}
#include "include_asm.h"

__attribute__((section(".text.cOmBase_setMeshColorFromLayer")))
void cOmBase_setMeshColorFromLayer(void *a0, int a1, float r, float g, float b) {
    char *v1 = (char *)cModel_getMeshPtr(a0, 0);
    if (v1 != 0) {
        do {
            if (*(unsigned char *)(v1 + 0x40C) == a1) {
                float *c = (float *)(v1 + 0x3A0);
                c[0] = r;
                c[1] = g;
                c[2] = b;
            }
            v1 = *(char **)(v1 + 0x404);
        } while (v1 != 0);
    }
}


__attribute__((section(".text.cOmBase_setScrSollEnable")))
void cOmBase_setScrSollEnable(char *a0, int a1) {
    long v = *(long *)(a0 + 0x540);
    func_001331B8(D_005CAE50, v, a1);
}

