__attribute__((section(".text.func_001FD2C0")))
int func_001FD2C0(char *a0, int a1, int a2)
{
    if (*(signed char *)(a0 + 0x49) == 0)
        return 1;
    *(int *)(a0 + 0x34) = 0;
    *(int *)(a0 + 0x30) = a2;
    func_001FD988();
    *(signed char *)(a0 + 0x4A) = 1;
    return 1;
}
