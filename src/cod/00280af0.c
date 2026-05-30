extern volatile int D_003C814C;
extern int D_003C80C8;
extern int SleepThread(void);
extern volatile int D_003C80FC;
extern int Obj33C8_GetShort_24(int a0);
extern int Obj33C8_GetField_28(int a0);
extern int Obj33C8_GetField_30(int a0);
extern int Obj33C8_GetField_34(int a0);
extern int Obj33C8_GetByte_D(int a0);
extern int Obj3270_Tramp_0033D040_7728(void);

__attribute__((section(".text.func_00280AF0")))
void func_00280AF0(void) {}

__attribute__((section(".text.func_00280B58")))
void func_00280B58(void) {}

__attribute__((section(".text.func_00282D68")))
void func_00282D68(void) {}

__attribute__((section(".text.func_00282E48")))
void func_00282E48(void) {}

__attribute__((section(".text.func_00282E50")))
void func_00282E50(void) {}

__attribute__((section(".text.func_00282EB8")))
void func_00282EB8(void) {}

__attribute__((section(".text.func_00283170")))
void func_00283170(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 0;
    a0[0x2F6] = 0;
    a0[0x2F7] = 0;
}

__attribute__((section(".text.func_00283188")))
void func_00283188(char *a0, char a1) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 1;
    a0[0x2F6] = 0;
    a0[0x2F7] = a1;
}

__attribute__((section(".text.func_002831B0")))
void func_002831B0(char *a0, char a1) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 2;
    a0[0x2F6] = 0;
    a0[0x2F7] = a1;
}

__attribute__((section(".text.func_00283240")))
void func_00283240(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 4;
    a0[0x2F6] = 0;
    a0[0x2F7] = 0;
}

__attribute__((section(".text.func_00283258")))
void func_00283258(char *a0) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 5;
    a0[0x2F6] = 0;
    a0[0x2F7] = 0;
}

__attribute__((section(".text.func_00283270")))
void func_00283270(char *a0, char a1) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 7;
    a0[0x2F6] = 0;
    a0[0x2F7] = a1;
}

__attribute__((section(".text.func_00283288")))
void func_00283288(char *a0, char a1) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 8;
    a0[0x2F6] = 0;
    a0[0x2F7] = a1;
}

__attribute__((section(".text.func_00283360")))
void func_00283360(char *a0, char a1) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 0xB;
    a0[0x2F6] = 0;
    a0[0x2F7] = a1;
}

__attribute__((section(".text.func_002833C0")))
void func_002833C0(char *a0, char a1) {
    a0[0x2F4] = 0;
    a0[0x2F5] = 0xA;
    a0[0x2F6] = 0;
    a0[0x2F7] = a1;
}

__attribute__((section(".text.func_003248D8")))
int func_003248D8(int a0, int a1) { return func_0033F130(a1); }

__attribute__((section(".text.func_00324C78")))
int func_00324C78(int a0) { return func_00335A18(a0); }

__attribute__((section(".text.func_00324E70")))
int func_00324E70(void) { return func_00324D88(D_003C814C, D_003C80C8); }

__attribute__((section(".text.func_003252E0")))
int func_003252E0(void) { return SleepThread(); }

__attribute__((section(".text.func_00325C60")))
int func_00325C60(int a0) { return func_0033B658(a0); }

__attribute__((section(".text.func_00325C78")))
int func_00325C78(int a0) { return func_0033B670(a0); }

__attribute__((section(".text.func_00325DC0")))
int func_00325DC0(int a0) { return func_00325C98(a0); }

__attribute__((section(".text.func_00325DD8")))
int func_00325DD8(int a0) { return func_0033F690(a0); }

__attribute__((section(".text.func_00325EF8")))
int func_00325EF8(void) {
  D_003C80FC = 1;
  return func_003252E0();
}

__attribute__((section(".text.func_00327800")))
int func_00327800(char *a0) { return Obj33C8_GetShort_24(*(int*)(a0 + 4)); }

__attribute__((section(".text.func_00327818")))
int func_00327818(char *a0) { return Obj33C8_GetField_28(*(int*)(a0 + 4)); }

__attribute__((section(".text.func_00327860")))
int func_00327860(char *a0) { return Obj33C8_GetField_30(*(int*)(a0 + 4)); }

__attribute__((section(".text.func_00327878")))
int func_00327878(char *a0) { return Obj33C8_GetField_34(*(int*)(a0 + 4)); }

__attribute__((section(".text.func_00327950")))
int func_00327950(char *a0) { return Obj33C8_GetByte_D(*(int*)(a0 + 4)); }

__attribute__((section(".text.func_00327970")))
int func_00327970(int *a0) { return func_0033CFB8(a0[1]); }

__attribute__((section(".text.func_00327988")))
int func_00327988(int *a0) { return func_0033CFF8(a0[1]); }

__attribute__((section(".text.func_00328C58")))
int func_00328C58(void) { return func_00330C88(); }

__attribute__((section(".text.func_0032B4C8")))
int func_0032B4C8(int *a0) { return func_00326800(a0[1]); }

__attribute__((section(".text.func_0032BB20")))
int func_0032BB20(void) { return Obj3270_Tramp_0033D040_7728(); }

__attribute__((section(".text.func_0032BD90")))
int func_0032BD90(int a0, int a1) { return func_0032BC98(a0, a1, 0, 0xFFFFF); }

__attribute__((section(".text.func_0032DA08")))
int func_0032DA08(int a0, int a1, int a2) { return func_0032D868(a0, a1, a2, 0, 0xFFFFF); }

__attribute__((section(".text.func_0032ED48")))
int func_0032ED48(int *a0, int a1, int a2) { a0 += a1; return func_0032A9F0(a0[3], a2); }
