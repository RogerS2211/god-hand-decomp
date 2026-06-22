/* cCoreSave_addKillEmNum — increment the kill counters for the current game
 * level: both the per-level table at (*a0)+0x8C and the running table at
 * (*a0)+0xBAC, indexed by (gameLevel-1).  The split base computation
 * (base = *a0 + OFFSET; p = base + idx*2) reproduces retail's addiu/addu address
 * forming (found via decomp-permuter).  sn-2.95.3-136. */

extern int cCoreSave_getGameLevel(void *);

__attribute__((section(".text.cCoreSave_addKillEmNum")))
void cCoreSave_addKillEmNum(void *a0) {
    int lv, idx;
    char *b1, *b2;
    short *p1, *p2;
    if (!*(void **)a0)
        return;
    lv = cCoreSave_getGameLevel(a0);
    idx = lv - 1;
    if (idx < 0)
        return;
    if (idx >= 5)
        return;
    b1 = (char *)*(void **)a0 + 0x8C;
    p1 = (short *)(b1 + idx * 2);
    *p1 += 1;
    b2 = (char *)*(void **)a0 + 0xBAC;
    p2 = (short *)(b2 + idx * 2);
    *p2 += 1;
}
