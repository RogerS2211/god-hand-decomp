extern int D_0041D8F8[];
extern int D_0041DCC8[];

__attribute__((section(".text.func_00139C58")))
void func_00139C58(int *a0, int a1) {
    *(int **)((char *)a0 + 0x35C) = D_0041D8F8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_0013C168")))
void func_0013C168(int *a0) {
    unsigned char x = *(unsigned char *)((char *)a0 + 0x94);
    if (((x ^ 1) & 1) == 0) {
        func_002AAC28();
    }
}

__attribute__((section(".text.func_0013C198")))
void func_0013C198(int *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_0013C528")))
void func_0013C528(int *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}

__attribute__((section(".text.func_0013C798")))
void func_0013C798(int *a0, int a1) {
    *(int **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        func_0030F5A0();
    }
}
