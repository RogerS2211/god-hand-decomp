/* TU: cEm30 [enemy] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cEm30_setEvent")))
void cEm30_setEvent(int a0) {
    *(char*)((char*)a0 + 0x2F4) = 0;
    *(char*)((char*)a0 + 0x2F6) = 0;
    *(char*)((char*)a0 + 0x2F5) = 4;
    *(char*)((char*)a0 + 0x2F7) = 0;
}
