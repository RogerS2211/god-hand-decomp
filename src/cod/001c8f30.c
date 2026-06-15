/* sn-2.95.3-136 matched TU. */

extern void func_0031EC48(float *, int *);
extern int D_007476B0;
extern void func_0014FF00(int a0, int a1, int a2, int a3);
extern void func_002B6400(void *a0);
extern int D_007858B8;
extern unsigned char D_00429E90[];
extern unsigned char D_00785878[];
extern void GetOrInitGlobal785878_1B8058(void);
extern void SetField_0_4_8_31EEA8(void *a0, void *a1, void *a2);
extern int D_007479F4;

__attribute__((section(".text.func_0031ED08")))
unsigned int func_0031ED08(float f12) {
    float fv; int s[4]; int tag; int a0;
    fv = f12;
    func_0031EC48(&fv, s);
    tag = s[0];
    if ((tag ^ 2) == 0) return 0;
    if ((unsigned int)tag < 2) return 0;
    if (s[1] != 0) return 0;
    if ((tag ^ 4) == 0) return 0xFFFFFFFFU;
    a0 = s[2];
    if (a0 < 0) return 0;
    if (a0 >= 0x20) return 0xFFFFFFFFU;
    if (a0 < 0x1F) return (unsigned int)s[3] >> (0x1E - a0);
    return s[3] << (a0 - 0x1E);
}

__attribute__((section(".text.func_0031A600")))
void func_0031A600(char *a0, int a1, int a2, int a3) {
    if (a1 < 0xA) {
        func_0014FF00(*(int *)(a0 + (((D_007476B0 & 1) << 2) + (a1 << 3)) + 0xB00), a2, a3, a3);
    }
}

__attribute__((section(".text.func_002B6230")))
void func_002B6230(char *a0, float *a1) {
    float *v0;
    func_002B6400(a0);
    v0 = (float *)(a0 + 0x30);
    if (v0 != a1) {
        *(float *)(a0 + 0x30) = a1[0];
        v0[1] = a1[1];
        v0[2] = a1[2];
    }
}

__attribute__((section(".text.func_001C8F30")))
void *func_001C8F30(void)
{
	if (D_007858B8 == 0) {
		GetOrInitGlobal785878_1B8058();
		SetField_0_4_8_31EEA8(&D_007858B8, D_00429E90, D_00785878);
	}
	return &D_007858B8;
}

__attribute__((section(".text.func_002ACDC8")))
int func_002ACDC8(int a0, int a1, unsigned int a2)
{
	int e, p, t, r;

	if (a1 != 0x21)
		goto work;
common:
	return *(int *)((char *)D_007479F4 + 0x8) + D_007479F4;
work:
	if (a2 == 0)
		goto common;
	e = a0 + (a1 << 3);
	p = *(int *)((char *)e + 0x4);
	if (p == 0)
		goto common;
	if ((unsigned int)*(int *)p < a2)
		goto common;
	t = *(int *)((char *)(a2 << 2) + p);
	r = t + p;
	if (t == 0)
		r = 0;
	return r;
}
