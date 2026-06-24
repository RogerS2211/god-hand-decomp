/* TU: BlackJack [casino] - recovered C++ class. */
#include "include_asm.h"

__attribute__((section(".text.BlackJack_Release")))
void BlackJack_Release(void) {
    func_001D4F48();
}

extern char D_00463050[];


INCLUDE_ASM("nonmatching", BlackJack_Main);

__attribute__((section(".text.BlackJack_SetBlackJackCamera")))
void BlackJack_SetBlackJackCamera(int a0, float *a1, float *a2) {
    float *dst1;
    float *dst2;

    cCamManager_setSubScrCamera(D_00463050, 0);
    *(int *)(a0 + 0x181C) = (int)(D_00463050 + 0xC90);
    dst1 = (float *)(D_00463050 + 0xEA0);
    if (a1 != dst1) {
        dst1[0] = a1[0];
        dst1[1] = a1[1];
        dst1[2] = a1[2];
    }
    dst2 = (float *)(*(int *)(a0 + 0x181C) + 0x200);
    if (dst2 != a2) {
        dst2[0] = a2[0];
        dst2[1] = a2[1];
        dst2[2] = a2[2];
    }
}


__attribute__((section(".text.BlackJack_ClearBlackJackCamera")))
void BlackJack_ClearBlackJackCamera(void) {
    cCamManager_setPlCamera(D_00463050, 0);
}

