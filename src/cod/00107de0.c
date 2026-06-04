/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_0041DCC8[];
extern void func_0030F5A0(void);
extern int D_004615F0[];
extern void func_0012C418(void);

__attribute__((section(".text.func_00144AD0")))
void func_00144AD0(void *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_00107DE0")))
void func_00107DE0(int a0, int a1) {
    if (a1 == 0xFFFF) {
        if (a0 != 0) {
            *(int*)((char*)D_004615F0+0) = 0;
            *(float*)((char*)D_004615F0+0xC) = 1.0f;
            *(int*)((char*)D_004615F0+0x8) = 0;
            *(int*)((char*)D_004615F0+0x4) = 0;
        }
    }
}

__attribute__((section(".text.func_0010BCC0")))
void func_0010BCC0(void *a0, int a1) {
    if (a1) {
        *(unsigned char*)((char*)a0+0x2F4) = 6;
        *(float*)((char*)a0+0x54C) = 5.0f;
        *(unsigned char*)((char*)a0+0x2F5) = 0;
        *(unsigned char*)((char*)a0+0x2F6) = 0;
        *(unsigned char*)((char*)a0+0x2F7) = 0;
    } else {
        func_0012C418();
    }
}

__attribute__((section(".text.func_0012CD90")))
void func_0012CD90(void *a0, float *a1, float f12) {
    float *v0 = (float*)((char*)a0+0x660);
    if (v0 != a1) {
        *v0 = *a1;
        v0[1] = a1[1];
        v0[2] = a1[2];
    }
    *(float*)((char*)a0+0x670) = f12;
    *(unsigned char*)((char*)a0+0x2F5) = 0x34;
    *(unsigned char*)((char*)a0+0x2F4) = 0;
    *(unsigned char*)((char*)a0+0x2F6) = 0;
    *(unsigned char*)((char*)a0+0x2F7) = 0;
}

__attribute__((section(".text.func_0012CDF0")))
void func_0012CDF0(char *a0, float *a1) {
    float *p = (float*)(a0 + 0x650);
    if (p == a1) return;
    *(float*)(a0 + 0x650) = a1[0];
    p[1] = a1[1];
    p[2] = a1[2];
}
