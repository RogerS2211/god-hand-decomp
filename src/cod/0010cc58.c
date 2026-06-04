/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern void func_00124E68(void *a0, float f);
extern void func_00123938(void *a0, int a1);
extern float D_003BD48C;

__attribute__((section(".text.func_0010CC58")))
void func_0010CC58(void *a0) {
    char *s0 = (char *)a0;
    int v0;
    int v1;
    switch (*(unsigned char *)(s0 + 0x2F6)) {
    case 0:
        v0 = *(int *)(s0 + 0x304);
        *(short *)(s0 + 0x5E0) = 0;
        *(short *)(s0 + 0x5E2) = 0;
        func_002A8578(s0, *(int *)(v0 + 0x220) + v0, *(int *)(v0 + 0x278) + v0, 0.0f, 3, 0, 0);
        *(int *)(s0 + 0x15B0) = 0x10;
        *(unsigned char *)(s0 + 0x2F6) = *(unsigned char *)(s0 + 0x2F6) + 1;
        /* fallthrough */
    case 1:
        *(float *)(s0 + 0x15F0) = D_003BD48C;
        v1 = *(int *)(s0 + 0x15B0);
        if (v1 != 0) {
            *(int *)(s0 + 0x15B0) = v1 - 1;
            func_00124E68(s0, 0.19634954f);
        }
        if (func_00157C18(s0) != 0) {
            *(unsigned char *)(s0 + 0x2F4) = 0;
            *(unsigned char *)(s0 + 0x2F5) = 0;
            *(unsigned char *)(s0 + 0x2F6) = 0;
            *(unsigned char *)(s0 + 0x2F7) = 0;
        }
        break;
    }
    func_00123938(s0, 1);
}
