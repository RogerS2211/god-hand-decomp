/* func_0027F570 — per-frame state machine on the +0x2F6 phase byte:
 * phase 0 fires func_002A8578 with motion params from the +0x304 record and
 * advances to phase 1; both phases then step moveMotion.  sn-2.95.3-136. */

extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern void moveMotion(void *a0);

__attribute__((section(".text.func_0027F570")))
void func_0027F570(void *a0) {
    char *s0 = (char *)a0;
    int v0;
    switch (*(unsigned char *)(s0 + 0x2F6)) {
    case 0:
        v0 = *(int *)(s0 + 0x304);
        func_002A8578(s0, *(int *)(v0 + 0xC) + v0, *(int *)(v0 + 0x10) + v0, 0.0f, 5, 0, 0);
        *(unsigned char *)(s0 + 0x2F6) = *(unsigned char *)(s0 + 0x2F6) + 1;
        /* fallthrough */
    case 1:
        moveMotion(s0);
        break;
    }
}
