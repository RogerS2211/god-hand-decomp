/* TU: cOl29 [object] - recovered C++ class. */
#include "godhand/vu0.h"
#include "include_asm.h"

__attribute__((section(".text.cOl29_setOpen")))
void cOl29_setOpen(unsigned char *a0)
{
    if (a0[0x764] == 0) {
        a0[0x2F7] = 0;
        a0[0x2F5] = 0;
        a0[0x2F6] = 0;
        a0[0x2F4] = 1;
    }
}

__attribute__((section(".text.cOl29_setClose")))
void cOl29_setClose(unsigned char *a0)
{
    if (a0[0x764] == 1) {
        a0[0x2F7] = 0;
        a0[0x2F5] = 0;
        a0[0x2F6] = 0;
        a0[0x2F4] = 2;
    }
}

__attribute__((section(".text.cOl29_isOpen")))
unsigned char cOl29_isOpen(unsigned char *a0) {
    return a0[0x764];
}

__attribute__((section(".text.cOl29_setOpenFix")))
void cOl29_setOpenFix(char *a0) {
    float buf[4] __attribute__((aligned(16)));
    if (*(unsigned char *)(a0 + 0x764) == 0) {
        int *vt = *(int **)(a0 + 0x214);
        short off = *(short *)((char *)vt + 0x80);
        void *(*fp)() = *(void *(**)())((char *)vt + 0x84);
        void *src = fp(a0 + off);
        VU0_LQC2(4, src, 0);
        VU0_SQC2(4, buf, 0);
        {
            int *vt2 = *(int **)(a0 + 0x214);
            short off2 = *(short *)((char *)vt2 + 0x70);
            void (*fp2)() = *(void (**)())((char *)vt2 + 0x74);
            fp2(a0 + off2, buf);
        }
        *(unsigned char *)(a0 + 0x764) = 1;
        *(unsigned char *)(a0 + 0x2F4) = 0;
        *(unsigned char *)(a0 + 0x2F5) = 0;
        *(unsigned char *)(a0 + 0x2F6) = 0;
        *(unsigned char *)(a0 + 0x2F7) = 0;
    }
}
__attribute__((section(".text.cOl29_setCloseFix")))
void cOl29_setCloseFix(char *a0) {
    float buf[4] __attribute__((aligned(16)));
    if (*(unsigned char *)(a0 + 0x764) == 1) {
        int *vt = *(int **)(a0 + 0x214);
        short off = *(short *)((char *)vt + 0x80);
        void *(*fp)() = *(void *(**)())((char *)vt + 0x84);
        void *src = fp(a0 + off);
        VU0_LQC2(4, src, 0);
        VU0_SQC2(4, buf, 0);
        {
            int *vt2 = *(int **)(a0 + 0x214);
            short off2 = *(short *)((char *)vt2 + 0x70);
            void (*fp2)() = *(void (**)())((char *)vt2 + 0x74);
            fp2(a0 + off2, buf);
        }
        *(unsigned char *)(a0 + 0x764) = 0;
        *(unsigned char *)(a0 + 0x2F4) = 0;
        *(unsigned char *)(a0 + 0x2F5) = 0;
        *(unsigned char *)(a0 + 0x2F6) = 0;
        *(unsigned char *)(a0 + 0x2F7) = 0;
    }
}
