/* Trivial field setter (store-rotation order). */

__attribute__((section(".text.func_00297F28")))
void func_00297F28(void *a0, int a1, int a2) { *(int *)((char *)a0 + 0x10) = a1; *(int *)((char *)a0 + 0x14) = a2; }
