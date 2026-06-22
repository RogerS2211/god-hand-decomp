/* cCollisionShape_setOffsetPos — copy the offset vector a1 into the shape's
 * offset field (0x50) unless they already alias, then recompute the shape
 * (func_002BB2D8).  sn-2.95.3-136. */

extern void func_002BB2D8(void *);

__attribute__((section(".text.cCollisionShape_setOffsetPos")))
void cCollisionShape_setOffsetPos(void *a0, float *a1) {
    float *dst = (float *)((char *)a0 + 0x50);
    if (dst != a1) {
        dst[0] = a1[0];
        dst[1] = a1[1];
        dst[2] = a1[2];
    }
    func_002BB2D8(a0);
}
