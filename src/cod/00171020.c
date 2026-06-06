extern int D_00785848;
extern int D_004209D0;
extern int D_00785858;
extern unsigned char D_005864F0[];
extern int D_00747B00[];
extern int *PTR_DAT_003c2f84;

__attribute__((section(".text.func_00171020")))
void *func_00171020(void) {
    if (D_00785848 == 0) {
        GetPilotClassDesc_1BDE00();
        SetField_0_4_8_31EEA8(&D_00785848, &D_004209D0, &D_00785858);
    }
    return &D_00785848;
}

__attribute__((section(".text.FindResolveActor_295978")))
int FindResolveActor_295978(unsigned char *a0)
{
    int v0 = func_00290868(D_005864F0, *a0);
    *(int *)((char *)a0 + 4) = v0;
    return v0 != 0;
}

__attribute__((section(".text.func_002959B0")))
int func_002959B0(int *a0, int a1)
{
    if (FindResolveActor_295978(a0)) {
        int a2 = *(int *)((char *)a0 + 4);
        int v0 = *(int *)(a2 + 0x214);
        short off = *(short *)(v0 + 0x70);
        void (*fp)(int, int) = *(void (**)(int, int))(v0 + 0x74);
        fp(a2 + off, a1);
        func_00149EB8(*(int *)((char *)a0 + 4));
    }
}

struct vec4 { int a; float b; int c; float d; };

__attribute__((section(".text.func_00295A08")))
void func_00295A08(int *a0, int a1, float f12)
{
    if (FindResolveActor_295978(a0)) {
        int s0 = *(int *)((char *)a0 + 4);
        int v0 = *(int *)(s0 + 0x214);
        short off = *(short *)(v0 + 0x70);
        void (*fp)(int, int) = *(void (**)(int, int))(v0 + 0x74);
        fp(s0 + off, a1);
        {
            int a2 = *(int *)(s0 + 0x214);
            struct vec4 v;
            short off2 = *(short *)(a2 + 0x78);
            v.a = 0;
            v.b = f12;
            v.c = 0;
            v.d = 1.0f;
            (*(void (**)(int, struct vec4 *))(a2 + 0x7C))(s0 + off2, &v);
        }
        func_00149EB8(*(int *)((char *)a0 + 4));
    }
}

__attribute__((section(".text.GetActorFieldPtr_295AF8")))
int *GetActorFieldPtr_295AF8(int *a0)
{
    return FindResolveActor_295978(a0) ? (int *)(*(int *)((char *)a0 + 4) + 0x100) : D_00747B00;
}

__attribute__((section(".text.UpdateSlotCurValues_295860")))
int UpdateSlotCurValues_295860(char *a0)
{
    int *v1 = PTR_DAT_003c2f84;
    int s3;
    unsigned int s2;
    char *s0;

    if (*(unsigned char *)((char *)v1 + 0x14) == 1) {
        return 0;
    }

    s3 = 0;
    s2 = 0;
    s0 = a0 + 0x10;
    for (; s2 < 2; s2++, s0 += 0x18) {
        if (*(unsigned char *)(s0 + 0x13)) {
            int v1b = func_002951B0(a0, s0);
            short cur = *(short *)(s0 + 0x16);
            if (cur >= *(short *)(v1b + 0x548)) {
                *(short *)(v1b + 0x54A) = *(unsigned short *)(v1b + 0x548);
            } else {
                *(short *)(v1b + 0x54A) = cur;
            }
            *(int *)(a0 + 4) = *(unsigned char *)(s0 + 0x12) + 0x200;
            *(unsigned char *)(s0 + 0x13) = 0;
            s3++;
        }
    }
    return s3 != 0;
}

__attribute__((section(".text.func_00295B38")))
int func_00295B38(void *a0)
{
    int v;
    if (FindResolveActor_295978(a0) == 0) {
        return 0;
    }
    v = *(int *)((char *)a0 + 4);
    if (v != 0) {
        return func_00290770(D_005864F0, v);
    }
    return 0;
}

__attribute__((section(".text.SetVia4_Float_54C_295B80")))
void SetVia4_Float_54C_295B80(void *a0, float f)
{
    if (FindResolveActor_295978(a0)) {
        char *p = *(char **)((char *)a0 + 4);
        *(float *)(p + 0x54C) = f;
    }
}

__attribute__((section(".text.func_00295BC0")))
void func_00295BC0(void *a0, int a1)
{
    if (FindResolveActor_295978(a0)) {
        char *a2 = *(char **)((char *)a0 + 4);
        char *v0 = *(char **)(a2 + 0x214);
        int off = *(short *)(v0 + 0x60);
        void (*fp)(char *, int) = *(void (**)(char *, int))(v0 + 0x64);
        fp(a2 + off, a1);
    }
}
