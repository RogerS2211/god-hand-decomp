/* RE4 PS2 byte-identical (SLUS-21134 @ 0x0017A2F8). ceil(a0 / 2048). */
__attribute__((section(".text.func_00324858")))
int func_00324858(int a0) { return a0 / 2048 + (a0 % 2048 > 0); }
