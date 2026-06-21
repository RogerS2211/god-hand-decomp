/* Byte-identical to RE4 PS2 (SLUS-21134) 0x0029EEF0 — shared engine code.
 * mod = a0->0x24 % a0->0x18; stores mod+1 back to 0x24; returns
 * a0->0x14 + (mod << 6). The return value is computed before the store-back so
 * the shift is emitted before the increment, matching retail's scheduling. */

__attribute__((section(".text.func_003B2B90")))
int func_003B2B90(void *a0) {
    int *p = (int *)a0;
    int mod = p[9] % p[6];
    int r = p[5] + (mod << 6);
    p[9] = mod + 1;
    return r;
}
