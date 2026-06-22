/* Byte-identical to RE4 PS2 (SLUS-21134) 0x002DAB40 — shared engine code.
 * Fills a 0x20-byte struct with -1. Retail stores 0x1C first, 0x18 last (in the
 * jr delay slot); writing 0x1C LAST in source lets the ee-gcc scheduler rotate
 * it to the front, matching retail exactly. */

__attribute__((section(".text.func_00369130")))
void func_00369130(void *a0) {
    int v = -1;
    *(int *)((char *)a0 + 0x0) = v;
    *(int *)((char *)a0 + 0x4) = v;
    *(int *)((char *)a0 + 0x8) = v;
    *(int *)((char *)a0 + 0xC) = v;
    *(int *)((char *)a0 + 0x10) = v;
    *(int *)((char *)a0 + 0x14) = v;
    *(int *)((char *)a0 + 0x18) = v;
    *(int *)((char *)a0 + 0x1C) = v;
}
