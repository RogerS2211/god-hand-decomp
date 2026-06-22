/* func_00289038 — guarded 3-float copy from a1 to a0+0x1590. sn-2.95.3-136. */

__attribute__((section(".text.func_00289038")))
void func_00289038(void *a0, void *a1) {
    float *d = (float *)((char *)a0 + 0x1590);
    if (d != (float *)a1) {
        d[0] = ((float *)a1)[0];
        d[1] = ((float *)a1)[1];
        d[2] = ((float *)a1)[2];
    }
}
