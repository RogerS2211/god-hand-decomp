/* SN ProDG ee-gcc 2.95.3 matched TU. */

__attribute__((section(".text.NoOp_33E6A8")))
void NoOp_33E6A8(void) {}

__attribute__((section(".text.NoOp_33E6B0")))
void NoOp_33E6B0(void) {}

__attribute__((section(".text.MaxField514_292030")))
void MaxField514_292030(int a0, int a1)
{
    if (*(int*)(a0 + 0x514) < a1)
        *(int*)(a0 + 0x514) = a1;
}
