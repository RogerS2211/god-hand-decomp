/* func_002FA128 — return whether cut-event data (group 6) is registered
 * for the object at a0+1 in the effect manager D_007419A0.  sn-2.95.3-136. */

extern int func_00306030(void *, int, void *);
extern char D_007419A0;

__attribute__((section(".text.func_002FA128")))
int func_002FA128(void *a0) {
    return func_00306030(&D_007419A0, 6, (char *)a0 + 1) != 0;
}
