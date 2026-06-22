#include "godhand/vu0.h"

/* func_001BBAC8 — object constructor: InitFields_1B6E90 base, set vtable at 0x214,
 * zero 0 quadword(s), return the object.  sn-2.95.3-136. */

extern void InitFields_1B6E90(void *);
extern int D_00429190;

__attribute__((section(".text.func_001BBAC8")))
void *func_001BBAC8(void *a0) {
    InitFields_1B6E90(a0);
    *(int **)((char *)a0 + 0x214) = &D_00429190;
    return a0;
}
