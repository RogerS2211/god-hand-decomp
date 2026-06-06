extern int D_0041D930;
extern int D_004283D8;
extern int D_00568280;
extern int D_0044ADD8[];
extern int D_007474A0[];
extern int D_0044BA68;
extern int D_0044CEE8;
extern int D_007419A0;
extern int D_0044FB60;
extern int D_0044E090;
extern int D_0044E820;
extern int D_0044EA10;

__attribute__((section(".text.func_001398D0")))
void *func_001398D0(void *a0) {
    func_001380A8(a0);
    *(int *)((char *)a0 + 0x364) = 0;
    *(int *)((char *)a0 + 0x35C) = (int)&D_0041D930;
    *(int *)((char *)a0 + 0x368) = 0;
    return a0;
}

__attribute__((section(".text.func_00180648")))
void func_00180648(void *a0) {
    if (*(unsigned char *)((char *)a0 + 0xA29)) {
        func_00306168(1, 3, 2);
        *(unsigned char *)((char *)a0 + 0xA29) = 0;
    }
}

__attribute__((section(".text.func_001B1B38")))
void *func_001B1B38(void *a0) {
    InitFields_1B6E90(a0);
    *(int *)((char *)a0 + 0x600) = 0;
    *(int *)((char *)a0 + 0x214) = (int)&D_004283D8;
    *(short *)((char *)a0 + 0x604) = 0;
    return a0;
}

__attribute__((section(".text.func_001BB508")))
void func_001BB508(void *a0) {
    *(char *)((char *)a0 + 0x531) = -1;
    func_00306200(a0, 0, 2);
    func_001B79B0(a0);
}

__attribute__((section(".text.func_001D55D0")))
void func_001D55D0(void *a0, int a1) {
    SetFlagOnEntries7C_1D51B8(a0, 0x21, a1);
    SetFlagOnEntries7C_1D51B8(a0, 0x22, 1);
}

__attribute__((section(".text.func_001D5610")))
void func_001D5610(void *a0, int a1) {
    SetFlagOnEntries7C_1D51B8(a0, 0x7, a1);
    SetFlagOnEntries7C_1D51B8(a0, 0x8, 1);
}

__attribute__((section(".text.func_001D5650")))
void func_001D5650(void *a0, int a1) {
    SetFlagOnEntries7C_1D51B8(a0, 0x5, a1);
    SetFlagOnEntries7C_1D51B8(a0, 0x6, 1);
}

__attribute__((section(".text.func_001E79A8")))
void func_001E79A8(int *a0, int a1) {
    func_003A52F0(a0, 0, 0x54);
    *a0 = a1;
}

__attribute__((section(".text.func_001E8798")))
int func_001E8798(int a0)
{
    InitStructAndSubfields_1E8DA8(a0);
    *(int *)(a0 + 0xC0) = 0;
    *(float *)(a0 + 0xBC) = 0.13425609469413757f;
    return a0;
}

__attribute__((section(".text.func_001F3580")))
int func_001F3580(int a0)
{
    func_003A52F0(a0, 0, 0x54);
    *(int *)(a0 + 0x54) = 0;
    func_001F45D8(a0 + 0x60);
    return a0;
}

__attribute__((section(".text.Tramp_003B4AD8_1F6E98")))
int Tramp_003B4AD8_1F6E98(int a0, int a1)
{
    func_003B4AD8(D_00568280, a0, a1);
    return a1;
}

__attribute__((section(".text.func_00295CA8")))
int func_00295CA8(int a0)
{
    if (FindResolveActor_295978(a0) == 0) {
        return 1;
    }
    return func_0028FB38(*(int *)(a0 + 4));
}

__attribute__((section(".text.func_002A71B0")))
void func_002A71B0(void)
{
    D_007474A0[0x608 / 4] = func_0031CCF0(D_007474A0[0x5AC / 4], D_0044ADD8, 0);
}

__attribute__((section(".text.InitVtableEntry_2B8AE0")))
int InitVtableEntry_2B8AE0(int a0)
{
    func_002BA178(a0, 0x26C, 2);
    *(int *)(a0 + 0x18) = (int)&D_0044BA68;
    return a0;
}

__attribute__((section(".text.func_002BE630")))
unsigned char func_002BE630(int *a0, int a1)
{
	int r;
	*a0 = a1;
	r = func_002BE6A0(a0);
	*(char *)((char *)a0 + 4) = (char)r;
	if (((unsigned int)r & 0xFF) == 0)
		*a0 = 0;
	return *(unsigned char *)((char *)a0 + 4);
}

__attribute__((section(".text.func_002C3280")))
void func_002C3280(char *a0)
{
	char *p = a0 + 0x1C;
	func_002D50E8(p, 0x10, 0x1800, 0x30);
	func_002D51F0(p);
}

__attribute__((section(".text.func_002CA518")))
void func_002CA518(void *a0)
{
	func_002CC150(a0);
	func_002D22F0(a0);
	func_002CB128(a0);
	func_002CB200(a0);
}

__attribute__((section(".text.InitActorVtable_2CC500")))
void *InitActorVtable_2CC500(void *a0)
{
	int r = Obj0000_Set_Field_80_372C68(a0);
	*(int **)((char *)a0 + 0x80) = &D_0044CEE8;
	func_002CC578(a0);
	return a0;
}

__attribute__((section(".text.FreeResourceNode_2D3710")))
void FreeResourceNode_2D3710(int *a0)
{
	int x = *a0;
	if (x != 0)
		Forward345EE0_345EC8(x);
	func_002D40F8(a0);
}

__attribute__((section(".text.func_002FA310")))
void func_002FA310(void)
{
	func_002FB4C0();
	func_00300900();
	func_00305BE0(&D_007419A0);
	func_00305C20(&D_007419A0);
}

__attribute__((section(".text.InitObjectVtable_2FBD98")))
void *InitObjectVtable_2FBD98(void *a0) {
    func_002B5C20(a0, 0, 0);
    *(int **)((char *)a0 + 0xF0) = &D_0044FB60;
    return a0;
}

__attribute__((section(".text.func_002FFA90")))
void *func_002FFA90(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044E090;
    }
    return a0;
}

__attribute__((section(".text.func_002FFC20")))
void *func_002FFC20(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044E820;
    }
    return a0;
}

__attribute__((section(".text.func_002FFC88")))
void *func_002FFC88(void *a0) {
    if (a0) {
        func_002FBCC8(a0);
        *(int **)((char *)a0 + 0xF0) = &D_0044EA10;
    }
    return a0;
}
