/* TU: cOm53 [object] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cOm53_setRiseWaitTime")))
void cOm53_setRiseWaitTime(int *a0, int a1) {
    *(int *)((char *)a0 + 0x628) = a1;
}
