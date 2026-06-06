/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void ForwardStoredCallback_2C4DE0(void *a0);
extern void func_002C3820(void *a0);
extern void func_002D56A8(void *a0);
extern void SetFieldsCESignalSemaSleep_2D5AA0(int a0, int a1);
extern unsigned int D_00747A78;
extern char D_00463050[];
extern void func_00138DB8(void *a0, int a1);
extern void func_001390B8(void *a0, int a1, int a2, int a3, float f12, int t0, int t1);
extern void func_00138600(void *a0);
extern void func_0013B9B8(void *a0, int a1);
extern void func_00138D40(void *a0, int a1);
extern void ClearField15F4Bit1_124F60(int a0, int a1, int a2);
extern int *PTR_DAT_003c2f84;
extern int PTR_DAT_003c23a4;
extern void ClearSoundSlot_2C4390(char *a0);
extern void cMessage_deleteMessNo(int a0, int a1);
extern void func_0031C7E0(void *p, float w);

__attribute__((section(".text.func_002C3858")))
void func_002C3858(void *a0) {
    ForwardStoredCallback_2C4DE0(a0);
    func_002C3820(a0);
    func_002D56A8((char *)a0 + 0x1C);
}

__attribute__((section(".text.LoadScreenOverlay_2C3F10")))
int LoadScreenOverlay_2C3F10(void *a0, int a1) {
    char *s0;
    if (a1 == 0) {
        return 0;
    }
    D_00747A78 = D_00747A78 | 0x200000;
    s0 = D_00463050;
    func_00138DB8(s0, 0);
    s0 = D_00463050 + 0x530;
    func_001390B8(s0, a1, 0, 0, 0.0f, 0, 0);
    *(float *)(s0 + 0x3A8) = 0.0f;
    func_00138600(s0);
    *(char *)((char *)a0 + 0x111) = 1;
    return 1;
}

__attribute__((section(".text.func_002C3FC0")))
void func_002C3FC0(void *a0) {
    char *s0;
    D_00747A78 = D_00747A78 & 0xFFDFFFFF;
    s0 = D_00463050;
    if (s0) {
        func_0013B9B8(s0, 0);
    }
    func_00138D40(s0, 0);
    ClearField15F4Bit1_124F60(Obj0000_Get_D_00747A94_2DB6B0(), 0, 1);
    *(char *)((char *)a0 + 0x111) = 0;
}

__attribute__((section(".text.func_002C4078")))
void func_002C4078(void *a0) {
    while (func_002C4040(a0) == 0) {
        SetFieldsCESignalSemaSleep_2D5AA0(*(int *)((char *)PTR_DAT_003c2f84 + 0x20), 1);
    }
}

__attribute__((section(".text.ForwardWithResolvedHandle_2C40C8")))
int ForwardWithResolvedHandle_2C40C8(void *a0, unsigned short a1, int a2, int a3, unsigned char t0, int t1) {
    int v0;
    if (a2 != 0) {
        v0 = func_0031CE38(a2);
    } else {
        v0 = 0;
    }
    return func_002C4150(a0, a1, v0, a3, t0, t1);
}

__attribute__((section(".text.SetSoundSlot_2C42E0")))
void SetSoundSlot_2C42E0(char *a0, int a1) {
    if (*(unsigned short*)(a0 + 0x112) != 0xFFFF) {
        ClearSoundSlot_2C4390(a0);
    }
    if (func_002AEB68(PTR_DAT_003c23a4, a1, 0, 0, 0) != 0xFFFF) {
        *(unsigned short*)(a0 + 0x112) = a1;
    }
}

__attribute__((section(".text.ClearSoundSlot_2C4390")))
void ClearSoundSlot_2C4390(char *a0) {
    if (*(unsigned short*)(a0 + 0x112) != 0xFFFF) {
        cMessage_deleteMessNo(PTR_DAT_003c23a4, *(unsigned short*)(a0 + 0x112));
        *(unsigned short*)(a0 + 0x112) = 0xFFFF;
    }
}

__attribute__((section(".text.SetObjectTransform_2C4440")))
void SetObjectTransform_2C4440(int a0, char *a1, float p0, float p1, float p2, float p3) {
    typedef struct { float a, b, c, d; } Vec4;
    char *obj = a1;
    Vec4 s1;
    if ((*(unsigned short*)(obj + 0x2FE) ^ 0x100) != 0) {
        char *vt;
        s1.d = 1.0f;
        vt = *(char**)(obj + 0x214);
        s1.a = p0; s1.b = p1; s1.c = p2;
        (*(void(**)(char*, Vec4*))(vt + 0x74))(obj + *(short*)(vt + 0x70), &s1);
        {
            Vec4 s2;
            Vec4 *q = &s2;
            char *vt2 = *(char**)(obj + 0x214);
            void (*fp2)(char*, Vec4*);
            char *arg2;
            arg2 = obj + *(short*)(vt2 + 0x78);
            s2.b = p3;
            s2.a = 0;
            s2.c = 0;
            q->d = 1.0f;
            fp2 = *(void(**)(char*, Vec4*))(vt2 + 0x7C);
            fp2(arg2, q);
        }
    } else {
        s1.a = p0; s1.b = p1; s1.c = p2; s1.d = 1.0f;
        func_0031C7E0(&s1, p3);
    }
}

__attribute__((section(".text.func_002C43D8")))
void func_002C43D8(char *a0) {
    while (func_002C4350(a0) == 1) {
        SetFieldsCESignalSemaSleep_2D5AA0(*(int*)((char*)PTR_DAT_003c2f84 + 0x20), 1);
    }
    ClearSoundSlot_2C4390(a0);
}
