/* cMessDrawFont_setRubyData — stores a1 at 0x8 and a2 at 0x14. */

__attribute__((section(".text.cMessDrawFont_setRubyData")))
void cMessDrawFont_setRubyData(void *a0, int a1, int a2) {
    *(int *)((char *)a0 + 0x8) = a1;
    *(int *)((char *)a0 + 0x14) = a2;
}
