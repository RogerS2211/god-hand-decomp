/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern volatile int D_003D847C;
extern volatile int D_003D8478;
extern void NoOp_33E6A8(int);
extern void NoOp_33E6B0(void);

__attribute__((section(".text.MaxByte538_292EF0")))
void MaxByte538_292EF0(void *a0, int a1) {
    if (*(signed char*)((char*)a0 + 0x538) < a1)
        *(signed char*)((char*)a0 + 0x538) = (signed char)a1;
}

__attribute__((section(".text.PushGlobalD8478History_331C78")))
void PushGlobalD8478History_331C78(int a0) {
    D_003D8478 = D_003D847C;
    D_003D847C = a0;
}

__attribute__((section(".text.GuardedCall_00329FD0_329F98")))
int GuardedCall_00329FD0_329F98(int a0) {
    int r;
    NoOp_33E6A8(a0);
    r = func_00329FD0(a0);
    NoOp_33E6B0();
    return r;
}
