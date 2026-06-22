/* func_00292018 — null-checked conditional field write (sn-2.95.3-136 branch-likely). */

__attribute__((section(".text.func_00292018")))
void func_00292018(void *a0, int a1) { if (*(int *)((char *)a0 + 1296) < a1) *(int *)((char *)a0 + 1296) = a1; }
