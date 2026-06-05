__attribute__((section(".text.func_0013C618")))
void func_0013C618(char *a0) {
    *(char*)(a0 + 0x74) = 0;
    *(char*)(a0 + 0x79) = 0;
    *(char*)(a0 + 0x7A) = 0;
    *(char*)(a0 + 0x7B) = 0;
    *(char*)(a0 + 0x7C) = 0;
}

__attribute__((section(".text.func_0013D1D0")))
void func_0013D1D0(char *a0) {
    *(char*)(a0 + 0x93) = 0;
    *(short*)(a0 + 0x90) = 6;
    *(char*)(a0 + 0x92) = 0;
}

__attribute__((section(".text.func_0013D1E8")))
void func_0013D1E8(char *a0) {
    *(char*)(a0 + 0x93) = 0;
    *(short*)(a0 + 0x90) = 6;
    *(char*)(a0 + 0x92) = 0;
}

__attribute__((section(".text.func_0013E7D8")))
void func_0013E7D8(char *a0) {
    *(int*)(a0 + 0x94) = 0;
    *(int*)(a0 + 0x9C) = 0;
}

__attribute__((section(".text.func_00147018")))
void func_00147018(char *a0) {
    unsigned int v = 0xFFFF;
    *(int*)(a0 + 0xB0) = 0;
    *(short*)(a0 + 0xAC) = v;
}

__attribute__((section(".text.func_00147188")))
void func_00147188(char *a0) {
    unsigned int v = 0xFFFF;
    if (*(int*)(a0 + 0xB0)) {
        *(int*)(a0 + 0xB0) = 0;
        *(short*)(a0 + 0xAC) = v;
        *(char*)(a0 + 0xB8) = 0;
    }
}

__attribute__((section(".text.func_0014FF60")))
void func_0014FF60(int a0, int *a1) {
    *(long long*)((char*)a0 + 0x18) = 0;
    *(long long*)((char*)a0 + 0x10) = ((long long)*a1 << 32) | 0x20000000;
}

__attribute__((section(".text.func_00159998")))
void func_00159998(int a0) {
    *(int*)((char*)a0 + 0x4) = 0;
    *(int*)((char*)a0 + 0x8) = 0;
    *(short*)((char*)a0 + 0xC) = 0;
    *(short*)((char*)a0 + 0xE) = 0;
}

__attribute__((section(".text.func_001646B0")))
void func_001646B0(int a0, int a1, int a2, int a3) {
    *(int*)((char*)a0 + 0x0) = a1;
    *(int*)((char*)a0 + 0x4) = a2;
    *(int*)((char*)a0 + 0x8) = a3;
}

__attribute__((section(".text.func_0017AEA0")))
void func_0017AEA0(int a0) {
    *(short*)((char*)a0 + 0x606) = 6;
}

__attribute__((section(".text.func_0017F6B0")))
void func_0017F6B0(int a0) {
    *(char*)((char*)a0 + 0x765) = 0;
    *(char*)((char*)a0 + 0x764) = 0;
}

__attribute__((section(".text.func_001AA500")))
void func_001AA500(void *a0) {
    *(int *)((char *)a0 + 0x9E0) = 8;
}

__attribute__((section(".text.func_001ADAE8")))
void func_001ADAE8(void *a0) {
    *(int *)((char *)a0 + 0x604) = 0;
    *(int *)((char *)a0 + 0x608) = 1;
}

__attribute__((section(".text.func_001B0B08")))
void func_001B0B08(void *a0) {
    *(char *)((char *)a0 + 0x2F4) = 1;
    *(char *)((char *)a0 + 0x2F5) = 0;
    *(char *)((char *)a0 + 0x2F6) = 0;
    *(char *)((char *)a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_001B1620")))
int func_001B1620(void *a0) {
    return *(int *)((char *)a0 + 0x600) != 0;
}

__attribute__((section(".text.func_001B1928")))
void func_001B1928(void *a0, int a1, short a2) {
    *(int *)((char *)a0 + 0x660) = a1;
    *(short *)((char *)a0 + 0x664) = a2;
    *(char *)((char *)a0 + 0x666) = 0;
}

__attribute__((section(".text.func_001B5180")))
void func_001B5180(void *a0, int a1, short a2) {
    *(int *)((char *)a0 + 0x604) = a1;
    *(short *)((char *)a0 + 0x608) = a2;
}

__attribute__((section(".text.func_001B79D0")))
long long func_001B79D0(void *a0) {
    long long v = *(unsigned int *)((char *)a0 + 0x5B0);
    return (v >> 3) & 0x1;
}

__attribute__((section(".text.func_001BD698")))
int func_001BD698(int a0) {
    *(int*)((char*)a0 + 0x5B8) |= 0x8;
    return 1;
}

__attribute__((section(".text.func_001BE830")))
void func_001BE830(int a0) {
    *(char*)((char*)a0 + 0x2F4) = 1;
    *(char*)((char*)a0 + 0x2F5) = 0;
    *(char*)((char*)a0 + 0x2F6) = 0;
    *(char*)((char*)a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_001C20C8")))
void func_001C20C8(char *a0) {
    a0[0x674] = 1;
}

__attribute__((section(".text.func_001C2308")))
void func_001C2308(char *a0) {
    a0[0x2F6] = 6;
}

__attribute__((section(".text.func_001C2318")))
void func_001C2318(char *a0) {
    *(int*)(a0 + 0x630) = 0;
    a0[0x2F6] = 2;
}

__attribute__((section(".text.func_001C2490")))
int func_001C2490(int a0) {
    return *(unsigned char*)((char*)a0 + 0x660) != 0;
}

__attribute__((section(".text.func_001D0C78")))
int func_001D0C78(int a0) {
    *(int*)((char*)a0 + 0x0) = 0;
    *(int*)((char*)a0 + 0x4) = 2;
    return a0;
}

__attribute__((section(".text.func_001FC7F8")))
void func_001FC7F8(int a0) {
    *(int*)((char*)a0 + 0x28) = 0;
    *(short*)((char*)a0 + 0x30) = 0;
    *(int*)((char*)a0 + 0x20) = 0;
    *(int*)((char*)a0 + 0x24) = 0;
}

__attribute__((section(".text.func_001FD528")))
void func_001FD528(void) {}

__attribute__((section(".text.func_001FE6B8")))
int func_001FE6B8(int a0, int a1, int a2) {
    *(int*)((char*)a0 + 0x4) = a2;
    *(int*)((char*)a0 + 0x8) = a1;
    return a0;
}

__attribute__((section(".text.func_001FFD98")))
int func_001FFD98(int a0, unsigned char *a1)
{
    unsigned int v1 = a1[1];
    unsigned short v0 = *(unsigned short *)(a1 + 2);
    return ((unsigned int)v0 + (v1 << 16)) << 4;
}

__attribute__((section(".text.func_001FFE00")))
void func_001FFE00(void)
{
}

extern int D_00760D84;
extern int D_00760D88;
extern int D_00760D8C;

__attribute__((section(".text.func_00342870")))
int func_00342870(int a0, int a1, int a2) {
    return func_003428A0(a0, a1, a2, 1);
}

__attribute__((section(".text.Forward342910_342888")))
int Forward342910_342888(int a0, int a1, int a2, int a3) {
    return Forward348870_342910(a0, a1, a2, a3);
}

__attribute__((section(".text.Forward348870_342910")))
int Forward348870_342910(int a0, int a1, int a2, int a3) {
    return func_00348870(a0 + 0x284, a1, a2, a3);
}

__attribute__((section(".text.Forward324950_342928")))
int Forward324950_342928(int a0, int a1, int a2, int a3) {
    return func_00324950(a0, a1, a2, a3);
}

__attribute__((section(".text.func_00342940")))
int func_00342940(int a0, int a1, int a2, int a3) {
    return func_00324AC8(a0, a1, a2, a3);
}

__attribute__((section(".text.func_00342A70")))
int func_00342A70(int a0, int a1, int a2, int a3) {
    return func_00329EA8(a0, a1, a2, a3);
}

__attribute__((section(".text.Forward35F900_346BF8")))
int Forward35F900_346BF8(void){ return func_0035F900(); }

__attribute__((section(".text.Forward35F970_346C18")))
int Forward35F970_346C18(void){ return func_0035F970(); }

__attribute__((section(".text.func_00346C30")))
int func_00346C30(void){ return func_0035FB88(); }

__attribute__((section(".text.func_003471F0")))
int func_003471F0(int a0, int a1, int a2){ return func_00347218(a0, a1, a2, 0); }

__attribute__((section(".text.Forward33BEC0_3489F0")))
int Forward33BEC0_3489F0(void){ return func_0033BEC0(); }

__attribute__((section(".text.Forward33B938_348A50")))
int Forward33B938_348A50(void){ return func_0033B938(2, D_00760D84); }

__attribute__((section(".text.Forward33B938_348AA8")))
int Forward33B938_348AA8(void){ return func_0033B938(6, D_00760D88); }

__attribute__((section(".text.Forward33B938_348B00")))
int Forward33B938_348B00(int a0, int a1, int a2, int a3) { return func_0033B938(5, D_00760D8C, a2, a3); }

__attribute__((section(".text.Forward3466C0_348B78")))
int Forward3466C0_348B78(int a0, int a1, int a2, int a3) { return func_003466C0(a0, a1, a2, a3); }

__attribute__((section(".text.func_00348B90")))
int func_00348B90(int a0, int a1, int a2, int a3) { return func_003466D8(a0, a1, a2, a3); }

__attribute__((section(".text.func_00348BC8")))
int func_00348BC8(int a0, int a1, int a2, int a3) { return func_0033BF18(a0, a1, a2, a3); }

__attribute__((section(".text.Forward33BBD8_348C78")))
int Forward33BBD8_348C78(int a0, int a1, int a2, int a3) { return func_0033BBD8(6, a1, a2, a3); }

__attribute__((section(".text.func_00348C98")))
int func_00348C98(int a0, int a1, int a2, int a3) { return func_0033B790(a0, a1, a2, a3); }

__attribute__((section(".text.Forward349308_349238")))
int Forward349308_349238(int a0, int a1, int a2, int a3) { return func_00349308(a0, a1, a2, a3); }

__attribute__((section(".text.Forward349480_349468")))
int Forward349480_349468(int a0, int a1, int a2, int a3) {
    return func_00349480(a0, a1, a2, a3);
}

__attribute__((section(".text.Forward349590_349578")))
int Forward349590_349578(int a0, int a1, int a2, int a3) {
    return func_00349590(a0, a1, a2, a3);
}

__attribute__((section(".text.Forward349988_349960")))
int Forward349988_349960(int a0, int a1, int a2, int a3) {
    return func_00349988(a0, a1, a2, 0, 0, *(int*)((char*)a1 + 0xC), *(int*)((char*)a1 + 0x10));
}

__attribute__((section(".text.func_00349AA0")))
int func_00349AA0(int a0, int a1, int a2, int a3) {
    return func_00327D00(a0, 0, a2, a3);
}

__attribute__((section(".text.Forward327D90_349AB8")))
int Forward327D90_349AB8(int a0, int a1, int a2, int a3) {
    return func_00327D90(a0, a1, a2, a3);
}

__attribute__((section(".text.func_00349B48")))
int func_00349B48(int a0, int a1, int a2, int a3) {
    return func_003281C8(a0, a1, a2, a3);
}
