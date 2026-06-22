/* Byte-identical to RE4 PS2 (SLUS-21134) 0x002A1FC8 — newlib byte-copy.
 * Compiled with ee-2.9-991111 (the newlib toolchain); cygnus-2.96 fills the
 * loop branch delay slot with the dst increment, whereas newlib leaves it a nop
 * with the dst increment before the branch. */

__attribute__((section(".text.func_003B67E8")))
void *func_003B67E8(void *a0, void *a1, unsigned a2) {
    unsigned char *d = (unsigned char *)a0, *s = (unsigned char *)a1;
    unsigned i = 0;
    if (a2 != 0) {
        do {
            unsigned char b = *s;
            i++;
            s++;
            *d = b;
            d++;
        } while (i < a2);
    }
    return 0;
}
