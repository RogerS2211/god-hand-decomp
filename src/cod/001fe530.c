/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_007861A8;
extern int D_00460D48;
extern char D_0042C4F8[];
extern char D_0042C508[];
extern int D_007861B8;
extern char D_0042C518[];
extern int D_00583F20;

__attribute__((section(".text.func_001FE530")))
void *func_001FE530(void) {
    if (D_007861A8 == 0) {
        if (D_00460D48 == 0) {
            func_0031EEC8(&D_00460D48, D_0042C4F8);
        }
        SetField_0_4_8_31EEA8(&D_007861A8, D_0042C508, &D_00460D48);
    }
    return &D_007861A8;
}

__attribute__((section(".text.func_001FE5E0")))
void *func_001FE5E0(void) {
    if (D_007861B8 == 0) {
        if (D_00460D48 == 0) {
            func_0031EEC8(&D_00460D48, D_0042C4F8);
        }
        SetField_0_4_8_31EEA8(&D_007861B8, D_0042C518, &D_00460D48);
    }
    return &D_007861B8;
}

__attribute__((section(".text.ResetSlotArray_1FE6C8")))
void ResetSlotArray_1FE6C8(int *a0, int a1) { int i = a0[1]; while (--i != -1) func_001FF028((void *)(a0[2] + i * 0x5C)); a0[0] = a1; }

__attribute__((section(".text.GetActiveEntry_1FE9B8")))
int GetActiveEntry_1FE9B8(void *a0) {
    int v1 = func_001FEE00(a0);
    if (v1 >= 0)
        return UpdateStateReady_1FF238(*(int*)((char*)a0+8) + v1*0x5C);
    return 0;
}

__attribute__((section(".text.GetEntryParam_1FEA00")))
int GetEntryParam_1FEA00(void *a0) {
    int r = func_001FEE00(a0);
    if (r >= 0)
        return *(int*)(*(int*)((char*)a0+8) + r*0x5C + 0x10);
    return 0;
}

__attribute__((section(".text.FreeActiveEntry_1FEC90")))
int FreeActiveEntry_1FEC90(void *a0, int a1) {
    int v1 = func_001FEE00(a0);
    if (v1 < 0) return 0;
    func_001FF028(*(int*)((char*)a0+8) + v1*0x5C);
    return 1;
}

__attribute__((section(".text.func_001FECE0")))
int func_001FECE0(void *a0, int a1, int a2) {
    int v0 = func_001FEE00(a0);
    if (v0 >= 0)
        FreeActiveEntry_1FEC90(a0, a1);
    v0 = func_001FEEA0(a0);
    if (v0 < 0) return 0;
    func_001FF470(*(int*)((char*)a0+8) + v0*0x5C, a1, a2);
    *(int*)(*(int*)((char*)a0+8) + v0*0x5C + 4) = -0x64;
    return 1;
}

__attribute__((section(".text.UpdateStateReady_1FF238")))
int UpdateStateReady_1FF238(void *a0) {
    int v1;
    int ret;
    if ((*(int*)((char*)a0+8) & 1) == 0) goto common;
    ret = func_00201098(&D_00583F20, *(int*)((char*)a0+0x1C));
    if (ret == 1) return 0;
    if (ret == 0) goto zero;
    if (ret == 2) return 0;
    v1 = *(int*)((char*)a0+0x20);
    goto check;
zero:
    *(int*)((char*)a0+8) &= -2;
common:
    v1 = *(int*)((char*)a0+0x20);
check:
    if (v1 != 0xFFFF) {
        if (IsSlotArrayValid_1FF540(a0) == 0) return 0;
    }
    v1 = 2;
    *(int*)((char*)a0+0) = v1;
    return 1;
}
