__attribute__((section(".text.func_001EE768")))
int func_001EE768(int a0) {
    *(int*)((char*)a0 + 0x30) = 0;
    *(int*)((char*)a0 + 0x0) = 0;
    return a0;
}

__attribute__((section(".text.func_001F6CE0")))
int func_001F6CE0(int a0) {
    *(int*)((char*)a0 + 0x0) = 0;
    return a0;
}

__attribute__((section(".text.func_001F8A40")))
int func_001F8A40(int a0) {
    *(int*)((char*)a0 + 0x0) = 0;
    *(int*)((char*)a0 + 0x4) = 0;
    *(int*)((char*)a0 + 0x8) = 0;
    *(int*)((char*)a0 + 0xC) = 0;
    *(int*)((char*)a0 + 0x10) = 0;
    *(int*)((char*)a0 + 0x14) = 0;
    return a0;
}

__attribute__((section(".text.func_001F9FF0")))
int func_001F9FF0(int a0) {
    int v0 = *(int*)((char*)a0 + 0x0);
    if (v0 == 0) {
        return 0;
    }
    return v0 + 0x180;
}

__attribute__((section(".text.func_001FA638")))
void func_001FA638(int *a0, short a1)
{
    int p = *a0;
    if (p != 0) *(short*)(p + 0x1C) = a1;
}

__attribute__((section(".text.func_001FA838")))
int func_001FA838(int *a0, int a1)
{
    char *p = (char*)*a0;
    if (p == 0) return 0;
    return *(int*)(p + (a1 << 2) + 0x28);
}

__attribute__((section(".text.func_001FAD38")))
unsigned char func_001FAD38(int *a0, int a1)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(unsigned char*)(p + a1 + 0x134);
}
