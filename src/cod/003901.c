/* newlib mprec d2b (TU 003901, ee-gcc 2.9-991111-01).  Double -> bignum:
 * splits the IEEE-754 fields of d, normalises off the trailing zero bits
 * (lo0bits), and writes the residual exponent/bit-count through *e / *bits.
 * The leading `_Bigint *b` arg lands in $a0 so the incoming double sits in
 * $a1 (EE soft-float ABI) and `b = Brealloc(b, 1)` needs no $a0 setup. */

typedef struct _Bigint {
    struct _Bigint *_next;   /* 0x00 */
    int _k;                  /* 0x04 */
    int _maxwds;             /* 0x08 */
    int _sign;               /* 0x0C */
    int _wds;                /* 0x10 */
    unsigned int _x[1];      /* 0x14 */
} _Bigint;

typedef union { double d; long long L; } U;

extern _Bigint *Brealloc(_Bigint *b, int k);
extern int lo0bits(unsigned int *);   /* trailing-zero count; updates *arg */
extern int hi0bits(unsigned int);

#define Frac_mask 0xfffff
#define Exp_msk1  0x100000
#define Exp_shift 20
#define Bias      0x3ff
#define P         53

__attribute__((section(".text.d2b")))
_Bigint *d2b(_Bigint *b, double d, int *e, int *bits)
{
    int de, k, i;
    unsigned int *x, y, z;
    int d0, d1;
    U ua, ub;

    ua.d = d; ub.d = d;
    d0 = (int)(ua.L >> 32);
    d1 = (int)ub.L;
    b = Brealloc(b, 1);
    x = b->_x;
    z = (unsigned int)d0 & Frac_mask;
    if (de = (int)(((unsigned int)d0 >> Exp_shift) & 0x7ff))
        z |= Exp_msk1;
    if (y = (unsigned int)d1) {
        if (k = lo0bits(&y)) {
            x[0] = y | (z << (32 - k));
            z >>= k;
        } else
            x[0] = y;
        i = b->_wds = (x[1] = z) ? 2 : 1;
    } else {
        k = lo0bits(&z);
        x[0] = z;
        i = b->_wds = 1;
        k += 32;
    }
    if (de) {
        *e = de - Bias - (P - 1) + k;
        *bits = P - k;
    } else {
        *e = de - Bias - (P - 1) + 1 + k;
        *bits = 32 * i - hi0bits(x[i - 1]);
    }
    return b;
}
