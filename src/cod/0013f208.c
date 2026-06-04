/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void func_002AAC28(void *);
extern int D_0041DCC8[];
extern void func_0030F5A0(void);

__attribute__((section(".text.func_0013F208")))
void func_0013F208(void *a0) {
    if (*(int *)((char *)a0 + 0x9C) != 0xFFFF) func_002AAC28(a0);
}

__attribute__((section(".text.func_001434D0")))
void func_001434D0(void *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_00143AF0")))
void func_00143AF0(void *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}
