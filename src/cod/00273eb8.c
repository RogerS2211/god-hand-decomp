/* func_00273EB8 — return (+0x1720 float) <= 0, via early-return on 0<x.  sn-2.95.3-136. */
__attribute__((section(".text.func_00273EB8")))
int func_00273EB8(void *a0){
    if (0.0f < *(float *)((char *)a0 + 0x1720)) return 0;
    return 1;
}
