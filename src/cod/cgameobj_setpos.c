/* cGameObj_setPos — copy the position vector a1 into the object's position field
 * (0x490), then mirror it into the model transform (*(a0+0xF0)); both copies are
 * skipped when source and destination already alias.  sn-2.95.3-136. */

__attribute__((section(".text.cGameObj_setPos")))
void cGameObj_setPos(void *a0, float *a1) {
    float *dst = (float *)((char *)a0 + 0x490);
    float *o;
    if (dst != a1) {
        dst[0] = a1[0];
        dst[1] = a1[1];
        dst[2] = a1[2];
    }
    o = *(float **)((char *)a0 + 0xF0);
    if (o != dst) {
        o[0] = dst[0];
        o[1] = dst[1];
        o[2] = dst[2];
    }
}
