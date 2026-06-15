/* sn-2.95.3-136 matched TU. */

extern int Obj0000_Get_D_0076A7A4_3756F0(int);
extern int cDvd_Check();
extern int D_00583F20;

__attribute__((section(".text.func_002CF258")))
short func_002CF258(int a0, short *obj)
{
    if (Obj0000_Get_D_0076A7A4_3756F0(a0) == 2)
        return obj[0x9];   /* 0x12 */
    return obj[0x8];       /* 0x10 */
}

__attribute__((section(".text.func_002CF298")))
short func_002CF298(short *obj)
{
    if (Obj0000_Get_D_0076A7A4_3756F0((int)obj) == 2)
        return obj[0x17];   /* 0x2E */
    return obj[0x16];       /* 0x2C */
}

__attribute__((section(".text.func_002CFC78")))
int func_002CFC78(int *a0) { return a0[0] == 0; }

__attribute__((section(".text.func_002CFC68")))
int func_002CFC68(int *a0) { return a0[0] == 2; }

__attribute__((section(".text.func_002CFC88")))
int func_002CFC88(int *a0) { return a0[0] == 3; }

__attribute__((section(".text.func_002CFF78")))
int func_002CFF78(int *a0) { return a0[1] == 0; }

__attribute__((section(".text.func_002CFF68")))
int func_002CFF68(int *a0) { return a0[1] == 0xF; }

__attribute__((section(".text.func_002CFC98")))
void func_002CFC98(int *a0) { if (a0[0] != 0) a0[0] = 3; }

__attribute__((section(".text.func_002CFD38")))
int func_002CFD38(int *a0, int a1) { return (~a0[1] & a1) == 0; }

__attribute__((section(".text.func_002CF868")))
int func_002CF868(short *a0) { return func_00375128(a0[0x16]) == 0; }

__attribute__((section(".text.func_002CFE28")))
int func_002CFE28(int *a0) { return func_002CD7C8(a0[3]); }

__attribute__((section(".text.func_002CFE48")))
int func_002CFE48(int *a0) { return func_002CD890(a0[3]); }

__attribute__((section(".text.func_002D0350")))
int func_002D0350(int *a0, int a1) { return a0[1] |= a1; }

__attribute__((section(".text.func_002D03D0")))
int func_002D03D0(int *a0, int a1) { return (~a0[1] & a1) == 0; }

__attribute__((section(".text.func_002D0748")))
int func_002D0748(int *a0, int a1) { return a0[20] |= a1; }

__attribute__((section(".text.func_002D0758")))
int func_002D0758(int *a0, int a1) { return a0[20] &= ~a1; }

__attribute__((section(".text.func_002D0578")))
int func_002D0578(int *a0, int a1) {
    int *p = (int *)a0[0xC];
    if (!p) return 0;
    return p[4] + (a1 << 3);
}

__attribute__((section(".text.func_002D0598")))
int func_002D0598(int *a0, int a1) {
    int *p = (int *)a0[0xC];
    if (!p) return 0;
    return p[5] + (a1 << 4);
}

__attribute__((section(".text.func_002D05B8")))
int func_002D05B8(int *a0, int a1) {
    int *p = (int *)a0[0xC];
    if (!p) return 0;
    return p[7] + (a1 << 1);
}

__attribute__((section(".text.func_002D0728")))
int func_002D0728(int *a0, int a1) { a0[20] = a1; return func_002D0820(a0); }

__attribute__((section(".text.func_002D04F8")))
int func_002D04F8(int *a0) {
    if (!func_002CFF68(a0)) return 0;
    return a0[3];
}

__attribute__((section(".text.func_002CF830")))
int func_002CF830(int *a0) {
    int x = a0[0xE];
    if (x == 0) return 1;
    return cDvd_Check(&D_00583F20, x) == 0;
}

__attribute__((section(".text.func_002D0318")))
int func_002D0318(int *a0) {
    int x = a0[7];
    if (x == 0) return 1;
    return cDvd_Check(&D_00583F20, x) == 0;
}

__attribute__((section(".text.func_002D0780")))
int func_002D0780(int *a0, int a1) { a0[0x16] = a1; return func_002D0728(a0, a1); }

__attribute__((section(".text.func_002D07A8")))
int func_002D07A8(int *a0, int a1) { a0[0x16] |= a1; return func_002D0748(a0, a1); }

__attribute__((section(".text.func_002D07D8")))
int func_002D07D8(int *a0, int a1) { a0[0x16] &= ~a1; return func_002D0758(a0, a1); }

__attribute__((section(".text.func_002D0528")))
int func_002D0528(int *a0, int a1) {
    if (!func_002CFF68(a0)) return 0;
    return a0[4] + (a1 << 5);
}

extern int D_00603A40;

__attribute__((section(".text.func_002CFCB0")))
void func_002CFCB0(int *a0, int a1)
{
    a0[1] |= a1;                                /* 0x4 */
    if (func_002CFD38(a0, 0x7F) == 1) {
        if (func_002CFD38(a0, 0x80) == 0) {
            int *p = (int *)a0[4];              /* 0x10 */
            if (p[8] != (int)p)                 /* 0x20 */
                func_002A9648(a0[2], p, p[8] - (int)p, 0x10);  /* 0x8 */
            func_002CFCB0(a0, 0x80);
        }
        a0[0] = 2;
    }
}

__attribute__((section(".text.func_002CFB60")))
void func_002CFB60(int *a0)
{
    int *p = (int *)a0[4];
    func_00374B70(((short *)a0)[0x16], a0[5], a0[6], a0[7], p[6]);
    func_00375988(((short *)a0)[0x16], a0[5], a0[6], a0[7]);
    func_002CFCB0(a0, 0x40);
}

__attribute__((section(".text.func_002CF888")))
int func_002CF888(int *a0)
{
    int *p;
    if (a0[6] != 0)        /* 0x18 */
        return 0;
    p = (int *)a0[4];      /* 0x10 */
    if (p[8] != (int)p)    /* 0x20 */
        a0[0xC] = func_002D3050(&D_00603A40, p[8], &a0[6], p[9]);  /* 0x30 */
    func_002CFCB0(a0, 0x10);
    return 1;
}

__attribute__((section(".text.func_002CF6F8")))
int func_002CF6F8(int *a0, int a1, int a2)
{
    int buf[16];
    int r;
    func_002CFE68(a0, a1, a2, buf);
    r = func_002CF600(a0, a1, buf);
    if (r == 1)
        a0[0xF] = a2;       /* 0x3C */
    return r;
}

__attribute__((section(".text.func_002D0360")))
void func_002D0360(int *a0)
{
    int *t = (int *)a0[3];   /* 0xC */
    if (*((unsigned char *)t + 0xC) == 0) {
        t[1] += (int)t;
        t = (int *)a0[3];
        if (t[2] != 0) {
            t[2] += (int)t;
            t = (int *)a0[3];
        }
        *((unsigned char *)t + 0xC) = 1;
    }
    a0[4] = ((int *)a0[3])[1];
    func_002D0350(a0, 2);
}

__attribute__((section(".text.func_002D0770")))
int func_002D0770(int *a0) { return a0[20]; }
