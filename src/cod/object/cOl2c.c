/* TU: cOl2c [object] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.cOl2c_isFireStart")))
unsigned char cOl2c_isFireStart(unsigned char *a0) {
    return a0[0x770];
}

__attribute__((section(".text.cOl2c_isFire")))
unsigned char cOl2c_isFire(unsigned char *a0) {
    return a0[0x771];
}
