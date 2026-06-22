/* func_0027DD10 — clamp the +0x15B4 float up to at least f12 (a1).  sn-2.95.3-136. */
__attribute__((section(".text.func_0027DD10")))
void func_0027DD10(void *a0, float f12){
    if (*(float *)((char *)a0 + 0x15B4) < f12)
        *(float *)((char *)a0 + 0x15B4) = f12;
}
