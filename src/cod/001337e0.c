extern unsigned char D_0041D5A8[];

__attribute__((section(".text.func_001337E0")))
void func_001337E0(int *a0, int a1) {
    *(int *)((char *)a0 + 0x5C) = (int)D_0041D5A8;
    if (a1 & 1) {
        func_0030F5A0(a0);
    }
}
