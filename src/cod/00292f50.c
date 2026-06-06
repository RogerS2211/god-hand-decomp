/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern float D_00747A14;
extern float func_0030F518(void);

__attribute__((section(".text.GetField_548Scaled_292F50")))
float GetField_548Scaled_292F50(void *a0) {
    return *(float*)((char*)a0 + 0x548) * D_00747A14;
}

__attribute__((section(".text.func_0031D020")))
float func_0031D020(void) {
    float f = func_0030F518() - 0.5f;
    return f + f;
}
