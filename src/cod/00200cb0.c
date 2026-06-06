/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern char D_00580D40[];
extern void func_00201228(char *a0, char *a1);
extern void func_00201290(char *a0);

__attribute__((section(".text.PushEntryAtField10000_299868")))
void PushEntryAtField10000_299868(char *a0, long a1, long a2) {
    char *base = a0 + 0x10000;
    *(long*)(*(long**)(base + 0)) = a2;
    *(long*)((char*)*(long**)(base + 0) + 8) = a1;
    *(int*)(base + 0) = *(int*)(base + 0) + 0x10;
    *(int*)(base + 0x10) = *(int*)(base + 0x10) + 1;
}

__attribute__((section(".text.CallThenReturnPlusB0_002B6420_2B61B0")))
int CallThenReturnPlusB0_002B6420_2B61B0(int a0) {
    func_002B6420(a0);
    return a0 + 0xB0;
}
