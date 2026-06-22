/* TU: cScenario [event] - recovered C++ class. */
extern void SetFieldsCESignalSemaSleep_2D5AA0(int a0, int a1);

__attribute__((section(".text.cScenario_waitEventStartOk")))
void cScenario_waitEventStartOk(void *a0) {
    char *s0 = (char *)a0;
    char *s1 = s0 + 0x1C;
    while (cScenario_isEventStartOk(s0) == 0) {
        SetFieldsCESignalSemaSleep_2D5AA0(*(int *)(s1 + 4), 1);
    }
}

__attribute__((section(".text.cScenario_setCam")))
int cScenario_setCam(void *a0, int a1) {
    return LoadScreenOverlay_2C3F10(a0, SearchCameraData(a1));
}
#include "include_asm.h"

INCLUDE_ASM("nonmatching", cScenario_taskExec);

INCLUDE_ASM("nonmatching", cScenario_isEventStartOk);

INCLUDE_ASM("nonmatching", cScenario_beginRoomJump);

INCLUDE_ASM("nonmatching", cScenario_beginCasinoBattle);

INCLUDE_ASM("nonmatching", cScenario_endCasinoBattle);

INCLUDE_ASM("nonmatching", cScenario_beginKurohukuBattle);

INCLUDE_ASM("nonmatching", cScenario_endKurohukuBattle);

INCLUDE_ASM("nonmatching", cScenario_isOmBreak_2C5168);

INCLUDE_ASM("nonmatching", cScenario_isOmBreak_2C5220);

INCLUDE_ASM("nonmatching", cScenario_isOmBreak_2C5288);
