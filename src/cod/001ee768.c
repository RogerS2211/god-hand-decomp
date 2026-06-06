__attribute__((section(".text.ClearFields00And30_1EE768")))
int ClearFields00And30_1EE768(int a0) {
    *(int*)((char*)a0 + 0x30) = 0;
    *(int*)((char*)a0 + 0x0) = 0;
    return a0;
}

__attribute__((section(".text.ClearField00_1F6CE0")))
int ClearField00_1F6CE0(int a0) {
    *(int*)((char*)a0 + 0x0) = 0;
    return a0;
}

__attribute__((section(".text.Clear_Field_00_14_1F8A40")))
int Clear_Field_00_14_1F8A40(int a0) {
    *(int*)((char*)a0 + 0x0) = 0;
    *(int*)((char*)a0 + 0x4) = 0;
    *(int*)((char*)a0 + 0x8) = 0;
    *(int*)((char*)a0 + 0xC) = 0;
    *(int*)((char*)a0 + 0x10) = 0;
    *(int*)((char*)a0 + 0x14) = 0;
    return a0;
}

__attribute__((section(".text.GetSubObjAt180_1F9FF0")))
int GetSubObjAt180_1F9FF0(int a0) {
    int v0 = *(int*)((char*)a0 + 0x0);
    if (v0 == 0) {
        return 0;
    }
    return v0 + 0x180;
}

__attribute__((section(".text.Obj1FA6_Set_Short_1C_1FA638")))
void Obj1FA6_Set_Short_1C_1FA638(int *a0, short a1)
{
    int p = *a0;
    if (p != 0) *(short*)(p + 0x1C) = a1;
}

__attribute__((section(".text.GetArrayElemAt28_1FA838")))
int GetArrayElemAt28_1FA838(int *a0, int a1)
{
    char *p = (char*)*a0;
    if (p == 0) return 0;
    return *(int*)(p + (a1 << 2) + 0x28);
}

__attribute__((section(".text.GetByteAt134ByIndex_1FAD38")))
unsigned char GetByteAt134ByIndex_1FAD38(int *a0, int a1)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(unsigned char*)(p + a1 + 0x134);
}
