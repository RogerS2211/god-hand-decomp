/* func_001FC518 — if the object pointer at +0x0 is non-null, write a field. */

__attribute__((section(".text.func_001FC518")))
void func_001FC518(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0);
    if (p) *(int *)((char *)p + 2984) = a1;
   
}
