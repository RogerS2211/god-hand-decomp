/* cMessDrawFont_setDrawPos — sets draw position. The int field (0x28) is
 * written last in source so the scheduler rotates it to the front, matching
 * retail's store order. */

__attribute__((section(".text.cMessDrawFont_setDrawPos")))
void cMessDrawFont_setDrawPos(void *a0, int a1, float x, float y) {
    *(float *)((char *)a0 + 0x20) = x;
    *(float *)((char *)a0 + 0x24) = y;
    *(int *)((char *)a0 + 0x28) = a1;
}
