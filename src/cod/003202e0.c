/* ee-2.9-991111 matched TU. */

extern void func_00320280(void);
extern void func_003A52F0(void *p, int v, int n);

__attribute__((section(".text.func_003202E0")))
void *func_003202E0(void) {
    char *s0 = (char *)func_003A7C70(0x18);
    if (!s0)
        func_00320280();
    func_003A52F0(s0, 0, 0x18);
    *(char **)(s0 + 4) = s0 + 0x10;
    return s0;
}
