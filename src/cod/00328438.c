/* Trivial field setter (store-rotation order). */

__attribute__((section(".text.func_00328438")))
void func_00328438(void *a0, int a1, int a2) { *(int *)((char *)a0 + 0x38) = a1; *(int *)((char *)a0 + 0x3c) = a2; }
