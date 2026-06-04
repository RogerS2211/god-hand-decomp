/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00466448[];
extern void func_002A9790(void *p);
extern void func_00149550(int a0, int a1);
extern int D_00747A80;
extern int D_00747AA8;
extern void func_00137AA0(void);
extern void *memcpy(void *, const void *, unsigned int);

__attribute__((section(".text.func_00149350")))
int func_00149350(int a0) {
    return func_001494F8(D_00466448, a0);
}

__attribute__((section(".text.func_00149550")))
void func_00149550(int a0, int a1) {
    if (a1 == 0xFFFF && a0 != 0) {
        func_002A9790(D_00466448);
    }
}

__attribute__((section(".text.func_00149580")))
void func_00149580(void) {
    func_00149550(1, 0xFFFF);
}

__attribute__((section(".text.func_0014B470")))
int func_0014B470(int a0) {
    int v1;
    if (D_00747A80 & 0x800000) {
        return 1;
    }
    v1 = *(int*)(a0 + 0x250);
    if (v1 & 2) {
        return 1;
    }
    if (v1 & 0x10000) {
        return 0;
    }
    return func_001F8AD8((int*)(a0 + 0x260), (int*)(a0 + 0x80)) == 0;
}

__attribute__((section(".text.func_0014B5D8")))
int func_0014B5D8(int a0, int a1) {
    if (*(int*)(*(int*)(a1 + 0x414) + 0x34) & 0x200000) {
        int a2 = D_00747AA8;
        if (a2) {
            return func_00148BD8(a1, *(int*)(a0 + 0x2C4), a2, 0);
        }
    }
    return func_00148D30(a1, *(int*)(a0 + 0x2C4));
}

__attribute__((section(".text.func_00137AE8")))
int func_00137AE8(int a0, int a1)
{
    if (a1 == 0) goto fail;
    memcpy((void *)(a0 + 4), (void *)a1, 0x2C);
    if (*(int *)(a0 + 4) != 0x444341) goto fail;
    if (*(int *)(a0 + 8) == 1) {
        *(int *)(a0 + 0) = a1 + 0x18;
        *(float *)(a0 + 0x1C) = 1.06f;
    } else {
        *(int *)(a0 + 0) = a1 + 0x2C;
    }
    return 1;
fail:
    func_00137AA0();
    return 0;
}
