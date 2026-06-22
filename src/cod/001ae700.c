/* func_001AE700 — 3-bucket threshold on the +0x614 float: 0 (<=200), 1 (<=320), 2.  sn-2.95.3-136. */
__attribute__((section(".text.func_001AE700")))
int func_001AE700(void *a0){
    float f = *(float *)((char *)a0 + 0x614);
    int v0 = 0;
    if (200.0f < f) v0 = 1;
    if (320.0f < f) v0 = 2;
    return v0;
}
