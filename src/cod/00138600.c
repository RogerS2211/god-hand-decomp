struct vtbl {
    char pad[0x10];
    short off;
    void (*fn)(int);
};

__attribute__((section(".text.func_00138600")))
void func_00138600(int a0) {
    struct vtbl *v0 = *(struct vtbl**)((char*)a0 + 0x35C);
    v0->fn(a0 + v0->off);
    func_00138558(a0);
    func_00138740(a0);
}

__attribute__((section(".text.func_0013D0B8")))
void func_0013D0B8(char *a0)
{
    func_002ABA78(a0);
    func_002ABA78(a0 + 0x140);
    func_002ABA78(a0 + 0x190);
    func_002ABA78(a0 + 0xA0);
    func_002ABA78(a0 + 0xF0);
}

__attribute__((section(".text.func_0013D100")))
void func_0013D100(char *a0)
{
    func_002AABA0(a0);
    func_002AABA0(a0 + 0x140);
    func_002AABA0(a0 + 0x190);
    func_002AABA0(a0 + 0xA0);
    func_002AABA0(a0 + 0xF0);
}
