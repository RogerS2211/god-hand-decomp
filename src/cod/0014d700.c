extern unsigned char D_004292F0[];
extern unsigned char D_00574380[];

__attribute__((section(".text.func_0014D700")))
void func_0014D700(char *a0, int a1, int a2) {
    char *node;
    node = func_0014B6F8(a0, 0);
    while (node != 0) {
        func_00155D98(node, a1, a2);
        node = *(char **)(node + 0x404);
    }
}

__attribute__((section(".text.func_0014D768")))
void func_0014D768(char *a0, int a1, int a2) {
    char *node;
    node = func_0014B6F8(a0, 0);
    while (node != 0) {
        func_00155D60(node, a1, a2);
        node = *(char **)(node + 0x404);
    }
}

__attribute__((section(".text.func_001BBF00")))
void func_001BBF00(int a0, int a1)
{
    int v1;
    *(int *)(a0 + 0x214) = (int)D_004292F0;
    v1 = *(int *)(a0 + 0x600);
    if (v1 != 0) {
        func_001FE278(D_00574380, v1);
        *(int *)(a0 + 0x600) = 0;
    }
    func_001BD3F0(a0);
    func_001B6F38(a0, a1);
}

__attribute__((section(".text.func_001F4C40")))
void func_001F4C40(int a0, unsigned short a1, int a2, int a3)
{
    unsigned int s0 = a1;
    int off;
    if (s0 < 7) {
        off = s0 * 0x7C + 0xC00;
        func_002D6548(a0 + off, a2);
        func_001F4778(a0, (int)(s0 + 0x18), a3);
    }
}

__attribute__((section(".text.func_001F5210")))
void func_001F5210(int a0, unsigned short a1, int a2, int a3)
{
    unsigned int s0 = a1;
    int off;
    if (s0 < 7) {
        off = s0 * 0x7C + 0x2058;
        func_002D6548(a0 + off, a2);
        func_001F4778(a0, (int)(s0 + 0x42), a3);
    }
}

__attribute__((section(".text.func_001FF9C0")))
int func_001FF9C0(int a0, int a1, int *a2)
{
    int s0;
    if (a2 != 0) {
        *a2 = 0;
    }
    s0 = func_001FFA68(a0);
    if (s0 == 0) {
        return -1;
    }
    if (a2 != 0) {
        *a2 = func_001FFD98(a0, s0);
    }
    return *(int *)(s0 + 8);
}
