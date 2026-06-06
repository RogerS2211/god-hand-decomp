/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_0041B598;
extern int D_0041B590;
extern int D_00462FC0;
extern void func_001347E8(void *, void *);
extern void func_002A73C8(void *, void *);
extern int D_007854C8;
extern int D_0041B638;
extern int D_007854D8;
extern void func_002A9300(void);
extern void SetField_0_4_8_31EEA8(void *, void *, void *);
extern int D_007854E8;
extern int D_0041B710;
extern int D_007854F8;
extern void func_0014FD20(void);
extern float D_003BC7C0;
extern void func_002A8578(void *, void *, void *, int, int, int, float);
extern void AddScaledVecToField_100_14F9F0(void *, float);
extern void AddScaledXfmVecToField_F0_14F928(void *, float);

__attribute__((section(".text.func_0010B5F0")))
int func_0010B5F0(unsigned char *a0) {
    int c;
    if (a0[0x2F4] != 0)
        return 0;
    c = a0[0x2F5];
    if (c != 0 && c != 0xA)
        return 0;
    return 1;
}

__attribute__((section(".text.func_00100280")))
void *func_00100280(void *a0) {
    void *r;
    func_002A7338(a0);
    *(int **)((char*)a0 + 0x214) = &D_0041B598;
    r = a0;
    *(int **)((char*)a0 + 0x4AC) = &D_0041B590;
    return r;
}

__attribute__((section(".text.func_001002C0")))
void func_001002C0(void *a0, void *a1) {
    *(int **)((char*)a0 + 0x214) = &D_0041B598;
    func_001347E8(&D_00462FC0, a0);
    func_002A73C8(a0, a1);
}

__attribute__((section(".text.GetOrInitSingleton_100328")))
void *GetOrInitSingleton_100328(void) {
    if (D_007854C8 == 0) {
        func_002A9300();
        SetField_0_4_8_31EEA8(&D_007854C8, &D_0041B638, &D_007854D8);
    }
    return &D_007854C8;
}

__attribute__((section(".text.GetOrInitSingletonAlt_101E48")))
void *GetOrInitSingletonAlt_101E48(void) {
    if (D_007854E8 == 0) {
        func_0014FD20();
        SetField_0_4_8_31EEA8(&D_007854E8, &D_0041B710, &D_007854F8);
    }
    return &D_007854E8;
}

__attribute__((section(".text.func_00102BD8")))
void func_00102BD8(void *a0) {
    void *r = Obj0000_Get_D_00747A94_2DB6B0();
    switch (*(unsigned char *)((char *)a0 + 0x2F6)) {
    case 0: {
        void *p = *(void **)((char *)a0 + 0x304);
        void *q = (void *)(*(int *)((char *)p + 0x24) + (int)p);
        func_002A8578(a0, q, q, 5, 0, 0, 0.0f);
        *(unsigned char *)((char *)a0 + 0x2F6) = *(unsigned char *)((char *)a0 + 0x2F6) + 1;
    }
    case 1:
        *(float *)((char *)r + 0x15F0) = D_003BC7C0;
        if (func_00157C18(a0) != 0) {
            *(unsigned char *)((char *)a0 + 0x2F4) = 0;
            *(unsigned char *)((char *)a0 + 0x2F5) = 0;
            *(unsigned char *)((char *)a0 + 0x2F6) = 0;
            *(unsigned char *)((char *)a0 + 0x2F7) = 0;
        }
        AddScaledVecToField_100_14F9F0(a0, 1.0f);
        AddScaledXfmVecToField_F0_14F928(a0, 1.0f);
        break;
    default:
        break;
    }
}
