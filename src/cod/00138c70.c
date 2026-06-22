#include "godhand/vu0.h"

/* func_00138C70 — set the object's 0x1028 flag to 1, run func_00139090, and
 * publish the object as the current instance in the D_005CAFF0 global.  Return
 * value is unused by callers (void).  sn-2.95.3-136. */

extern void func_00139090(void *);
extern void *D_005CAFF0;

__attribute__((section(".text.func_00138C70")))
void func_00138C70(void *a0) {
    *(int *)((char *)a0 + 0x1028) = 1;
    func_00139090(a0);
    D_005CAFF0 = a0;
}
