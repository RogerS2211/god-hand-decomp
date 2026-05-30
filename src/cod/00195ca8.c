extern int D_00424C30;
extern int D_00574380;

__attribute__((section(".text.func_00195CA8")))
void *func_00195CA8(void *a0, int a1) {
    int v1;
    *(int *)((char *)a0 + 0x214) = (int)&D_00424C30;
    v1 = *(int *)((char *)a0 + 0x600);
    if (v1 != 0) {
        func_001FE278(&D_00574380, v1);
        *(int *)((char *)a0 + 0x600) = 0;
    }
    return func_001C2820(a0, a1);
}
