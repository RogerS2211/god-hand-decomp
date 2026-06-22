#include "godhand/vu0.h"

/* func_002FFA68 — guarded InitObject: r = a0; if r, r = InitObject_2FBCC8(a0);
 * return r (the merge form matches retail's single-branch v0=a0/beqz/call/
 * return v0 shape — an early-return splits into two branches).  sn-2.95.3-136. */

extern void *InitObject_2FBCC8(void *);

__attribute__((section(".text.func_002FFA68")))
void *func_002FFA68(void *a0) {
    void *r = a0;
    if (r)
        r = InitObject_2FBCC8(a0);
    return r;
}
