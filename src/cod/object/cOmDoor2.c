/* TU: cOmDoor2 [object] - recovered C++ class. */

#include "godhand/vu0.h"

__attribute__((section(".text.cOmDoor2_setOpen")))
void cOmDoor2_setOpen(int a0) {
    if (*(unsigned char*)((char*)a0 + 0x774) == 0) {
        *(unsigned char*)((char*)a0 + 0x2F4) = 1;
        *(unsigned char*)((char*)a0 + 0x2F5) = 0;
        *(unsigned char*)((char*)a0 + 0x2F6) = 0;
        *(unsigned char*)((char*)a0 + 0x2F7) = 0;
    }
}

__attribute__((section(".text.cOmDoor2_setClose")))
void cOmDoor2_setClose(int a0) {
    if (*(unsigned char*)((char*)a0 + 0x774) == 1) {
        *(unsigned char*)((char*)a0 + 0x2F4) = 2;
        *(unsigned char*)((char*)a0 + 0x2F5) = 0;
        *(unsigned char*)((char*)a0 + 0x2F6) = 0;
        *(unsigned char*)((char*)a0 + 0x2F7) = 0;
    }
}
#include "include_asm.h"

__attribute__((section(".text.cOmDoor2_setOpenFix")))
void cOmDoor2_setOpenFix(char *a0) {
    float buf[4] __attribute__((aligned(16)));
    if (*(unsigned char *)(a0 + 0x774) == 0) {
        int *vt = *(int **)(a0 + 0x214);
        short off = *(short *)((char *)vt + 0x80);
        void *(*fp)() = *(void *(**)())((char *)vt + 0x84);
        void *src = fp(a0 + off);
        VU0_LQC2(4, src, 0);
        VU0_SQC2(4, buf, 0);
        if (*(int *)(a0 + 0x778) == 0) {
            buf[1] = buf[1] + *(float *)(a0 + 0x770);
        } else {
            buf[1] = buf[1] - *(float *)(a0 + 0x770);
        }
        {
            int *vt2 = *(int **)(a0 + 0x214);
            short off2 = *(short *)((char *)vt2 + 0x70);
            void (*fp2)() = *(void (**)())((char *)vt2 + 0x74);
            fp2(a0 + off2, buf);
        }
        *(unsigned char *)(a0 + 0x774) = 1;
        *(unsigned char *)(a0 + 0x2F4) = 0;
        *(unsigned char *)(a0 + 0x2F5) = 0;
        *(unsigned char *)(a0 + 0x2F6) = 0;
        *(unsigned char *)(a0 + 0x2F7) = 0;
    }
}


__attribute__((section(".text.cOmDoor2_setCloseFix")))
void cOmDoor2_setCloseFix(char *a0) {
    float buf[4] __attribute__((aligned(16)));
    if (*(unsigned char *)(a0 + 0x774) == 1) {
        int *vt = *(int **)(a0 + 0x214);
        short off = *(short *)((char *)vt + 0x80);
        void *(*fp)() = *(void *(**)())((char *)vt + 0x84);
        void *src = fp(a0 + off);
        VU0_LQC2(4, src, 0);
        VU0_SQC2(4, buf, 0);
        if (*(int *)(a0 + 0x778) == 0) {
            buf[1] = buf[1] - *(float *)(a0 + 0x770);
        } else {
            buf[1] = buf[1] + *(float *)(a0 + 0x770);
        }
        {
            int *vt2 = *(int **)(a0 + 0x214);
            short off2 = *(short *)((char *)vt2 + 0x70);
            void (*fp2)() = *(void (**)())((char *)vt2 + 0x74);
            fp2(a0 + off2, buf);
        }
        *(unsigned char *)(a0 + 0x774) = 0;
        *(unsigned char *)(a0 + 0x2F4) = 0;
        *(unsigned char *)(a0 + 0x2F5) = 0;
        *(unsigned char *)(a0 + 0x2F6) = 0;
        *(unsigned char *)(a0 + 0x2F7) = 0;
    }
}


__attribute__((section(".text.cOmDoor2_setOpenType")))
void cOmDoor2_setOpenType(int a0, int a1) {
    if (*(int *)((char *)a0 + 0x778) == a1) {
        return;
    }
    if (*(unsigned char *)((char *)a0 + 0x774) == 1) {
        cOmDoor2_setCloseFix(a0);
        *(int *)((char *)a0 + 0x778) = a1;
        cOmDoor2_setOpenFix(a0);
    } else {
        *(int *)((char *)a0 + 0x778) = a1;
    }
}

