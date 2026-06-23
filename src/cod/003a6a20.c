/* sn-2.95.3-136 matched TU. */

extern int *PTR_DAT_003fa62c;

__attribute__((section(".text.func_003A6A20")))
int func_003A6A20(char *fmt, ...) {
    char *ap = (char *)__builtin_next_arg(fmt) - 0x38;
    int *r = PTR_DAT_003fa62c;
    int stream = *(int *)((char *)r + 0x8);
    *(int **)((char *)stream + 0x54) = r;
    return func_003A9D88(*(int *)((char *)PTR_DAT_003fa62c + 0x8), fmt, ap);
}
