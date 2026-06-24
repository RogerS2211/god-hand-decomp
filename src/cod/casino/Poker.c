/* TU: Poker [casino] - recovered C++ class. */
#include "include_asm.h"

INCLUDE_ASM("nonmatching", Poker_Initialize);

__attribute__((section(".text.Poker_Release")))
void Poker_Release(void) {
    func_001DF940();
}


INCLUDE_ASM("nonmatching", Poker_SetDefaultDisp);

INCLUDE_ASM("nonmatching", Poker_Main);
