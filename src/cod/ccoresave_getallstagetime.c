/* cCoreSave_getAllStageTime — split the total play time ((*a0)->0xBBC, in
 * 1/30s ticks) into hours / minutes / seconds, written through the optional
 * out-pointers a1/a2/a3 (0x1A5E0 ticks/hour, 0x708/min, 0x1E/sec).
 * sn-2.95.3-136. */

__attribute__((section(".text.cCoreSave_getAllStageTime")))
void cCoreSave_getAllStageTime(void *a0, int *a1, int *a2, int *a3) {
    void *p;
    unsigned int t, h, m, s;
    p = *(void **)a0;
    if (!p)
        return;
    t = *(unsigned int *)((char *)p + 0xBBC);
    h = t / 0x1A5E0;
    t = t - h * 0x1A5E0;
    m = t / 0x708;
    t = t - m * 0x708;
    s = t / 0x1E;
    if (a1)
        *a1 = h;
    if (a2)
        *a2 = m;
    if (a3)
        *a3 = s;
}
