#include "godhand/vu0.h"

/* func_001ADB88 — InitFields_1B6E90 base, zero field 0x620, set the vtable at
 * 0x214, return the object.  sn-2.95.3-136. */

extern void InitFields_1B6E90(void *);
extern int D_00427F48;

__attribute__((section(".text.func_001ADB88")))
void *func_001ADB88(void *a0) {
    InitFields_1B6E90(a0);
    *(int *)((char *)a0 + 0x620) = 0;
    *(int **)((char *)a0 + 0x214) = &D_00427F48;
    return a0;
}
