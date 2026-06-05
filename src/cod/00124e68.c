/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern char D_00429C80[];
extern char D_00574380[];
extern void func_001FE278(char *, int);
extern void func_001B6F38(int *, int);
extern int D_00785798;
extern int D_00429D50;
extern int D_00785878;
extern void func_001B8058(void);
extern void func_0031EEA8(void *a, void *b, void *c);
extern int D_007863C8;
extern int D_00786598;
extern int D_0044FBA8;
extern int D_00460D58;
extern int D_0044FBB8;
extern void func_002B6528(void);
extern int SignalSema(int sema);
extern int SleepThread(void);
extern void func_002A7498(char *a0, int a1, float f12);

__attribute__((section(".text.func_001C2820")))
void func_001C2820(int *a0, int a1) {
    *(char **)((char *)a0 + 0x214) = D_00429C80;
    if (a0[0x180] != 0) {
        func_001FE278(D_00574380, a0[0x180]);
        a0[0x180] = 0;
    }
    if (a0[0x181] != 0) {
        func_001FE278(D_00574380, a0[0x180]);
        a0[0x180] = 0;
    }
    func_001B6F38(a0, a1);
}

__attribute__((section(".text.func_001C3BE8")))
void *func_001C3BE8(void)
{
    if (D_00785798 == 0) {
        func_001B8058();
        func_0031EEA8(&D_00785798, &D_00429D50, &D_00785878);
    }
    return &D_00785798;
}

__attribute__((section(".text.func_00300148")))
void *func_00300148(void)
{
    if (D_007863C8 == 0) {
        if (D_00786598 == 0) {
            func_002B6528();
            func_0031EEA8(&D_00786598, &D_0044FBA8, &D_00460D58);
        }
        func_0031EEA8(&D_007863C8, &D_0044FBB8, &D_00786598);
    }
    return &D_007863C8;
}

__attribute__((section(".text.func_002D5AA0")))
void func_002D5AA0(char *a0, int a1)
{
    *(short *)(a0 + 0xC) = 1;
    *(short *)(a0 + 0xE) = (short)a1;
    SignalSema(*(int *)(*(int *)(a0 + 0x0) + 0x28));
    SleepThread();
}

__attribute__((section(".text.func_00124E68")))
void func_00124E68(char *a0, float f12)
{
    char *a1 = *(char **)(a0 + 0x640);
    if (a1 != 0) {
        char *v1 = *(char **)(a1 + 0x214);
        short off = *(short *)(v1 + 0x68);
        int (*fn)(char *) = *(int (**)(char *))(v1 + 0x6C);
        int r = fn(a1 + off);
        func_002A7498(a0, r, f12);
    }
}
