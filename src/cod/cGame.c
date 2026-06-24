/* TU: cGame - recovered C++ class. */
extern void cEmManage_ReleaseEmAll(void *a0);
extern char D_005864F0[];
#include "include_asm.h"

__attribute__((section(".text.cGame_setReleaseActiveHeap")))
void cGame_setReleaseActiveHeap(void *a0) {
    cEmManage_ReleaseEmAll(D_005864F0);
    *(short *)((char *)a0 + 0x1B2) = 5;
}
