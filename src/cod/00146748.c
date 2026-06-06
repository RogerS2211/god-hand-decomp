/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern char D_0041DCC8[];
extern void ForwardFieldNeg20_002A9680_30F5A0(void);
extern void func_002AAC28(void *);

__attribute__((section(".text.SetLinkedObjFlags_1471A8")))
void SetLinkedObjFlags_1471A8(int a0, unsigned short a1) {
    if (*(int *)((char*)a0 + 0xB0)) {
        int *p1;
        int *p2;
        *(short *)((char*)a0 + 0xAC) = a1;
        *(char *)((char*)a0 + 0xB8) = 1;
        p1 = *(int **)((char*)a0 + 0xA4);
        *(int *)((char*)p1 + 0x2C) = *(int *)((char*)p1 + 0x2C) | 0x8000000;
        p2 = *(int **)((char*)a0 + 0xA8);
        *(int *)((char*)p2 + 0x2C) = *(int *)((char*)p2 + 0x2C) | 0x8000000;
    }
}

__attribute__((section(".text.SetListNodeBitByKey_14A398")))
void SetListNodeBitByKey_14A398(int a0, int a1, int a2) {
    int v1 = *(int *)((char*)a0 + 0x25C);
    if (v1 == 0) return;
    do {
        if (a1 == *(unsigned char *)((char*)v1 + 0x40C)) {
            int v0 = *(int *)((char*)v1 + 0x380);
            if (a2 != 0)
                v0 &= 0xFFFFFFFE;
            else
                v0 |= 1;
            *(int *)((char*)v1 + 0x380) = v0;
        }
        v1 = *(int *)((char*)v1 + 0x404);
    } while (v1 != 0);
}

__attribute__((section(".text.func_00146748")))
void func_00146748(void *a0, int a1) {
    *(char **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0();
    }
}

__attribute__((section(".text.func_00146E20")))
void func_00146E20(char *a0) {
    char v1 = a0[0x79];
    if (v1 == 0) return;
    if (v1 == 6) return;
    if (*(unsigned short *)(a0 + 0xF8) == 0) {
        func_002AAC28(a0);
    } else {
        func_002AAC28(a0 + 0xA0);
    }
}

__attribute__((section(".text.func_00146E70")))
void func_00146E70(void *a0, int a1) {
    *(char **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0();
    }
}

__attribute__((section(".text.func_00146F98")))
void func_00146F98(void *a0, int a1) {
    *(char **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0();
    }
}
