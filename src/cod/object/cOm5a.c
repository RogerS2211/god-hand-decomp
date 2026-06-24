/* TU: cOm5a [object] - recovered C++ class. */
#include "godhand/vu0.h"
#include "include_asm.h"

__attribute__((section(".text.cOm5a_isOpen")))
unsigned char cOm5a_isOpen(unsigned char *a0) {
    return a0[0x60D];
}

__attribute__((section(".text.cOm5a_setOpenFix")))
void cOm5a_setOpenFix(char *a0) {
    float buf[4] __attribute__((aligned(16)));
    if (*(unsigned char *)(a0 + 0x60D) == 0) {
        int *vt = *(int **)(a0 + 0x214);
        short off = *(short *)((char *)vt + 0x80);
        void *(*fp)() = *(void *(**)())((char *)vt + 0x84);
        void *src = fp(a0 + off);
        VU0_LQC2(4, src, 0);
        VU0_SQC2(4, buf, 0);
        if (*(int *)(a0 + 0x600) == 0) {
            buf[1] = buf[1] + *(float *)(a0 + 0x790);
        } else {
            buf[1] = buf[1] - *(float *)(a0 + 0x790);
        }
        {
            int *vt2 = *(int **)(a0 + 0x214);
            short off2 = *(short *)((char *)vt2 + 0x70);
            void (*fp2)() = *(void (**)())((char *)vt2 + 0x74);
            fp2(a0 + off2, buf);
        }
        *(int *)(a0 + 0x5B8) = *(int *)(a0 + 0x5B8) & ~0x100;
        *(unsigned char *)(a0 + 0x60D) = 1;
        *(unsigned char *)(a0 + 0x2F4) = 3;
        *(unsigned char *)(a0 + 0x2F5) = 0;
        *(unsigned char *)(a0 + 0x2F6) = 0;
        *(unsigned char *)(a0 + 0x2F7) = 0;
    }
}
__attribute__((section(".text.cOm5a_setCloseFix")))
void cOm5a_setCloseFix(char *a0) {
    float buf[4] __attribute__((aligned(16)));
    if (*(unsigned char *)(a0 + 0x60D) == 1) {
        int *vt = *(int **)(a0 + 0x214);
        short off = *(short *)((char *)vt + 0x80);
        void *(*fp)() = *(void *(**)())((char *)vt + 0x84);
        void *src = fp(a0 + off);
        VU0_LQC2(4, src, 0);
        VU0_SQC2(4, buf, 0);
        if (*(int *)(a0 + 0x600) == 0) {
            buf[1] = buf[1] - *(float *)(a0 + 0x790);
        } else {
            buf[1] = buf[1] + *(float *)(a0 + 0x790);
        }
        {
            int *vt2 = *(int **)(a0 + 0x214);
            short off2 = *(short *)((char *)vt2 + 0x70);
            void (*fp2)() = *(void (**)())((char *)vt2 + 0x74);
            fp2(a0 + off2, buf);
        }
        *(int *)(a0 + 0x5B8) = *(int *)(a0 + 0x5B8) | 0x100;
        *(unsigned char *)(a0 + 0x60D) = 0;
        *(unsigned char *)(a0 + 0x2F4) = 0;
        *(unsigned char *)(a0 + 0x2F5) = 0;
        *(unsigned char *)(a0 + 0x2F6) = 0;
        *(unsigned char *)(a0 + 0x2F7) = 0;
    }
}
__attribute__((section(".text.cOm5a_setFaceClose")))
void cOm5a_setFaceClose(int *a0) {
    int p;
    a0[0x182] = 2;
    a0[0x181] = 0;
    p = a0[0x189];
    if (p != 0) {
        cDamageUnit_SetDamageCollActive(p, 0);
    }
}

