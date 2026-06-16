/* newlib mprec multadd (TU 0038f6, ee-gcc 2.9-991111-01).  Pack_32 mul-add:
 * b = b*m + a, growing via Brealloc when the carry overflows _maxwds. */

typedef struct _Bigint {
    struct _Bigint *_next;   /* 0x00 */
    int _k;                  /* 0x04 */
    int _maxwds;             /* 0x08 */
    int _sign;               /* 0x0C */
    int _wds;                /* 0x10 */
    unsigned int _x[1];      /* 0x14 */
} _Bigint;

extern _Bigint *Brealloc(_Bigint *b, int k);

__attribute__((section(".text.multadd")))
_Bigint *multadd(_Bigint *b, int m, int a) {
    int i, wds;
    unsigned int *x;
    unsigned int y, z, carry;

    wds = b->_wds;
    x = b->_x;
    i = 0;
    carry = a;
    do {
        y = (*x & 0xffff) * m + carry;
        z = (*x >> 16) * m + (y >> 16);
        carry = z >> 16;
        *x++ = (z << 16) + (y & 0xffff);
    } while (++i < wds);
    if (carry) {
        if (wds >= b->_maxwds) {
            b = Brealloc(b, b->_k + 1);
        }
        b->_x[wds++] = carry;
        b->_wds = wds;
    }
    return b;
}
