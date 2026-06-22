/* cCoreSave_addCasinoTicket — add a1 to the casino-ticket count
 * ((*a0)->0xB94), clamped to [0, 9].  Re-derefs reproduce retail's aliasing
 * reloads; sn-2.95.3-136 branch-likely. */

__attribute__((section(".text.cCoreSave_addCasinoTicket")))
void cCoreSave_addCasinoTicket(void *a0, int a1) {
    if (!*(void **)a0)
        return;
    *(int *)((char *)*(void **)a0 + 0xB94) += a1;
    if (*(int *)((char *)*(void **)a0 + 0xB94) >= 0xA)
        *(int *)((char *)*(void **)a0 + 0xB94) = 9;
    if (*(int *)((char *)*(void **)a0 + 0xB94) < 0)
        *(int *)((char *)*(void **)a0 + 0xB94) = 0;
}
