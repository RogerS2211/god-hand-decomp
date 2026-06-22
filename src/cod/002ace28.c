/* sn-2.95.3-136 matched TU. */

extern int (*PTR_FUN_003c490c)(void *);
extern void *D_003C3CF0;
extern int EnsureInitThenForward_2A9538_30EE08(void *, int, void *);

__attribute__((section(".text.func_00320360")))
int func_00320360(void *a0) {
    return PTR_FUN_003c490c(a0) + 8;
}

__attribute__((section(".text.func_002ACE28")))
int func_002ACE28(void *a0, void *a1) {
    return cIDManager_getTexAddr(a0, 1, a1);
}

__attribute__((section(".text.func_0030F550")))
int func_0030F550(void *a0) {
    return EnsureInitThenForward_2A9538_30EE08(a0, 0x10, D_003C3CF0);
}
