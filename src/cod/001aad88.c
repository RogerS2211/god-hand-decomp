/* cOm59_setParent — stores two ints at 0x9A0/0x9A4 then guard-copies two 3-float
 * vectors (parent transforms) to a0+0x9B0 and a0+0x9C0. The second base pointer
 * is scoped late so it materialises after the first copy, matching retail.
 * sn-2.95.3-136. */

__attribute__((section(".text.cOm59_setParent")))
void cOm59_setParent(void *a0, int a1, int a2, void *a3, void *t0) {
    float *d1 = (float *)((char *)a0 + 0x9B0);
    *(int *)((char *)a0 + 0x9A0) = a1;
    *(int *)((char *)a0 + 0x9A4) = a2;
    if (d1 != (float *)a3) {
        d1[0] = ((float *)a3)[0];
        d1[1] = ((float *)a3)[1];
        d1[2] = ((float *)a3)[2];
    }
    {
        float *d2 = (float *)((char *)a0 + 0x9C0);
        if (d2 != (float *)t0) {
            d2[0] = ((float *)t0)[0];
            d2[1] = ((float *)t0)[1];
            d2[2] = ((float *)t0)[2];
        }
    }
}
