/* func_001FBEB8 — zeroes the kill counter (0x96) in the save block
 * at a0->0x0 when present. */

__attribute__((section(".text.func_001FBEB8")))
void func_001FBEB8(void *a0) {
    short *p = *(short **)a0;
    if (p) *(short *)((char *)p + 0x96) = 0;
}
