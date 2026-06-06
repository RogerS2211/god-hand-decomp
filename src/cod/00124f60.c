/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00463050;
extern void func_0013B9B8(void *a0);
extern void func_00138D40(void *a0, int a1);
extern void func_0030F518(void);
extern void func_00150710(float a, float b, float c);

__attribute__((section(".text.func_00124F60")))
void func_00124F60(void *a0, int a1, int a2) {
    void *s0;
    if (((a2 ^ 1) & 1) != 0) {
        int v1 = *(int*)((char*)a0 + 0x15F4);
        if ((v1 & 2) == 0) {
            return;
        }
        *(int*)((char*)a0 + 0x15F4) = v1 & ~2;
    }
    s0 = &D_00463050;
    if (s0 != 0) {
        func_0013B9B8(s0);
    }
    func_00138D40(s0, 0);
}

__attribute__((section(".text.func_001B7280")))
void func_001B7280(void *a0, int a1, int a2) {
    char *v1 = (char *)GetListNodeAt404_Field25C_14B6F8(a0, 0);
    if (v1 != 0) {
        do {
            if (*(unsigned char *)(v1 + 0x40C) == a1) {
                if (a2 == 1) {
                    *(int *)(v1 + 0x380) &= 0xFFFFFFFE;
                } else {
                    *(int *)(v1 + 0x380) |= 1;
                }
            }
            v1 = *(char **)(v1 + 0x404);
        } while (v1 != 0);
    }
}

__attribute__((section(".text.func_0031D000")))
void func_0031D000(void) {
    func_0030F518();
}

__attribute__((section(".text.func_00147C60")))
void func_00147C60(void *a0, float *a1) {
    func_00150710(a1[12], a1[13], a1[14]);
}
