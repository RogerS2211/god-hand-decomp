/* EffEventDataRelease — if the effect manager (D_007419A0) flag at 0x41C is set,
 * clear it and release the event data (group 6) via espSys_effDataRelease.
 * sn-2.95.3-136. */

extern void espSys_effDataRelease(void *, int);
extern char D_007419A0;

__attribute__((section(".text.EffEventDataRelease")))
void EffEventDataRelease(void) {
    char *p = &D_007419A0;
    if (*(unsigned char *)(p + 0x41C) == 1) {
        *(signed char *)(p + 0x41C) = 0;
        espSys_effDataRelease(p, 6);
    }
}
