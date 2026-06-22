/* Byte-identical to RE4 PS2 (SLUS-21134) 0x00178590 — LEB128 varint decode.
 * Compiled with the SN toolchain (sn-2.95.3-136). Reads a base-128 varint from
 * a0 into *a1 and returns the pointer past the last byte consumed. */

__attribute__((section(".text.func_00321938")))
void *func_00321938(unsigned char *a0, int *a1) {
    int sh = 0, r;
    unsigned char b;
    b = *a0;
    a0++;
    r = b & 0x7F;
    while (b & 0x80) {
        b = *a0;
        a0++;
        sh += 7;
        r = r | ((b & 0x7F) << sh);
    }
    *a1 = r;
    return a0;
}
