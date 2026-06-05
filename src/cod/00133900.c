extern int D_0044EAB8;
extern int D_0044EB70;
extern int D_0044EC68;
extern int D_0044EFA0;
extern int D_0044F078;
extern int D_0044F1C8;
extern int D_0044F270;
extern int D_0044F3A0;
extern int D_0044F630;
extern int D_0044F880;
extern int D_0044FCF8;
extern int D_0044FC98;
extern int D_0044FC38;
extern int D_00460D08;
extern int D_0041D618;
extern int D_00460D10;
extern int D_0041D830;
extern int D_00460D20;
extern int D_0041D8D8;
extern int D_00460D28;
extern int D_0041DD00;
extern int D_00460D30;
extern int D_0041ECB8;
extern int D_00460D38;
extern int D_0041F1D0;
extern int D_00429620;

__attribute__((section(".text.func_002FFCC8")))
void *func_002FFCC8(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044EAB8;
    }
    return a0;
}

__attribute__((section(".text.func_002FFD08")))
void *func_002FFD08(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044EB70;
    }
    return a0;
}

__attribute__((section(".text.func_002FFD48")))
void *func_002FFD48(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044EC68;
    }
    return a0;
}

__attribute__((section(".text.func_002FFE10")))
void *func_002FFE10(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044EFA0;
    }
    return a0;
}

__attribute__((section(".text.func_002FFE50")))
void *func_002FFE50(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044F078;
    }
    return a0;
}

__attribute__((section(".text.func_002FFE90")))
void *func_002FFE90(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044F1C8;
    }
    return a0;
}

__attribute__((section(".text.func_002FFED0")))
void *func_002FFED0(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044F270;
    }
    return a0;
}

__attribute__((section(".text.func_002FFF50")))
void *func_002FFF50(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044F3A0;
    }
    return a0;
}

__attribute__((section(".text.func_00300020")))
int func_00300020(int a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int *)(a0 + 0xF0) = (int)&D_0044F630;
    }
    return a0;
}

__attribute__((section(".text.func_003000B0")))
int func_003000B0(int a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int *)(a0 + 0xF0) = (int)&D_0044F880;
    }
    return a0;
}

__attribute__((section(".text.func_00304D70")))
int func_00304D70(int a0) {
    if (a0) {
        func_00302790(a0);
        *(int *)(a0 + 0xF0) = (int)&D_0044FCF8;
    }
    return a0;
}

__attribute__((section(".text.func_00304DB0")))
int func_00304DB0(int a0) {
    if (a0) {
        func_00302790(a0);
        *(int *)(a0 + 0xF0) = (int)&D_0044FC98;
    }
    return a0;
}

__attribute__((section(".text.func_00304DF0")))
int func_00304DF0(int a0) {
    if (a0) {
        func_00302790(a0);
        *(int *)(a0 + 0xF0) = (int)&D_0044FC38;
    }
    return a0;
}

__attribute__((section(".text.IsActorActiveOrReady_379EC0")))
int IsActorActiveOrReady_379EC0(int a0) {
    if (func_00379F00(a0) != 0) {
        return 1;
    }
    return func_0037A020(a0);
}

__attribute__((section(".text.func_0037B620")))
void func_0037B620(int a0) {
    func_0037B660(a0);
    func_0037B0E0(a0);
    func_0037B918(a0);
    func_0037BC90(a0);
}

__attribute__((section(".text.GetOrInitSingleton_133900")))
int *GetOrInitSingleton_133900(void)
{
    if (D_00460D08 == 0) {
        func_0031EEC8(&D_00460D08, &D_0041D618);
    }
    return &D_00460D08;
}

__attribute__((section(".text.GetOrInit_D460D10_134270")))
int *GetOrInit_D460D10_134270(void)
{
    if (D_00460D10 == 0) {
        func_0031EEC8(&D_00460D10, &D_0041D830);
    }
    return &D_00460D10;
}

__attribute__((section(".text.func_00138B78")))
int *func_00138B78(void)
{
    if (D_00460D20 == 0) {
        func_0031EEC8(&D_00460D20, &D_0041D8D8);
    }
    return &D_00460D20;
}

__attribute__((section(".text.GetOrInitSingletonC_13C758")))
int *GetOrInitSingletonC_13C758(void)
{
    if (D_00460D28 == 0) {
        func_0031EEC8(&D_00460D28, &D_0041DD00);
    }
    return &D_00460D28;
}

__attribute__((section(".text.func_0013D3C0")))
void func_0013D3C0(void *a0)
{
    func_002A9EA0(a0, 1, 3);
    func_002A9EA0((char *)a0 + 0xD0, 1, 0x20);
    *(short *)((char *)a0 + 0x92) = 0;
}

__attribute__((section(".text.func_00145160")))
void func_00145160(void *a0, int a1)
{
    int r;
    r = func_003A5148((char *)a0 + 0x3B4, a1, *(short *)((char *)a0 + 0x3B2) << 1);
    *(int *)((char *)a0 + 0x90) |= 0x40000000;
}

__attribute__((section(".text.GetOrInitSingletonD_150638")))
void *GetOrInitSingletonD_150638(void) {
    if (D_00460D30 == 0) {
        func_0031EEC8(&D_00460D30, &D_0041ECB8);
    }
    return &D_00460D30;
}

__attribute__((section(".text.GetOrInit_00460D38_161628")))
void *GetOrInit_00460D38_161628(void) {
    if (D_00460D38 == 0) {
        func_0031EEC8(&D_00460D38, &D_0041F1D0);
    }
    return &D_00460D38;
}

__attribute__((section(".text.InitActorWithVtableAndTimer_1BE8B0")))
void *InitActorWithVtableAndTimer_1BE8B0(void *a0) {
    func_001B6E90(a0);
    *(int *)((char *)a0 + 0x604) = 0x3E9;
    *(int *)((char *)a0 + 0x214) = (int)&D_00429620;
    *(int *)((char *)a0 + 0x600) = 0;
    return a0;
}
