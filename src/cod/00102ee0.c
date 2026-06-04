/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00785508;
extern void func_00100328(void);
extern void func_0031EEA8(void *a0, void *a1, void *a2);
extern char D_0041B7D0[];
extern char D_007854C8[];
extern void func_001351D8(void *a0, void *a1, int a2);
extern void func_002A8578(void *a0, void *a1, void *a2, float f, int a3, int t0, int t1);
extern char D_00462FC0[];
extern void func_0014F9F0(void *a0, float f);
extern void func_0014F928(void *a0, float f);

__attribute__((section(".text.func_00103880")))
void *func_00103880(void) {
    void *p = (void *)&D_00785508;
    if (D_00785508 == 0) {
        func_00100328();
        func_0031EEA8(p, D_0041B7D0, D_007854C8);
    }
    return p;
}

__attribute__((section(".text.func_00102EE0")))
void func_00102EE0(void *a0) {
    int s1 = func_002DB6B0();
    int g;
    int p0, p1;
    func_001351D8(D_00462FC0, a0, 0);
    *(int *)((char *)a0 + 0x250) |= 2;
    *(float *)((char *)a0 + 0x54C) = 2.0f;
    switch (*(unsigned char *)((char *)a0 + 0x2F6)) {
    case 0:
        g = *(int *)((char *)a0 + 0x304);
        func_002A8578(a0, (void *)(*(int *)((char *)g + 0xC) + g),
                      (void *)(*(int *)((char *)g + 0x10) + g), 0.0f, 0, 0, 0);
        (*(unsigned char *)((char *)a0 + 0x2F6))++;
        /* fallthrough */
    case 1:
        p0 = *(int *)((char *)a0 + 0xF0);
        p1 = *(int *)((char *)s1 + 0xF0);
        if (p0 != p1) {
            *(float *)((char *)p0 + 0) = *(float *)((char *)p1 + 0);
            *(float *)((char *)p0 + 4) = *(float *)((char *)p1 + 4);
            *(float *)((char *)p0 + 8) = *(float *)((char *)p1 + 8);
        }
        {
            char *d = (char *)a0 + 0x100;
            char *s = (char *)s1 + 0x100;
            if (d != s) {
                *(float *)(d + 0) = *(float *)(s + 0);
                *(float *)(d + 4) = *(float *)(s + 4);
                *(float *)(d + 8) = *(float *)(s + 8);
            }
        }
        func_00157C18(a0);
        break;
    }
}

__attribute__((section(".text.func_00102FE8")))
void func_00102FE8(void *a0) {
    int g;
    switch (*(unsigned char *)((char *)a0 + 0x2F6)) {
    case 0:
        g = *(int *)((char *)a0 + 0x304);
        func_002A8578(a0, (void *)(*(int *)((char *)g + 0x54) + g),
                      (void *)(*(int *)((char *)g + 0x58) + g), 0.0f, 0, 0, 0);
        if (func_00306528(0, 0x51, a0, 0, -1, 0xFFFFFFFF)) { }
        (*(unsigned char *)((char *)a0 + 0x2F6))++;
        /* fallthrough */
    case 1:
        if (func_00157C18(a0)) {
            *(unsigned char *)((char *)a0 + 0x2F4) = 0;
            *(unsigned char *)((char *)a0 + 0x2F5) = 0;
            *(unsigned char *)((char *)a0 + 0x2F6) = 0;
            *(unsigned char *)((char *)a0 + 0x2F7) = 0;
        }
        func_0014F9F0(a0, 1.0f);
        func_0014F928(a0, 1.0f);
        break;
    }
}

__attribute__((section(".text.func_00138210")))
void func_00138210(char *a0) {
    int *p;
    void (*fn)();
    p = *(int **)(a0 + 0x35C);
    fn = (void (*)())p[3];
    fn(a0 + *(short *)((char *)p + 8));
}

__attribute__((section(".text.func_00140C58")))
int func_00140C58(char *a0) {
    int v1 = 0;
    a0 += 0x22F4;
    while (1) {
        if (*(int*)a0 == 0) {
            return v1;
        }
        v1++;
        if (v1 >= 0x11) {
            return -1;
        }
        a0 += 0xC;
    }
}
