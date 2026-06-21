/* cMessDrawFont_setBodyData — stores a1/a2/a3 at 0x4/0xC/0x10. Source order
 * 0x4,0xC,0x10 lets the scheduler emit retail's 0x10,0x4,0xC (0xC in delay). */

__attribute__((section(".text.cMessDrawFont_setBodyData")))
void cMessDrawFont_setBodyData(void *a0, int a1, int a2, int a3) {
    *(int *)((char *)a0 + 0x4) = a1;
    *(int *)((char *)a0 + 0xC) = a2;
    *(int *)((char *)a0 + 0x10) = a3;
}
