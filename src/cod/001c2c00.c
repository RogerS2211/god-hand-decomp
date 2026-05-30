extern void func_002CBA48(void *a, int b, int c, void *d, int e, int f, int g, int h);
extern char D_005FEE00[];
extern void func_002D6910(void *p, int x, int y, int z);
extern void func_002D6948(void *p);

__attribute__((section(".text.func_001C2C00")))
void func_001C2C00(void *a0)
{

    int s = *(short *)((char *)a0 + 0x5F4);
    if (s >= 0) {
        func_002CBA48((void *)D_005FEE00, 2, s, a0, 0, 0, 0, 0);
    }
}

__attribute__((section(".text.func_001C2D60")))
void func_001C2D60(void *a0)
{

    int s = *(short *)((char *)a0 + 0x5F6);
    if (s >= 0) {
        func_002CBA48((void *)D_005FEE00, 2, s, a0, 0, 0, 0, 0);
    }
}

__attribute__((section(".text.func_001D57A0")))
void func_001D57A0(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x5B4, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x5B4);
    }
}

__attribute__((section(".text.func_001D5848")))
void func_001D5848(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x4BC, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x4BC);
    }
}

__attribute__((section(".text.func_001D58F0")))
void func_001D58F0(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x6AC, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x6AC);
    }
}

__attribute__((section(".text.func_001D5998")))
void func_001D5998(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x105C, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x105C);
    }
}

__attribute__((section(".text.func_001D5A40")))
void func_001D5A40(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x3C4, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x3C4);
    }
}

__attribute__((section(".text.func_001D5AE8")))
void func_001D5AE8(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x2CC, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x2CC);
    }
}

__attribute__((section(".text.func_001D5B90")))
void func_001D5B90(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x820, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x820);
    }
}

__attribute__((section(".text.func_001DDB10")))
void func_001DDB10(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x1D4, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x1D4);
    }
}

__attribute__((section(".text.func_001DDBB8")))
void func_001DDBB8(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x348, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x348);
    }
}

__attribute__((section(".text.func_001DDC60")))
void func_001DDC60(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x4BC, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x4BC);
    }
}

__attribute__((section(".text.func_001DDD08")))
void func_001DDD08(void *a0, int a1, int a2)
{
    if (a1) {
        int b;
        int x = (((((((b & ~0xFF) | 0x60) & ~0xFF00) | 0x6000) & ~0xFF0000) | 0x600000) & ~0xFF000000) | 0x50000000;
        int y = (((((((a2 & ~0xFF) | 0xA0) & ~0xFF00) | 0xA000) & ~0xFF0000) | 0xA00000) & ~0xFF000000) | 0x80000000;
        func_002D6910((char *)a0 + 0x630, x, y, 3);
    } else {
        func_002D6948((char *)a0 + 0x630);
    }
}
