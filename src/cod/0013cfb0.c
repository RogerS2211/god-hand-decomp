extern int D_0041DCC8[];
extern char D_00464080;

__attribute__((section(".text.func_0013CFB0")))
void func_0013CFB0(int *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_0013D150")))
void func_0013D150(int *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_0013F270")))
void func_0013F270(int a0, int a1) {
    *(int*)((char*)a0 + 0x80) = (int)&D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_00140B58")))
void func_00140B58(int a0, int a1) {
    *(int*)((char*)a0 + 0x80) = (int)&D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_00141AC8")))
void func_00141AC8(int a0, int a1) {
    if (a1 != 0xFFFF) {
        return;
    }
    if (a0 == 0) {
        return;
    }
    func_00141678(&D_00464080);
}

__attribute__((section(".text.func_00141AF8")))
void func_00141AF8(void) {
    func_00141AC8(1, 0xFFFF);
}
