/* cygnus-2.96 matched TU. */

extern void func_00366918(void);

__attribute__((section(".text.func_002B45E8")))
void func_002B45E8(void) {
}

__attribute__((section(".text.func_002C30C0")))
void *func_002C30C0(void *a0) {
    return (char *)a0 + 0x5C;
}

__attribute__((section(".text.func_0032F570")))
int func_0032F570(void *a0) {
    return *(int *)((char *)a0 + 0x1958);
}

__attribute__((section(".text.func_0035AEC8")))
void func_0035AEC8(void) {
    func_00366918();
}

__attribute__((section(".text.func_002AF628")))
void func_002AF628(void *a0, void *a1, void *a2, void *a3) {
    *(void **)((char *)a0 + 0x4) = a1;
    *(void **)((char *)a0 + 0xC) = a2;
    *(void **)((char *)a0 + 0x10) = a3;
}
