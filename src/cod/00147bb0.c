extern void Tramp_func_0030A2E0_00147548(int a, int b, void *buf);
extern void Obj0000_Set_D_007474A0_Fields_5D8_5E0(int a);
extern char **D_003C2384;

__attribute__((section(".text.func_00147BB0")))
void func_00147BB0(int a0, int a1, int a2) {
    int buf[16];
    func_001478A8(buf, a2);
    Tramp_func_0030A2E0_00147548(a0, a1, buf);
}

__attribute__((section(".text.func_00147BF8")))
void func_00147BF8(int a0, int a1, int a2) {
    int buf[16];
    func_00147A08(buf, a2);
    Tramp_func_0030A2E0_00147548(a0, a1, buf);
}

__attribute__((section(".text.func_00161780")))
void func_00161780(int a0) {
    char *p;
    Obj0000_Set_D_007474A0_Fields_5D8_5E0(a0);
    func_002AA078(a0);
    p = *D_003C2384;
    *(int *)(p + 0x4C) = 0;
    *(int *)(p + 0x48) = 0;
    func_00161590(a0);
}

__attribute__((section(".text.func_00161CC0")))
void func_00161CC0(int a0) {
    char *p;
    Obj0000_Set_D_007474A0_Fields_5D8_5E0(a0);
    func_002AA078(a0);
    p = *D_003C2384;
    *(int *)(p + 0x34) = 0;
    *(int *)(p + 0x30) = 0;
    func_00161590(a0);
}

__attribute__((section(".text.func_001632A0")))
void func_001632A0(int a0) {
    int *v1;
    Obj0000_Set_D_007474A0_Fields_5D8_5E0(a0);
    func_002AA078(a0);
    v1 = *D_003C2384;
    v1[9] = 0;
    v1[8] = 0;
    func_00161590(a0);
}
