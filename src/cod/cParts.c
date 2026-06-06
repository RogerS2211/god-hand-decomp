/* TU: cParts - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cParts_setRotationOrder")))
void cParts_setRotationOrder(char *arg0, int arg1) {
    arg0[0x140] = arg1;
}
