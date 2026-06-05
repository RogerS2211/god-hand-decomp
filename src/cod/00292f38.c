/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void func_002FB020(void *a0);
extern int PTR_DAT_003fa62c;
extern void func_003A8048(int a0);
extern void func_003ACA28(int a0, int a1);
extern void func_003A80A8(int a0);
extern float D_00741DC0;
extern float D_00754C48;

__attribute__((section(".text.func_002FBE50")))
void func_002FBE50(void *a0) {
    int r;
    r = func_002B5E50(a0);
    func_002B5CF0(a0, r);
    func_002FB020(a0);
}

__attribute__((section(".text.func_003A7CC0")))
void func_003A7CC0(int a0) {
    func_003A8048(PTR_DAT_003fa62c);
    func_003ACA28(PTR_DAT_003fa62c, a0);
    func_003A80A8(PTR_DAT_003fa62c);
}

__attribute__((section(".text.func_00292F38")))
void func_00292F38(void *a0, float f12) {
    *(float*)((char*)a0 + 0x548) = f12;
    D_00741DC0 = f12;
    D_00754C48 = f12;
}
