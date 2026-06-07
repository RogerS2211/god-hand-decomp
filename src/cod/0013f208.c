/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void cIDBase_trans(void *);
extern int D_0041DCC8[];
extern void ForwardFieldNeg20_002A9680_30F5A0(void);

__attribute__((section(".text.func_0013F208")))
void func_0013F208(void *a0) {
    if (*(int *)((char *)a0 + 0x9C) != 0xFFFF) cIDBase_trans(a0);
}

__attribute__((section(".text.func_001434D0")))
void func_001434D0(void *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0();
    }
}

__attribute__((section(".text.func_00143AF0")))
void func_00143AF0(void *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0();
    }
}
