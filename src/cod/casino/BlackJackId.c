/* TU: BlackJackId [casino] - recovered C++ class. */
#include "include_asm.h"

extern void SetFlagOnEntries7C_1D51B8();

INCLUDE_ASM("nonmatching", BlackJackId_Move);

__attribute__((section(".text.BlackJackId_SetDefaultDisp")))
void BlackJackId_SetDefaultDisp(int a0) {
    SetFlagOnEntries7C_1D51B8(a0, 0x2D, 0);
    SetFlagOnEntries7C_1D51B8(a0, 0x1, 1);
    SetFlagOnEntries7C_1D51B8(a0, 0x2, 1);
    SetFlagOnEntries7C_1D51B8(a0, 0x3, 1);
    SetFlagOnEntries7C_1D51B8(a0, 0x4, 1);
    SetFlagOnEntries7C_1D51B8(a0, 0xA, 1);
    SetFlagOnEntries7C_1D51B8(a0, 0xC, 1);
    SetFlagOnEntries7C_1D51B8(a0, 0xF, 1);
    SetFlagOnEntries7C_1D51B8(a0, 0x22, 1);
    SetFlagOnEntries7C_1D51B8(a0, 0x19, 1);
}
