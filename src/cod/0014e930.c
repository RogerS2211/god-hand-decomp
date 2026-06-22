/* func_0014E930 — sets (a1==1) or clears bit 0x8000 of the flags at a0+0x250.
 * Compiled with sn-2.95.3-136. */

__attribute__((section(".text.func_0014E930")))
void func_0014E930(void *a0, int a1) {
    if (a1 == 1) {
        int v = *(int *)((char *)a0 + 0x250);
        *(int *)((char *)a0 + 0x250) = v | 0x8000;
    } else {
        int v = *(int *)((char *)a0 + 0x250);
        *(int *)((char *)a0 + 0x250) = v & 0xFFFF7FFF;
    }
}
