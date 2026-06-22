/* func_001FC5E8 — if the object pointer at +0x0 is non-null, write a field. */

__attribute__((section(".text.func_001FC5E8")))
void func_001FC5E8(void *a0) {
    void *p = *(void **)((char *)a0 + 0);
    if (p) *(short *)((char *)p + 3000) = 0;
   
}
