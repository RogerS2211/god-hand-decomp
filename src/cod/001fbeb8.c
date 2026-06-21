/* cCoreSave_clearKillNpcNum — zeroes the kill counter (0x96) in the save block
 * at a0->0x0 when present. */

__attribute__((section(".text.cCoreSave_clearKillNpcNum")))
void cCoreSave_clearKillNpcNum(void *a0) {
    short *p = *(short **)a0;
    if (p) *(short *)((char *)p + 0x96) = 0;
}
