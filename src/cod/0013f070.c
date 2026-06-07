/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void cIDBase_trans(void);
extern int D_0041DCC8[];
extern void ForwardFieldNeg20_002A9680_30F5A0(void);
extern void cIDBase_move(void *);

__attribute__((section(".text.Forward2AAC28_13F070")))
void Forward2AAC28_13F070(void)
{
    cIDBase_trans();
}

__attribute__((section(".text.func_0013F090")))
void func_0013F090(void *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0();
    }
}

__attribute__((section(".text.func_0013F1C0")))
void func_0013F1C0(void *a0) {
    if (*(int *)((char *)a0 + 0x9C) != 0xFFFF) {
        *(short *)(*(int *)((char *)a0 + 0x90) + 0x90) = *(unsigned short *)((char *)a0 + 0x9C);
        *(short *)(*(int *)((char *)a0 + 0x94) + 0x90) = *(unsigned short *)((char *)a0 + 0x9C);
    }
    cIDBase_move(a0);
}
