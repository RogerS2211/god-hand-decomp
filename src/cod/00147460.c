/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void func_002AAC28(void *);
extern char D_0041DCC8[];
extern void ForwardFieldNeg20_002A9680_30F5A0(void);
extern int D_007476B0;
extern int D_00466448[];
extern int D_00747A34;

__attribute__((section(".text.ForwardIfStateActive_147460")))
void ForwardIfStateActive_147460(char *a0) {
    char v1;
    if (*(int *)(a0 + 0xB0) == 0) return;
    v1 = a0[0xB8];
    if (v1 >= 5) return;
    if (v1 <= 0) return;
    func_002AAC28(a0);
}

__attribute__((section(".text.func_001474A0")))
void func_001474A0(void *a0, int a1) {
    *(char **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0();
    }
}

__attribute__((section(".text.Forward155AE8_148F00")))
int Forward155AE8_148F00(int a0, int a1) {
    return func_00155AE8(a0, a1, D_007476B0 & 1);
}

__attribute__((section(".text.func_001492C8")))
int func_001492C8(void) {
    return func_00149378(D_00466448);
}

__attribute__((section(".text.func_001492E8")))
int func_001492E8(int a0) {
    return func_00149400(D_00466448, a0);
}

__attribute__((section(".text.GetActiveState_149310")))
int GetActiveState_149310(void) {
    if (D_00747A34 & 0x40000) {
        return 0;
    }
    return func_00149488(D_00466448);
}
