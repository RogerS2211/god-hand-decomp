#include "godhand/vu0.h"

/* func_001A8348 — InitFields_1B6E90 base, zero field 0x600, set the vtable at
 * 0x214, return the object.  sn-2.95.3-136. */

extern void InitFields_1B6E90(void *);
extern int D_004277B8;

__attribute__((section(".text.func_001A8348")))
void *func_001A8348(void *a0) {
    InitFields_1B6E90(a0);
    *(int *)((char *)a0 + 0x600) = 0;
    *(int **)((char *)a0 + 0x214) = &D_004277B8;
    return a0;
}
