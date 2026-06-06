/* TU: cCamera [camera] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cCamera_setMode")))
void cCamera_setMode(void) {}

__attribute__((section(".text.cCamera_resetVib")))
void cCamera_resetVib(void *a0) {
    char *p = (char *)a0;
    *(int *)(p + 0x274) = 0;
    *(int *)(p + 0x268) = 0;
    *(int *)(p + 0x270) = 0;
    *(int *)(p + 0x26C) = 0;
    *(char *)(p + 0x278) = 0;
    *(int *)(p + 0x260) = 0;
    *(int *)(p + 0x254) = 0;
    *(int *)(p + 0x25C) = 0;
    *(int *)(p + 0x258) = 0;
    *(char *)(p + 0x264) = 0;
}
