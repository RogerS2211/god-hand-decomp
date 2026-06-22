/* espSys_effDataRelease — release effect data (a0, group a1) by forwarding to
 * FindAndForwardEntry_3059A8 with mode 0.  sn-2.95.3-136. */

extern void FindAndForwardEntry_3059A8(void *, int, int);

__attribute__((section(".text.espSys_effDataRelease")))
void espSys_effDataRelease(void *a0, int a1) {
    FindAndForwardEntry_3059A8(a0, a1, 0);
}
