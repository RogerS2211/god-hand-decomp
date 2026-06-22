/* EffEventDataRegist — if a0 (the event object) is non-null, mark the effect
 * manager (D_007419A0) flag at 0x41C and register the event data for the object
 * (group 6) via espSys_effDataRegist.  sn-2.95.3-136. */

extern int espSys_effDataRegist(void *, int, void *);
extern char D_007419A0;

__attribute__((section(".text.EffEventDataRegist")))
void EffEventDataRegist(void *a0) {
    char *p;
    if (!a0)
        return;
    p = &D_007419A0;
    *(signed char *)(p + 0x41C) = 1;
    espSys_effDataRegist(p, 6, a0);
}
