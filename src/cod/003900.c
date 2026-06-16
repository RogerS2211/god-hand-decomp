/* newlib mprec b2d (TU 003900, ee-gcc 2.9-991111-01).  Bignum -> double:
 * takes the top words of the bignum into an IEEE-754 mantissa and reports the
 * shift in *e.  The double is assembled in a GPR as (word0<<32)|word1 — the
 * EE keeps doubles in 64-bit GPRs, hence the dsll32/dsrl32 splits. */

typedef struct _Bigint {
    struct _Bigint *_next;   /* 0x00 */
    int _k;                  /* 0x04 */
    int _maxwds;             /* 0x08 */
    int _sign;               /* 0x0C */
    int _wds;                /* 0x10 */
    unsigned int _x[1];      /* 0x14 */
} _Bigint;

typedef union { double d; unsigned int i[2]; } U;
/* EE is little-endian: i[1] = high word (word0), i[0] = low word (word1) */

extern int hi0bits(unsigned int);

#define Ebits 11
#define Exp_1 0x3ff00000

__attribute__((section(".text.b2d")))
double b2d(_Bigint *a, int *e)
{
    unsigned int *xa, *xa0, w, y, z;
    int k;
    unsigned int d0, d1;
    U d;
    double rv;

    xa0 = a->_x;
    xa = xa0 + a->_wds;
    y = *--xa;
    k = hi0bits(y);
    *e = 32 - k;
    if (k < Ebits) {
        d0 = Exp_1 | (y >> (Ebits - k));
        w = xa > xa0 ? *--xa : 0;
        d1 = (y << (32 - Ebits + k)) | (w >> (Ebits - k));
        goto ret_d;
    }
    z = xa > xa0 ? *--xa : 0;
    if (k -= Ebits) {
        d0 = Exp_1 | (y << k) | (z >> (32 - k));
        y = xa > xa0 ? *--xa : 0;
        d1 = (z << k) | (y >> (32 - k));
    } else {
        d0 = Exp_1 | y;
        d1 = z;
    }
ret_d:
    d.i[1] = d0;
    d.i[0] = d1;
    rv = d.d;
    return rv;
}
