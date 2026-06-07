/* TU: cOm4f [object] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cOm4f_isOpen")))
unsigned char cOm4f_isOpen(unsigned char *a0) {
    return a0[0x761];
}

__attribute__((section(".text.cOm4f_isActive")))
unsigned int cOm4f_isActive(unsigned char *a0) {
    return a0[0x760];
}

__attribute__((section(".text.cOm4f_setEventMode")))
void cOm4f_setEventMode(char *a0, int a1) {
    a0[0x763] = (char)a1;
}

__attribute__((section(".text.cOm4f_setLock")))
void cOm4f_setLock(unsigned char *a0, int a1) {
    ((unsigned char *)a0)[0x762] = (unsigned char)a1;
}

__attribute__((section(".text.cOm4f_connectDoor")))
void cOm4f_connectDoor(char *a0, int a1) {
    *(int *)(a0 + 0x790) = a1;
}

INCLUDE_ASM("nonmatching", cOm4f_setOpen);

INCLUDE_ASM("nonmatching", cOm4f_setClose);
