/* func_0026EC60 — if the linked object at +0x17A0 shares our +0x2FE id, is not
 * already in phase +0x2F4, and its +0x54C timer has run out (<= 0), re-arm its
 * phase block to 0x2F5=0x65.  sn-2.95.3-136. */
__attribute__((section(".text.func_0026EC60")))
void func_0026EC60(void *a0){
    char *s0 = (char *)a0;
    char *a1 = *(char **)(s0 + 0x17A0);
    if (a1 == 0) return;
    if (*(unsigned short *)(a1 + 0x2FE) != *(unsigned short *)(s0 + 0x2FE)) return;
    if (*(unsigned char *)(a1 + 0x2F4) != 0) return;
    if (0.0f < *(float *)(a1 + 0x54C)) return;
    *(unsigned char *)(a1 + 0x2F4) = 0;
    *(unsigned char *)(a1 + 0x2F5) = 0x65;
    *(unsigned char *)(a1 + 0x2F6) = 0;
    *(unsigned char *)(a1 + 0x2F7) = 0;
}
