/* func_002E13D8 — sets the global font width/height (D_0061B280 +0x8/+0x9) to
 * the byte args, or 8/8 if either is zero. sn-2.95.3-136. Source store order
 * 0x8,0x9 yields retail's 0x9-first / 0x8-in-delay-slot via scheduler rotation. */

extern signed char D_0061B280[];

__attribute__((section(".text.func_002E13D8")))
void func_002E13D8(int a0, int a1) {
    a0 &= 0xFF;
    if (a0 != 0) {
        a1 &= 0xFF;
        if (a1 != 0) {
            D_0061B280[8] = a0;
            D_0061B280[9] = a1;
            return;
        }
    }
    D_0061B280[8] = 8;
    D_0061B280[9] = 8;
}
