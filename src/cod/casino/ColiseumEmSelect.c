/* TU: ColiseumEmSelect [casino] - recovered C++ class. */
extern char D_003BF0A8[];
#include "include_asm.h"

__attribute__((section(".text.ColiseumEmSelect_Main")))
void ColiseumEmSelect_Main(int a0) {
    int i = *(int *)(a0 + 0x4);
    short off = *(short *)(D_003BF0A8 + i * 8);
    void (*fn)() = *(void (**)())(D_003BF0A8 + i * 8 + 4);
    fn(a0 + off);
}
