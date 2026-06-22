/* func_00273EE0 — return (+0x1724 float) <= 0, via early-return on 0<x.  sn-2.95.3-136. */
__attribute__((section(".text.func_00273EE0")))
int func_00273EE0(void *a0){
    if (0.0f < *(float *)((char *)a0 + 0x1724)) return 0;
    return 1;
}
