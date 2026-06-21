/* sn-2.95.3-136 matched TU. */

extern void func_002DB2B0(int a0, int a1);
extern void func_003735E0(void *a0, int a1, float f12, float f13);

__attribute__((section(".text.func_001E3D78")))
void func_001E3D78(void *a0, int a1, int a2) {
    *(short *)((char *)a0 + 0x4A8) = 0;
    if (a2) {
        *(unsigned short *)((char *)a0 + 0x4A8) = 0x8000;
    }
    if (a1) {
        *(unsigned short *)((char *)a0 + 0x4A8) = *(unsigned short *)((char *)a0 + 0x4A8) | 0x4000;
        func_002DB2B0(*(int *)((char *)a0 + 0x430), 1);
    } else {
        func_002DB2B0(*(int *)((char *)a0 + 0x430), 0);
    }
}

__attribute__((section(".text.func_001E6C80")))
void func_001E6C80(void *a0, int a1, int a2) {
    *(short *)((char *)a0 + 0x3E2) = 0;
    if (a2) {
        *(unsigned short *)((char *)a0 + 0x3E2) = 0x8000;
    }
    if (a1) {
        *(unsigned short *)((char *)a0 + 0x3E2) = *(unsigned short *)((char *)a0 + 0x3E2) | 0x4000;
        func_002DB2B0(*(int *)((char *)a0 + 0x3C8), 1);
    } else {
        func_002DB2B0(*(int *)((char *)a0 + 0x3C8), 0);
    }
}

__attribute__((section(".text.func_001E6D48")))
void func_001E6D48(void *a0, int a1, int a2) {
    *(short *)((char *)a0 + 0x3E4) = 0;
    if (a2) {
        *(unsigned short *)((char *)a0 + 0x3E4) = 0x8000;
    }
    if (a1) {
        *(unsigned short *)((char *)a0 + 0x3E4) = *(unsigned short *)((char *)a0 + 0x3E4) | 0x4000;
        func_002DB2B0(*(int *)((char *)a0 + 0x3C8), 1);
    } else {
        func_002DB2B0(*(int *)((char *)a0 + 0x3C8), 0);
    }
}

__attribute__((section(".text.func_001E6E10")))
void func_001E6E10(void *a0, int a1, int a2) {
    *(short *)((char *)a0 + 0x3E6) = 0;
    if (a2) {
        *(unsigned short *)((char *)a0 + 0x3E6) = 0x8000;
    }
    if (a1) {
        *(unsigned short *)((char *)a0 + 0x3E6) = *(unsigned short *)((char *)a0 + 0x3E6) | 0x4000;
        func_002DB2B0(*(int *)((char *)a0 + 0x3C8), 1);
    } else {
        func_002DB2B0(*(int *)((char *)a0 + 0x3C8), 0);
    }
}

__attribute__((section(".text.func_003AE188")))
int func_003AE188(int a0, int a1, ...) {
    return func_003AB158(a0, a1, (char*)__builtin_next_arg(a1) - 0x30);
}

__attribute__((section(".text.func_002CD500")))
void func_002CD500(void *a0, int a1, float f) {
    *(int *)((char *)a0 + 0x98) |= a1;
    *(float *)((char *)a0 + 0xC8) = f;
    func_003735E0(a0, -1, 0.01f, f);
}
