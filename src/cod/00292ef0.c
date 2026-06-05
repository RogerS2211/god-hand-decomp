/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern volatile int D_003D847C;
extern volatile int D_003D8478;
extern void func_0033E6A8(int);
extern void func_0033E6B0(void);

__attribute__((section(".text.func_00292EF0")))
void func_00292EF0(void *a0, int a1) {
    if (*(signed char*)((char*)a0 + 0x538) < a1)
        *(signed char*)((char*)a0 + 0x538) = (signed char)a1;
}

__attribute__((section(".text.func_00331C78")))
void func_00331C78(int a0) {
    D_003D8478 = D_003D847C;
    D_003D847C = a0;
}

__attribute__((section(".text.GuardedCall_00329FD0_329F98")))
int GuardedCall_00329FD0_329F98(int a0) {
    int r;
    func_0033E6A8(a0);
    r = func_00329FD0(a0);
    func_0033E6B0();
    return r;
}
