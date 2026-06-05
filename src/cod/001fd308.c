/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern unsigned int D_00747B10;

__attribute__((section(".text.func_0031CEF8")))
int func_0031CEF8(void)
{
    unsigned int v0 = (unsigned short)D_00747B10 * 5;
    v0 = ((v0 & 0xFF) << 8) + ((v0 & 0xFF00) >> 8);
    D_00747B10 = v0;
    return (unsigned char)D_00747B10;
}

__attribute__((section(".text.func_001FD308")))
void func_001FD308(char *a0, float *a1)
{
    float *v0 = (float *)(a0 + 0x10);
    if (v0 != a1) {
        v0[0] = a1[0];
        v0[1] = a1[1];
        v0[2] = a1[2];
    }
}
