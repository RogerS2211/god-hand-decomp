#include "godhand/vu0.h"

/* func_00137A48 — small initialiser: zero fields 0x0 and 0x30, run
 * func_003A52F0(obj+0x4, 0, 0x2C) (clear a 0x2C-byte sub-region), set the
 * float field at 0x1C to 1.06, return the object.  sn-2.95.3-136. */

extern void func_003A52F0(void *, int, int);

__attribute__((section(".text.func_00137A48")))
void *func_00137A48(void *a0) {
    *(int *)((char *)a0 + 0x0) = 0;
    *(int *)((char *)a0 + 0x30) = 0;
    func_003A52F0((char *)a0 + 0x4, 0, 0x2C);
    *(float *)((char *)a0 + 0x1C) = 1.06f;
    return a0;
}
