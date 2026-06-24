/* TU: cSaveManager [system] - recovered C++ class. */
#include "include_asm.h"

extern int D_00569B70;
extern int D_005E8658;

__attribute__((section(".text.cSaveManager_stageClear")))
void cSaveManager_stageClear(void) {
    cCoreSave_stageInit(&D_00569B70);
    cRoomSave_systemInit(&D_005E8658);
}


INCLUDE_ASM("nonmatching", cSaveManager_setCheckPoint);
