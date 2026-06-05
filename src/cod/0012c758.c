/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern unsigned short D_00747A50;
extern int D_005FEA60;
extern void func_002DBE98(void);
extern unsigned int D_00747A78;
extern void func_00139180(int a0);
extern char D_0041DCC8[];
extern void ForwardFieldNeg20_002A9680_30F5A0(void *a0);

__attribute__((section(".text.func_0012C758")))
int func_0012C758(char *a0) {
    if (D_00747A50 != 0x608) {
        return 0;
    }
    if (*(int*)(a0 + 0x698) != 0) {
        return 0;
    }
    if (*(int*)(a0 + 0x6A0) != 0) {
        return 0;
    }
    if (FindNodeByType_2C2568(&D_005FEA60, *(int*)(a0 + 0xF0), 0) == 1) {
        func_002DBE98();
        return 1;
    }
    return 0;
}

__attribute__((section(".text.func_00139060")))
void func_00139060(int a0)
{
    if ((D_00747A78 & 0x800000) == 0) {
        func_00139180(a0);
    }
}

__attribute__((section(".text.func_0013D338")))
void func_0013D338(void *a0, int a1)
{
    *(char **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0(a0);
    }
}

__attribute__((section(".text.func_0013E300")))
void func_0013E300(void *a0, int a1)
{
    *(char **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0(a0);
    }
}

__attribute__((section(".text.func_0013E750")))
void func_0013E750(void *a0, int a1)
{
    *(char **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0(a0);
    }
}

__attribute__((section(".text.func_0013EC50")))
void func_0013EC50(void *a0, int a1)
{
    *(char **)((char *)a0 + 0x80) = D_0041DCC8;
    if (a1 & 1) {
        ForwardFieldNeg20_002A9680_30F5A0(a0);
    }
}
