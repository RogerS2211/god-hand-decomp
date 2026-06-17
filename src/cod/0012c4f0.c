/* ee-2.9-991111 matched TU. */

__attribute__((section(".text.func_0012C4F0")))
int func_0012C4F0(void *a0) {
    unsigned long long m = *(unsigned long long *)((char *)a0 + 0x2F0) & 0xFFFF00000000ULL;
    int r;
    if (m == 0x60100000000ULL) return 1;
    r = 1;
    if (m != 0x50100000000ULL) r = 0;
    return r;
}
