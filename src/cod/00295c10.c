extern unsigned char D_0044A870[];

__attribute__((section(".text.func_00295C10")))
void func_00295C10(void *a0, int a1)
{
    if (func_00295978(a0)) {
        char *p = *(char **)((char *)a0 + 4);
        if (func_003A5678(D_0044A870, *(int *)(p + 0x4AC)) == 0) {
            func_00276090(*(void **)((char *)a0 + 4), a1);
        }
    }
}

__attribute__((section(".text.func_00295C70")))
void func_00295C70(void *a0)
{
    if (func_00295978(a0)) {
        func_0028FB08(*(void **)((char *)a0 + 4));
    }
}

__attribute__((section(".text.func_00295CE8")))
void func_00295CE8(void *a0)
{
    if (func_00295978(a0)) {
        char *a1 = *(char **)((char *)a0 + 4);
        char *v0 = *(char **)(a1 + 0x214);
        int off = *(short *)(v0 + 0xD8);
        void (*fp)(char *) = *(void (**)(char *))(v0 + 0xDC);
        fp(a1 + off);
    }
}

__attribute__((section(".text.func_00295D88")))
void func_00295D88(void *a0, int a1) {
    if (func_00295978(a0, a1)) {
        *(short*)(*(char**)((char*)a0 + 4) + 0x548) = (short)a1;
    }
}

__attribute__((section(".text.func_00295E38")))
void func_00295E38(void *a0, int a1) {
    if (func_00295978(a0, a1)) {
        *(int*)(*(char**)((char*)a0 + 4) + 0x560) = a1;
    }
}

__attribute__((section(".text.func_00295DC8")))
int func_00295DC8(void *a0, int a1) {
    int *p;
    if (func_00295978(a0, a1) == 0) return 0;
    p = *(int**)((char*)a0 + 4);
    return *(short*)((char*)p + 0x54A);
}

__attribute__((section(".text.func_00295E00")))
int func_00295E00(void *a0, int a1) {
    int *p;
    if (func_00295978(a0, a1) == 0) return 0;
    p = *(int**)((char*)a0 + 4);
    return *(short*)((char*)p + 0x548);
}

__attribute__((section(".text.func_00295E78")))
void func_00295E78(void *a0, int a1) {
    if (func_00295978(a0, a1) == 0) return;
    if (a1 == 1) {
        *(int*)(*(char**)((char*)a0 + 4) + 0x5A0) &= ~4;
    } else {
        *(int*)(*(char**)((char*)a0 + 4) + 0x5A0) |= 4;
    }
}
