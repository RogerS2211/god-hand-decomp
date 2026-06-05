/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00747A2C;

__attribute__((section(".text.func_002D6490")))
void func_002D6490(int *a0, int a1) {
    int *p = (int *)a0[1];
    if (p != 0) {
        if ((a1 ^ 1) != 0) {
            *(int *)((char *)p + 0x2C) |= 0x20000000;
        } else {
            *(int *)((char *)p + 0x2C) &= 0xDFFFFFFF;
        }
    }
}

__attribute__((section(".text.func_001FAC00")))
void func_001FAC00(int *a0) {
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
