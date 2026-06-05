/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern unsigned int D_00747A84;
extern int D_00586B34;
extern char D_00747470[];
extern int D_00747A30;
extern char D_0044A920[];
extern char D_0044A940[];
extern char D_0044A958[];
extern char D_00583F20[];
extern int D_003C3CF0;
extern void func_003A6C58(void *a0, void *a1, void *a2);

__attribute__((section(".text.InitGameState_296458")))
void InitGameState_296458(void *a0) {
    void *v0;
    float *v1;
    float *p;
    unsigned long b;
    InitSubState_2975F8(a0);
    D_00747A84 = D_00747A84 | 0x20000000;
    *(char*)((char*)a0+0x34) = 0;
    *(int*)((char*)a0+8) = *(int*)((char*)a0+8) | 1;
    v0 = Obj0000_Get_D_00747A94_2DB6B0();
    v1 = *(float**)((char*)v0+0xF0);
    p = (float*)((char*)a0+0x20);
    if (p != v1) {
        p[0] = v1[0];
        p[1] = v1[1];
        p[2] = v1[2];
    }
    *(float*)((char*)a0+0x30) = *(float*)((char*)v0+0x104);
    *(float*)((char*)v0+0x54C) = 60.0f;
    *(char*)((char*)a0+4) = 0;
    *(char*)((char*)a0+5) = 0;
    *(char*)((char*)a0+6) = 0;
    *(char*)((char*)a0+7) = 0;
    b = D_00586B34;
    if (((b>>3)&1)==0) {} else {
        func_00307208(D_00747470, 0, 0xA, 0, 0xFF000000, 0xFF000000, 0);
    }
}

__attribute__((section(".text.LoadResourceEntry_297378")))
void LoadResourceEntry_297378(void *a0) {
    char *s = (char*)a0;
    unsigned long b = *(unsigned char*)(s + 8);
    int buf[16];
    if ((b >> 7) != 0) return;
    if ((D_00747A30 & 0x400) != 0) {
        func_003A6C58(buf, D_0044A920, D_0044A940);
    } else {
        func_003A6C58(buf, D_0044A958, D_0044A940);
    }
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0xC) = SetupSlotFromField78_200CB0(D_00583F20, buf, s + 0x10, D_003C3CF0, 0, 0, 0, 0);
}
