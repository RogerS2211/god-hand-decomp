/* Byte-identical to RE4 PS2 (SLUS-21134) 0x002B2720 — strrchr.
 * Compiled with the SN toolchain (sn-2.95.3-136). Returns the last occurrence
 * of (char)a1 in a0, or the terminator if a1 is 0, else NULL. */

__attribute__((section(".text.func_003A93A8")))
char *func_003A93A8(char *a0, int a1) {
    char c = (char)a1;
    char *result = 0;
    while (*a0) {
        if (*a0 == c) result = a0;
        a0++;
    }
    return (*a0 == c) ? a0 : result;
}
