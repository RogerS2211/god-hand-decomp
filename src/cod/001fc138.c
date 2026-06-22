/* func_001FC138 — if the object pointer at +0x0 is non-null, write a field. */

__attribute__((section(".text.func_001FC138")))
void func_001FC138(void *a0) {
    void *p = *(void **)((char *)a0 + 0);
    if (p) *(signed char *)((char *)p + 343) = 0;
   
}
