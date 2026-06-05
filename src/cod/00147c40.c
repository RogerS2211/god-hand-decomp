/* SN ProDG ee-gcc 2.95.3 matched TU. */

__attribute__((section(".text.func_00147C40")))
void func_00147C40(float *a0, float *a1) {
    a0[12] = a1[0];
    a0[13] = a1[1];
    a0[14] = a1[2];
}

__attribute__((section(".text.func_00158288")))
void func_00158288(void *a0, float f12) {
    if (*(unsigned short*)((char*)a0 + 0x434) & 0x4) {
        f12 = -f12;
    }
    *(float*)((char*)a0 + 0x444) = f12;
}
