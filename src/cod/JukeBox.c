/* TU: JukeBox - recovered C++ class. */
#include "include_asm.h"

extern void cIDBase(void *);

__attribute__((section(".text.JukeBox")))
void *JukeBox(void *a0) {
    *((unsigned char *)a0 + 0x4) = 0;
    cIDBase((char *)a0 + 0x30);
    *(int *)((char *)a0 + 0x80) = 0;
    return a0;
}

INCLUDE_ASM("nonmatching", JukeBox_Execute);
