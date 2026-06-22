/* func_001FAC98 — stores a1 to offset 0x84 of the save block at a0->0x0. */

__attribute__((section(".text.func_001FAC98")))
void func_001FAC98(void *a0, int a1) {
    void *p = *(void **)a0;
    if (p) *(int *)((char *)p + 0x84) = a1;
}
