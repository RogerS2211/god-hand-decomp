/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_0041D220[];
extern int D_00462FC0[];
extern void func_001347E8(void *a0, void *a1);
extern void func_001002C0(void *a0, void *a1);
extern void func_001351D8(void *a0, void *a1, int a2);
extern float func_00158288(void *a0, float f);
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);

__attribute__((section(".text.func_0013F238")))
void func_0013F238(char *a0, unsigned short a1, unsigned char a2, float f12, float f13) {
    if (*(int *)(a0 + 0x9C) == 0xFFFF) {
        *(int *)(a0 + 0x9C) = a1;
        *(float *)(*(char **)(a0 + 0x90) + 0x38) = f12;
        *(float *)(*(char **)(a0 + 0x90) + 0x3C) = f13;
        *(char *)(*(char **)(a0 + 0x98) + 0x4F) = a2;
    }
}

__attribute__((section(".text.func_0013F510")))
void func_0013F510(char *a0) {
    short i;
    for (i = 4; i >= 0; i--) {
        char *v1 = a0 + 0xB8 - (4 - i) * 4;
        *(int *)(v1 + 0x1A8) = 0;
        *(float *)(v1 + 0x218) = 1.0f;
        *(int *)(v1 + 0x0) = 0;
    }
    *(int *)(a0 + 0xA0) = 0;
    *(char *)(a0 + 0x358) = 0;
    *(char *)(a0 + 0x384) = 0;
}

__attribute__((section(".text.InitActorWithVtable_107EC8")))
void InitActorWithVtable_107EC8(void *a0, void *a1) {
    *(int **)((char*)a0+0x214) = D_0041D220;
    func_001347E8(D_00462FC0, a0);
    func_001002C0(a0, a1);
}

__attribute__((section(".text.UpdateBossPhase_10B780")))
void UpdateBossPhase_10B780(void *a0) {
    int st;
    int base;
    *(float*)((char*)a0 + 0x54C) = 5.0f;
    func_001351D8(D_00462FC0, a0, 0);
    *(int*)((char*)a0 + 0x15F4) = *(int*)((char*)a0 + 0x15F4) | 0x2000;
    *(float*)((char*)a0 + 0x5A8) = 1.0f;
    func_00158288(a0, 1.0f);
    st = *(unsigned char*)((char*)a0 + 0x2F6);
    switch (st) {
    case 0:
        base = *(int*)((char*)a0 + 0x304);
        func_002A8578(a0, *(int*)((char*)base + 0x28) + base, *(int*)((char*)base + 0x2C) + base, 0.0f, 0xA, 0, 0);
        *(unsigned char*)((char*)a0 + 0x2F6) = *(unsigned char*)((char*)a0 + 0x2F6) + 1;
        /* fallthrough */
    case 1:
        func_00157C18(a0);
        break;
    case 2:
        *(unsigned char*)((char*)a0 + 0x2F6) = st + 1;
        /* fallthrough */
    case 3:
        if (func_00157C18(a0) != 0) {
            *(unsigned char*)((char*)a0 + 0x2F6) = 0;
        }
        break;
    }
    *(unsigned short*)((char*)a0 + 0x3AC) = *(unsigned short*)((char*)a0 + 0x3AC) | 0x404;
}
