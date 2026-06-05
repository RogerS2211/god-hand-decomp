/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern char D_0041B6A0[];
extern char D_0041B730[];
extern void func_001F6EE0(int x);
extern void func_0012ECF0(void *p);

__attribute__((section(".text.func_001451E0")))
short func_001451E0(char *a0) {
    int idx;
    int bound;
    if (*(short*)(a0+0x41E) == 3 && *(short*)(a0+0x420) == 0) {
        idx = *(short*)(a0+0x422) + 1;
        bound = *(short*)(a0+0x3B2);
        if (idx >= bound) {
            return *(short*)(a0 + 0x36C);
        }
        return *(short*)(a0 + (idx << 1) + 0x36C);
    }
    if (*(short*)(a0+0x41E) != 0) {
        return -1;
    }
    return -2;
}

__attribute__((section(".text.func_00100508")))
int func_00100508(void *a0) {
    *(char**)((char*)a0+0x214) = D_0041B6A0;
    return func_0014EA28(a0);
}

__attribute__((section(".text.Forward100FB8_101E98")))
int Forward100FB8_101E98(void) {
    return func_00100FB8(1, 0xFFFF);
}

__attribute__((section(".text.func_00102128")))
int func_00102128(void *a0) {
    *(char**)((char*)a0+0x214) = D_0041B730;
    return func_001002C0(a0);
}

__attribute__((section(".text.FreeFieldObject_1267F8")))
void FreeFieldObject_1267F8(char *a0) {
    if (*(int*)(a0 + 0x165C)) {
        func_001F6EE0(*(int*)(a0 + 0x165C));
    }
}

__attribute__((section(".text.InitZeroAndSetup_12E800")))
void InitZeroAndSetup_12E800(int *a0) {
    int *v0 = a0;
    v0[0] = 0;
    v0[1] = 0;
    v0[2] = 0;
    v0[3] = 0;
    v0[4] = 0;
    v0[5] = 0;
    v0[6] = 0;
    v0[7] = 0;
    v0[8] = 0;
    func_0012ECF0(v0);
}
