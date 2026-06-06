/* TU: CustomIDWork [id] - recovered C++ class. */

__attribute__((section(".text.CustomIDWork_SetDisp")))
void CustomIDWork_SetDisp(int *a0, int a1) {
    int *p = (int *)a0[1];
    if (p != 0) {
        if ((a1 ^ 1) != 0) {
            *(int *)((char *)p + 0x2C) |= 0x20000000;
        } else {
            *(int *)((char *)p + 0x2C) &= 0xDFFFFFFF;
        }
    }
}

__attribute__((section(".text.CustomIDWork_SetNumber")))
void CustomIDWork_SetNumber(void *a0, int a1) {
    int *v0 = *(int **)((char *)a0 + 0x4);
    if (v0 != 0) {
        *(int *)((char *)v0 + 0x84) = a1;
    }
}
