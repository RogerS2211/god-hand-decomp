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
