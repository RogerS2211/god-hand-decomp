extern unsigned char D_0041D808[];

__attribute__((section(".text.func_001339C0")))
void func_001339C0(int *a0, int a1) {
    *(int *)((char *)a0 + 0x30) = (int)D_0041D808;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0(a0);
    }
}
