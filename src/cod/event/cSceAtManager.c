/* TU: cSceAtManager [event] - recovered C++ class. */

__attribute__((section(".text.cSceAtManager_SetEnable_2C28F8")))
int cSceAtManager_SetEnable_2C28F8(int *a0, int a1) {
    if (*a0 == 0) return 0;
    if (a1 == 0) return 0;
    if (func_002C0E68(a1) != 0) return 1;
    cSceAtUnit_SetEnable(a1, 0);
    return 1;
}

__attribute__((section(".text.cSceAtManager_SetEnable_2C2950")))
int cSceAtManager_SetEnable_2C2950(int *a0, unsigned short a1) {
    int v0;
    if (*a0 == 0) return 0;
    v0 = cSceAtManager_getUnit((int)a0, a1);
    if (v0 == 0) return 0;
    return cSceAtManager_SetEnable_2C28F8((int)a0, v0);
}

__attribute__((section(".text.cSceAtManager_SetDisable")))
int cSceAtManager_SetDisable(int *a0, int a1) {
    if (*a0 == 0) return 0;
    if (a1 == 0) return 0;
    if (func_002C0E68(a1) != 0) {
        cSceAtUnit_SetDisable(a1, 0);
    }
    return 1;
}

__attribute__((section(".text.cSceAtManager_getCenterPos")))
void cSceAtManager_getCenterPos(int *a0, unsigned short a1, int a2) {
    int v0;
    if (*a0) {
        v0 = cSceAtManager_getUnit(a0, a1);
        if (v0) {
            cSceAtUnit_getCenterPos(v0, a2);
        }
    }
}

__attribute__((section(".text.cSceAtManager_isHit")))
void *cSceAtManager_isHit(void *a0, void *a1, void *a2) {
    void *v0 = cSceAtManager_getUnit(a0, a1);
    if (v0 == 0) return 0;
    return func_002C0ED0(v0, a2);
}

__attribute__((section(".text.cSceAtManager_getUnit")))
int cSceAtManager_getUnit(int a0, int a1) {
    int e;
    if (a1 == 0xFFFFF) return 0;
    e = func_002C30C0(a0);
    while ((e = func_002C30C8(a0, e)) != 0) {
        if (*(unsigned short*)((char*)e + 0x36) == a1) return e;
    }
    return 0;
}
#include "include_asm.h"

__attribute__((section(".text.cSceAtManager_AtDataSet_exec")))
void cSceAtManager_AtDataSet_exec(int a0, unsigned short a1, int a2, int a3, int a4, int a5) {
    int v0;
    v0 = cSceAtManager_getUnit(a0, a1);
    if (v0) {
        cSceAtManager_AtDataSet_exec_2C2750(a0, v0, a2, a3, a4, a5);
    }
}


INCLUDE_ASM("nonmatching", cSceAtManager_AtExecute_2C2870);

INCLUDE_ASM("nonmatching", cSceAtManager_AtExecute_2C28B0);

__attribute__((section(".text.cSceAtManager_delUnitData")))
void cSceAtManager_delUnitData(int a0, int a1) {
    if (a1) {
        func_002C3058(a0, a0 + 0x5C, a1);
    }
}

