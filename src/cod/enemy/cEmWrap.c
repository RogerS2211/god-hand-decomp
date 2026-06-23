/* TU: cEmWrap [enemy] - recovered C++ class. */
struct vec4 { int a; float b; int c; float d; };
extern int D_00747B00[];
extern unsigned char D_005864F0[];
extern void func_0026E7A8(int a0, int a1);
extern void func_0026E7A0(int a0, float f);
extern void func_002736F8(int a0);
extern int D_0044A878;
extern void cEma2_SetEscPos(int a0, int a1);

__attribute__((section(".text.cEmWrap_setPos_2959B0")))
int cEmWrap_setPos_2959B0(int *a0, int a1)
{
    if (FindResolveActor_295978(a0)) {
        int a2 = *(int *)((char *)a0 + 4);
        int v0 = *(int *)(a2 + 0x214);
        short off = *(short *)(v0 + 0x70);
        void (*fp)(int, int) = *(void (**)(int, int))(v0 + 0x74);
        fp(a2 + off, a1);
        cModel_calcParts(*(int *)((char *)a0 + 4));
    }
}

__attribute__((section(".text.cEmWrap_setPos_295A08")))
void cEmWrap_setPos_295A08(int *a0, int a1, float f12)
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
        cModel_calcParts(*(int *)((char *)a0 + 4));
    }
}

__attribute__((section(".text.cEmWrap_getRot")))
int *cEmWrap_getRot(int *a0)
{
    return FindResolveActor_295978(a0) ? (int *)(*(int *)((char *)a0 + 4) + 0x100) : D_00747B00;
}

__attribute__((section(".text.cEmWrap_release")))
int cEmWrap_release(void *a0)
{
    int v;
    if (FindResolveActor_295978(a0) == 0) {
        return 0;
    }
    v = *(int *)((char *)a0 + 4);
    if (v != 0) {
        return cEmManage_ReleaseEm(D_005864F0, v);
    }
    return 0;
}

__attribute__((section(".text.cEmWrap_setSuspend")))
void cEmWrap_setSuspend(void *a0, int a1)
{
    if (FindResolveActor_295978(a0)) {
        char *a2 = *(char **)((char *)a0 + 4);
        char *v0 = *(char **)(a2 + 0x214);
        int off = *(short *)(v0 + 0x60);
        void (*fp)(char *, int) = *(void (**)(char *, int))(v0 + 0x64);
        fp(a2 + off, a1);
    }
}

__attribute__((section(".text.cEmWrap_setLockOff")))
void cEmWrap_setLockOff(void *a0, int a1)
{
    extern unsigned char D_0044A870[];
    if (FindResolveActor_295978(a0)) {
        char *p = *(char **)((char *)a0 + 4);
        if (func_003A5678(D_0044A870, *(int *)(p + 0x4AC)) == 0) {
            func_00276090(*(void **)((char *)a0 + 4), a1);
        }
    }
}

__attribute__((section(".text.cEmWrap_setDead")))
void cEmWrap_setDead(void *a0)
{
    if (FindResolveActor_295978(a0)) {
        func_0028FB08(*(void **)((char *)a0 + 4));
    }
}

__attribute__((section(".text.cEmWrap_isDead")))
int cEmWrap_isDead(int a0)
{
    if (FindResolveActor_295978(a0) == 0) {
        return 1;
    }
    return cEmBase_checkDeadFlag(*(int *)(a0 + 4));
}

__attribute__((section(".text.cEmWrap_StartAction")))
void cEmWrap_StartAction(void *a0)
{
    if (FindResolveActor_295978(a0)) {
        char *a1 = *(char **)((char *)a0 + 4);
        char *v0 = *(char **)(a1 + 0x214);
        int off = *(short *)(v0 + 0xD8);
        void (*fp)(char *) = *(void (**)(char *))(v0 + 0xDC);
        fp(a1 + off);
    }
}

__attribute__((section(".text.cEmWrap_GetVital")))
int cEmWrap_GetVital(void *a0, int a1) {
    int *p;
    if (FindResolveActor_295978(a0, a1) == 0) return 0;
    p = *(int**)((char*)a0 + 4);
    return *(short*)((char*)p + 0x54A);
}

__attribute__((section(".text.cEmWrap_GetVitalMax")))
int cEmWrap_GetVitalMax(void *a0, int a1) {
    int *p;
    if (FindResolveActor_295978(a0, a1) == 0) return 0;
    p = *(int**)((char*)a0 + 4);
    return *(short*)((char*)p + 0x548);
}

__attribute__((section(".text.cEmWrap_setDropItem")))
void cEmWrap_setDropItem(void *a0, int a1) {
    if (FindResolveActor_295978(a0, a1)) {
        *(int*)(*(char**)((char*)a0 + 4) + 0x560) = a1;
    }
}

__attribute__((section(".text.cEmWrap_setScrCollEnable")))
void cEmWrap_setScrCollEnable(void *a0, int a1) {
    if (FindResolveActor_295978(a0, a1) == 0) return;
    if (a1 == 1) {
        *(int*)(*(char**)((char*)a0 + 4) + 0x5A0) &= ~4;
    } else {
        *(int*)(*(char**)((char*)a0 + 4) + 0x5A0) |= 4;
    }
}

__attribute__((section(".text.cEmWrap_CkActive")))
int cEmWrap_CkActive(void *a0){
 extern unsigned char D_0044A870[];
 char *p;
 if(!FindResolveActor_295978(a0)) return 0;
 p=*(char**)((char*)a0+4);
 return func_003A5678(D_0044A870,*(int*)(p+0x4AC))?0:Obj0000_IsSet_Field_16D0_Bit_1_26ECC0(*(void**)((char*)a0+4));
}

__attribute__((section(".text.cEmWrap_ckGoto")))
int cEmWrap_ckGoto(void *a0){
 extern unsigned char D_0044A870[];
 char *p;
 if(!FindResolveActor_295978(a0)) return 0;
 p=*(char**)((char*)a0+4);
 return func_003A5678(D_0044A870,*(int*)(p+0x4AC))?0:func_0026EA28(*(void**)((char*)a0+4));
}

__attribute__((section(".text.cEmWrap_SetKeepPos")))
void cEmWrap_SetKeepPos(void *a0, int a1) {
    extern unsigned char D_0044A870[];
    void *s0 = a0;
    int s1 = a1;
    if (FindResolveActor_295978(s0)) {
        int *v0 = *(int**)((char*)s0 + 4);
        if (func_003A5678(&D_0044A870, *(int*)((char*)v0 + 0x4AC)) == 0)
            func_0026E7A8(*(int*)((char*)s0 + 4), s1);
    }
}

__attribute__((section(".text.cEmWrap_SetKeepLength")))
void cEmWrap_SetKeepLength(void *a0, float f) {
    extern int FindResolveActor_295978(void *a0, float f);
    extern int D_0044A870;
    if (FindResolveActor_295978(a0, f)) {
        int *p = *(int **)((char *)a0 + 4);
        if (func_003A5678(&D_0044A870, p[0x4AC / 4]) == 0) {
            func_0026E7A0(*(int *)((char *)a0 + 4), f);
        }
    }
}

__attribute__((section(".text.cEmWrap_clearNoMove")))
void cEmWrap_clearNoMove(void *a0, float f) {
    extern int FindResolveActor_295978(void *a0, float f);
    extern int D_0044A870;
    if (FindResolveActor_295978(a0, f)) {
        int *p = *(int **)((char *)a0 + 4);
        if (func_003A5678(&D_0044A870, p[0x4AC / 4]) == 0) {
            func_002736F8(*(int *)((char *)a0 + 4));
        }
    }
}

__attribute__((section(".text.cEmWrap_SetEscPos")))
void cEmWrap_SetEscPos(void *a0, int a1, float f) {
    extern int FindResolveActor_295978(void *a0, float f);
    if (FindResolveActor_295978(a0, f)) {
        int *p = *(int **)((char *)a0 + 4);
        if (func_003A5678(&D_0044A878, p[0x4AC / 4]) == 0) {
            cEma2_SetEscPos(*(int *)((char *)a0 + 4), a1);
        }
    }
}
