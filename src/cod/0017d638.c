extern char D_00421F20[];
extern char D_00428778[];
extern char D_00429420[];
extern char D_00429EC8[];

__attribute__((section(".text.func_0017D638")))
void func_0017D638(int a0, int a1) {
    *(int *)((char *)a0 + 0x214) = (int)D_00421F20;
    func_0017DF88(a0);
    SetField214PtrThenInit_1B6F38(a0, a1);
}

__attribute__((section(".text.func_0017E1E8")))
int func_0017E1E8(int a0) {
    func_001B6FB8(a0);
    *(int *)((char *)a0 + 0x250) = *(int *)((char *)a0 + 0x250) | 0x10000;
    *(char *)((char *)a0 + 0x600) = 0;
    *(int *)((char *)a0 + 0x5B8) = *(int *)((char *)a0 + 0x5B8) | 0x8;
    return 1;
}

__attribute__((section(".text.func_001B3A70")))
void func_001B3A70(int a0, int a1) {
    *(int *)((char *)a0 + 0x214) = (int)D_00428778;
    func_001B55A0(a0);
    SetField214PtrThenInit_1B6F38(a0, a1);
}

__attribute__((section(".text.func_001BD650")))
void func_001BD650(int a0, int a1) {
    *(int *)((char *)a0 + 0x214) = (int)D_00429420;
    func_001BDBB8(a0);
    SetField214PtrThenInit_1B6F38(a0, a1);
}

__attribute__((section(".text.func_001C8F80")))
int func_001C8F80(int a0) {
    int v0 = a0;
    func_001B6E90(a0);
    *(int *)((char *)a0 + 0x214) = (int)D_00429EC8;
    *(int *)((char *)a0 + 0x600) = 5;
    *(int *)((char *)a0 + 0x604) = 0xE;
    *(int *)((char *)a0 + 0x608) = 0;
    return v0;
}
