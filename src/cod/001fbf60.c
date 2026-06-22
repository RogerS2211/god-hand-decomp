/* cCoreSave_initContinueNum — zeroes the continue counter (0x12) in the save
 * block at a0->0x0 when present. */

__attribute__((section(".text.cCoreSave_initContinueNum")))
void cCoreSave_initContinueNum(void *a0) {
    short *p = *(short **)a0;
    if (p) *(short *)((char *)p + 0x12) = 0;
}
