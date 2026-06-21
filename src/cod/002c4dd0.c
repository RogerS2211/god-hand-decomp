/* Trivial field setter (store-rotation order). */

__attribute__((section(".text.func_002C4DD0")))
void func_002C4DD0(void *a0, int a1, int a2) { *(int *)((char *)a0 + 0xf4) = a1; *(int *)((char *)a0 + 0xf8) = a2; }
