/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00747A2C;

__attribute__((section(".text.ShiftDownBytesA8_FAC00")))
void ShiftDownBytesA8_FAC00(int *a0) {
    unsigned int i;
    if ((D_00747A2C & 0x80000) == 0) {
        i = 0;
        do {
            int base = *a0 + 0xA8;
            unsigned int j = i + 1;
            unsigned char src = *(unsigned char *)(base + j);
            *(unsigned char *)(base + i) = src;
            i = j;
        } while (i < 5);
        *((unsigned char *)(*a0) + 0xAD) = 0;
    }
}
