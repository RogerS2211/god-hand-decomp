/* func_002B3020 — returns 0 (symbolic decoder). */

__attribute__((section(".text.func_002B3020")))
int func_002B3020(void *a0) { *(int *)((char *)a0 + 20) = (*(int *)((char *)a0 + 20) | 0x4000); return 0; }
