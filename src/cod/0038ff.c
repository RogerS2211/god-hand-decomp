/* newlib mprec ulp (TU 0038ff, ee-gcc 2.9-991111-01).  Returns the
 * unit-in-the-last-place of x: the gap to the next representable double.
 * Reads word0(x) from the GPR via the 64-bit `ux.q >> 32` (dsra32), then
 * builds the result double directly in $v0 per branch.
 *
 * The deepest (denormal) branch returns through its OWN union `b` rather
 * than reusing `a`: this cc1 reserves one 16-byte stack slot per distinct
 * register-valued aggregate local (reserved-but-unused — no memory ops),
 * so the second union is what makes the frame 0x20 to match retail. */

typedef union { double d; unsigned int L[2]; long long q; } U;

__attribute__((section(".text.ulp")))
double ulp(double x) {
    U ux, a, b;
    int L;
    ux.d = x;
    L = ((int)(ux.q >> 32) & 0x7ff00000) - 0x3400000;
    if (L > 0) { a.L[1] = L; a.L[0] = 0; return a.d; }
    L = -L >> 20;
    if (L < 20) { a.L[1] = 0x80000 >> L; a.L[0] = 0; return a.d; }
    L -= 20;
    b.L[1] = 0; b.L[0] = (L >= 31) ? 1 : (1 << (31 - L));
    return b.d;
}
