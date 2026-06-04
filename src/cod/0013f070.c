/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void func_002AAC28(void);
extern int D_0041DCC8[];
extern void func_0030F5A0(void);
extern void func_002AAA40(void *);

__attribute__((section(".text.func_0013F070")))
void func_0013F070(void)
{
    func_002AAC28();
}

__attribute__((section(".text.func_0013F090")))
void func_0013F090(void *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_0013F1C0")))
void func_0013F1C0(void *a0) {
    if (*(int *)((char *)a0 + 0x9C) != 0xFFFF) {
        *(short *)(*(int *)((char *)a0 + 0x90) + 0x90) = *(unsigned short *)((char *)a0 + 0x9C);
        *(short *)(*(int *)((char *)a0 + 0x94) + 0x90) = *(unsigned short *)((char *)a0 + 0x9C);
    }
    func_002AAA40(a0);
}
