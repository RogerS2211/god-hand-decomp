/* newlib mprec Balloc — bignum allocator (ee-gcc 2.9-991111-01, the older
 * Sony/Cygnus cc1 the PS2 SDK used for its statically-linked newlib; emits
 * 64-bit `sd` callee-saves in 16-byte slots, which neither cygnus-2.96 nor
 * SN 2.95.3-136 reproduces).  Byte-matches retail 0x0038F4E8..0x0038F548.
 *
 * The _Bigint field widths below are chosen to reproduce retail's exact
 * field-zeroing stores (two `sh` + one `sw`); the trailing array begins at
 * the offset retail's allocation size implies (maxwds*4 + 0x14 header).
 */

typedef struct _Bigint {
    struct _Bigint *_next;
    int _k, _maxwds;
    short _sign, _wds;
    unsigned int _x[1];
} _Bigint;

extern void *func_003A7C70(unsigned int);   /* malloc */

__attribute__((section(".text.Balloc")))
_Bigint * Balloc(int k) {
    int x, m;
    _Bigint *rv;
    x = (k > 2) ? k : 3;
    m = 1 << x;
    rv = (_Bigint *) func_003A7C70(sizeof(_Bigint) + m * sizeof(int));
    rv->_k = x;
    rv->_maxwds = m;
    rv->_x[0] = 0;
    rv->_sign = rv->_wds = 0;
    return rv;
}
