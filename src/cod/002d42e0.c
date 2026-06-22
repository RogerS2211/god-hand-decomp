/* func_002D42E0 — null-checked conditional field write (sn-2.95.3-136 branch-likely). */

__attribute__((section(".text.func_002D42E0")))
void func_002D42E0(void *a0) { if (*(int *)((char *)a0 + 0)) *(int *)((char *)a0 + 96) = 1; }
