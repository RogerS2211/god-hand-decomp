/* cCoreSave_getComboMax — returns slot a1's combo-max (0x24-byte records at
 * +0x1D0 off the save block at a0->0x0); 0 if no block or a1>=6. sn-2.95.3-136. */

__attribute__((section(".text.cCoreSave_getComboMax")))
int cCoreSave_getComboMax(void *a0, int a1) {
    char *p = *(char **)a0;
    if (!p) return 0;
    if ((unsigned)a1 >= 6) return 0;
    return *(int *)(p + a1 * 0x24 + 0x1D0);
}
