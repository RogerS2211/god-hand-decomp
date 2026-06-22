/* func_001FC618 — if the object pointer at +0x0 is non-null, write a field. */

__attribute__((section(".text.func_001FC618")))
void func_001FC618(void *a0) {
    void *p = *(void **)((char *)a0 + 0);
    if (p) *(int *)((char *)p + 3004) = 0;
   
}
