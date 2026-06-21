/* cCoreSave_initAddGold — zeroes the added-gold field (0x24) in the save block
 * at a0->0x0 when present. */

__attribute__((section(".text.cCoreSave_initAddGold")))
void cCoreSave_initAddGold(void *a0) {
    int *p = *(int **)a0;
    if (p) *(int *)((char *)p + 0x24) = 0;
}
