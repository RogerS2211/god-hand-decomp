extern char D_003C532F;

__attribute__((section(".text.func_00201AD0")))
void func_00201AD0(char *a0)
{
    a0[0] = 0;
    a0[1] = 0;
}

__attribute__((section(".text.func_00208260")))
void func_00208260(void)
{
}

__attribute__((section(".text.func_002478B8")))
void func_002478B8(unsigned char *a0) {
    int v = 0x99;
    a0[0x2F4] = 0;
    a0[0x2F5] = v;
    a0[0x2F6] = 2;
    a0[0x2F7] = 0;
}

__attribute__((section(".text.func_002609E0")))
void func_002609E0(char *a0, int a1, int a2, int a3, int t0, short t1) {
    *(int*)((char*)a0+0x1874) = a1;
    *(int*)((char*)a0+0x1870) = a2;
    *(int*)((char*)a0+0x1878) = a3;
    *(int*)((char*)a0+0x187C) = t0;
    *(short*)((char*)a0+0x1880) = t1;
}

__attribute__((section(".text.func_002609F8")))
void func_002609F8(char *a0, int a1, int a2, int a3, int t0, short t1) {
    *(int*)((char*)a0+0x1888) = a1;
    *(int*)((char*)a0+0x1884) = a2;
    *(int*)((char*)a0+0x188C) = a3;
    *(int*)((char*)a0+0x1890) = t0;
    *(short*)((char*)a0+0x1894) = t1;
}

__attribute__((section(".text.func_00138528")))
void func_00138528(void *a0) {
    char *p = (char *)a0;
    *(int *)(p + 0x274) = 0;
    *(int *)(p + 0x268) = 0;
    *(int *)(p + 0x270) = 0;
    *(int *)(p + 0x26C) = 0;
    *(char *)(p + 0x278) = 0;
    *(int *)(p + 0x260) = 0;
    *(int *)(p + 0x254) = 0;
    *(int *)(p + 0x25C) = 0;
    *(int *)(p + 0x258) = 0;
    *(char *)(p + 0x264) = 0;
}

__attribute__((section(".text.func_001614D0")))
void func_001614D0(char *a0) {
    *(char *)(a0 + 0x58) = 0;
    *(char *)(a0 + 0x59) = 0;
    *(int *)(a0 + 0x50) = 0;
    *(char *)(a0 + 0x64) = 0;
    *(char *)(a0 + 0x5A) = 0;
    *(char *)(a0 + 0x5B) = 0;
    *(char *)(a0 + 0x5C) = 0;
    *(int *)(a0 + 0x60) = -1;
    *(char *)(a0 + 0x5D) = 0;
}

__attribute__((section(".text.func_001C7E08")))
int func_001C7E08(void *a0) {
    int v1 = *(int *)((char *)a0 + 0x5B8) & ~0x40;
    *(char *)((char *)a0 + 0x2F4) = 0;
    *(char *)((char *)a0 + 0x2F5) = 0;
    *(char *)((char *)a0 + 0x2F6) = 0;
    *(char *)((char *)a0 + 0x2F7) = 0;
    *(int *)((char *)a0 + 0x5B8) = v1;
    return 1;
}

__attribute__((section(".text.func_001EE9A0")))
void func_001EE9A0(int *a0)
{
    int v1 = *a0;
    if (v1 != 0) {
        *(char *)((char *)v1 + 0x2F4) = 2;
        *a0 = 0;
    }
    *(char *)((char *)a0 + 0x4) = 0;
    *(int *)((char *)a0 + 0x2C) = 0;
    *(int *)((char *)a0 + 0x30) = 0;
}

__attribute__((section(".text.func_001FAD58")))
void func_001FAD58(int **a0, unsigned char a1) {
    if (*a0) {
        *((unsigned char *)*a0 + 0x154) = a1;
        if ((unsigned char)*((unsigned char *)*a0 + 0x154) >= 0xE) {
            *((unsigned char *)*a0 + 0x154) = 0xD;
        }
    }
}

__attribute__((section(".text.func_001FAD88")))
void func_001FAD88(int **a0, unsigned char a1) {
    if (*a0) {
        *((unsigned char *)*a0 + 0x154) = a1 + *((unsigned char *)*a0 + 0x154);
        if ((unsigned char)*((unsigned char *)*a0 + 0x154) >= 0xE) {
            *((unsigned char *)*a0 + 0x154) = 0xD;
        }
    }
}

__attribute__((section(".text.func_001FADC0")))
void func_001FADC0(int **a0, unsigned char a1) {
    if (*a0) {
        *((unsigned char *)*a0 + 0x155) = a1;
        if ((unsigned char)*((unsigned char *)*a0 + 0x155) >= 0x6) {
            *((unsigned char *)*a0 + 0x155) = 0x5;
        }
    }
}

__attribute__((section(".text.func_001FADF0")))
void func_001FADF0(int **a0, unsigned char a1) {
    if (*a0) {
        *((unsigned char *)*a0 + 0x155) = a1 + *((unsigned char *)*a0 + 0x155);
        if ((unsigned char)*((unsigned char *)*a0 + 0x155) >= 0x6) {
            *((unsigned char *)*a0 + 0x155) = 0x5;
        }
    }
}

__attribute__((section(".text.func_001FBD28")))
void func_001FBD28(unsigned char **a0, int a1) {
    unsigned char *p;
    unsigned char *q;
    int s;
    a1 = a1 & 0xFF;
    p = *a0;
    if (p != 0) {
        s = a1 + p[0x8A];
        p[0x8A] = s;
        q = *a0;
        if (q[0x8A] >= 7) {
            q[0x8A] = 6;
        }
    }
}

__attribute__((section(".text.func_001FC0D8")))
void func_001FC0D8(unsigned char **a0, unsigned int a1) {
    unsigned char *p;
    p = a0[0];
    a1 = a1 & 0xFF;
    if (p == 0) {
        return;
    }
    p[0xAF] = p[0xAE];
    a0[0][0xAE] = (unsigned char)a1;
}

__attribute__((section(".text.Forward322BD8_322AD0")))
int Forward322BD8_322AD0(int a0, int a1, int a2, int a3) {
    return func_00322BD8(a0, a1, a2, a3, ((unsigned int)&D_003C532F) & -0x40, 0x800);
}

__attribute__((section(".text.Forward322C18_322B60")))
int Forward322C18_322B60(int a0, int a1, int a2, int a3) {
    return func_00322C18(a0, a1, a2, a3, ((unsigned int)&D_003C532F) & -0x40, 0x800);
}

__attribute__((section(".text.Forward323050_323038")))
void Forward323050_323038(void) { func_00323050(); }

__attribute__((section(".text.Forward33E6A8_324880")))
void Forward33E6A8_324880(void) { func_0033E6A8(); }

__attribute__((section(".text.func_00324898")))
void func_00324898(void) { func_0033E6B0(); }

__attribute__((section(".text.func_0033D578")))
void func_0033D578(short *a0, int a1, int a2, int a3) {
    func_0033D4D8(a0, a0 + a1, a3);
}

__attribute__((section(".text.Forward33B658_33E678")))
int Forward33B658_33E678(int a0, int a1, int a2, int a3) {
    return Forward33B568_33B658(a0, a1, a2, a3);
}

__attribute__((section(".text.func_0033E690")))
int func_0033E690(int a0, int a1, int a2, int a3) {
    return Forward33B5C8_33B670(a0, a1, a2, a3);
}

__attribute__((section(".text.Forward3B0640_33F3D0")))
int Forward3B0640_33F3D0(int a0, int a1, int a2, int a3) {
    return func_003B0640(a0, a0 + a1 - 1, a2, a3);
}

__attribute__((section(".text.Forward33B658_3403C8")))
int Forward33B658_3403C8(int a0, int a1, int a2, int a3) {
    return Forward33B568_33B658(a0, a1, a2, a3);
}

__attribute__((section(".text.func_003403E0")))
int func_003403E0(int a0, int a1, int a2, int a3) {
    return Forward33B5C8_33B670(a0, a1, a2, a3);
}

__attribute__((section(".text.func_003406B0")))
int func_003406B0(int a0, int a1, int a2, int a3) {
    return func_003A52F0(a0, 0, 0x2C, a3);
}

__attribute__((section(".text.Forward33B790_340AE8")))
int Forward33B790_340AE8(int a0, int a1, int a2, int a3) {
    return func_0033B790(a0, a1, a2, a3);
}

/* writes both the func_002609E0 and func_002609F8 field blocks. */
__attribute__((section(".text.func_002609A8")))
void func_002609A8(char *a0, int a1, int a2, int a3, int t0, short t1) {
    *(int*)((char*)a0+0x1874) = a1;
    *(int*)((char*)a0+0x1870) = a2;
    *(int*)((char*)a0+0x1878) = a3;
    *(int*)((char*)a0+0x187C) = t0;
    *(short*)((char*)a0+0x1880) = t1;
    *(int*)((char*)a0+0x1888) = a1;
    *(int*)((char*)a0+0x1884) = a2;
    *(int*)((char*)a0+0x188C) = a3;
    *(int*)((char*)a0+0x1890) = t0;
    *(short*)((char*)a0+0x1894) = t1;
}
