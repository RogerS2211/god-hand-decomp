/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00450FF0;
extern void NoOp_33E6A8(void);
extern void func_0032A720(int a0, int a1, int a2);
extern int NoOp_33E6B0(void);

__attribute__((section(".text.func_0031EEC8")))
void func_0031EEC8(int *a0, int a1)
{
	if (a0) {
		a0[0] = a1;
		a0[1] = (int)&D_00450FF0;
	}
}

__attribute__((section(".text.GetIndexedEntry_2CC4B8")))
int GetIndexedEntry_2CC4B8(char *a0, int a1) { return *(int*)(a0 + 0x3C) + (a1 << 6); }

__attribute__((section(".text.func_0032A6D0")))
int func_0032A6D0(int a0, int a1, int a2)
{
    NoOp_33E6A8();
    func_0032A720(a0, a1, a2);
    return NoOp_33E6B0();
}
