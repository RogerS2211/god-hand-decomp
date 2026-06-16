/* newlib mprec.c helpers (SN ProDG cc 2.95.3 build 136).
 * lo0bits: count and strip low-order zero bits of *y, returning the count.
 * Byte-matches retail 0x0038F8C0..0x0038F980 (192 B).
 */

__attribute__((section(".text.lo0bits")))
int lo0bits(unsigned int *y) {
    int k;
    unsigned int x = *y;

    if (x & 7) {
        if (x & 1)
            return 0;
        if (x & 2) {
            *y = x >> 1;
            return 1;
        }
        *y = x >> 2;
        return 2;
    }
    k = 0;
    if (!(x & 0xffff)) {
        k = 16;
        x >>= 16;
    }
    if (!(x & 0xff)) {
        k += 8;
        x >>= 8;
    }
    if (!(x & 0xf)) {
        k += 4;
        x >>= 4;
    }
    if (!(x & 0x3)) {
        k += 2;
        x >>= 2;
    }
    if (!(x & 1)) {
        k += 1;
        x >>= 1;
        if (!x)
            return 32;
    }
    *y = x;
    return k;
}
