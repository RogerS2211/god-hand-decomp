#include "godhand/vu0.h"

/* func_0017EE40 — object constructor: InitFields_1B6E90 base, set vtable at 0x214,
 * zero 0 quadword(s), return the object.  sn-2.95.3-136. */

extern void InitFields_1B6E90(void *);
extern int D_00422308;

__attribute__((section(".text.func_0017EE40")))
void *func_0017EE40(void *a0) {
    InitFields_1B6E90(a0);
    *(int **)((char *)a0 + 0x214) = &D_00422308;
    return a0;
}
