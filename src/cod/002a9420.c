/* cGameObj_setRot — copies 3 rotation floats from a1 to a0+0x100 unless a1
 * already points there. Compiled with sn-2.95.3-136 (cygnus schedules the
 * stores differently). */

__attribute__((section(".text.cGameObj_setRot")))
void cGameObj_setRot(void *a0, void *a1) {
    float *d = (float *)((char *)a0 + 0x100);
    if (d != (float *)a1) {
        d[0] = ((float *)a1)[0];
        d[1] = ((float *)a1)[1];
        d[2] = ((float *)a1)[2];
    }
}
