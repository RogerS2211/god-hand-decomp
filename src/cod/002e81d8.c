#include "godhand/vu0.h"

/* func_002E81D8 — object constructor (no null guard): InitObject base, set the
 * vtable pointer at 0xF0, return the object.  sn-2.95.3-136. */

extern void *InitObject_2FBCC8(void *);
extern int D_0044E6D8;

__attribute__((section(".text.func_002E81D8")))
void *func_002E81D8(void *a0) {
    InitObject_2FBCC8(a0);
    *(int **)((char *)a0 + 0xF0) = &D_0044E6D8;
    return a0;
}
