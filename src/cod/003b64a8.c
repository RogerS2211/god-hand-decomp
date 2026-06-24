/* ee-2.9-991111 matched TU. */

__attribute__((section(".text.func_003B64A8")))
int *func_003B64A8(int *a0, int *a1, int a2) {
    for (;;) {
        if (*a0 == a2) break;
        if (a0 >= a1) break;
        a0++;
    }
    return a0 < a1 ? a0 : 0;
}
