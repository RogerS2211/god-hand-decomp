/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern unsigned int D_00747A84;
extern void VecRotVec(void *a0, void *a1, void *a2, int a3);
extern void func_001F7DA0(float *p);
extern void SetNodeListFlag_134608(void *a0, int a1);
extern float D_007479FC;
extern float func_002DA038(int a0, float f12, float f13);
extern float func_001F7D48(float f12);

#include "godhand/vu0.h"




__attribute__((section(".text.AddScaledXfmVecToField_F0_14F928")))
void AddScaledXfmVecToField_F0_14F928(char *a0, float f12) {
    float v[4];
    if (!(D_00747A84 & 0x20000000)) {
        VU0_SQC2_VF0(v, 0);
        v[0] = *(float*)(a0 + 0x330) * *(float*)(a0 + 0x110) * f12;
        v[1] = *(float*)(a0 + 0x334) * *(float*)(a0 + 0x114) * f12;
        v[2] = *(float*)(a0 + 0x338) * *(float*)(a0 + 0x118) * f12;
        VecRotVec(v, v, a0 + 0x100, 0);
        *(float*)(*(int*)(a0 + 0xF0) + 0) += v[0];
        *(float*)(*(int*)(a0 + 0xF0) + 4) += v[1];
        *(float*)(*(int*)(a0 + 0xF0) + 8) += v[2];
    }
}

__attribute__((section(".text.AddScaledVecToField_100_14F9F0")))
void AddScaledVecToField_100_14F9F0(char *a0, float f12) {
    if (!(D_00747A84 & 0x20000000)) {
        *(float*)(a0 + 0x100) += *(float*)(a0 + 0x360) * f12;
        *(float*)(a0 + 0x104) += *(float*)(a0 + 0x364) * f12;
        *(float*)(a0 + 0x108) += *(float*)(a0 + 0x368) * f12;
        func_001F7DA0((float*)(a0 + 0x100));
    }
}

__attribute__((section(".text.Forward_001346C8_00134608_1351D8")))
void Forward_001346C8_00134608_1351D8(int a0, int a1, int a2) {
    void *v0 = func_001346C8(a0, a1);
    if (v0 != 0) {
        SetNodeListFlag_134608(v0, a2);
    }
}

__attribute__((section(".text.AddScaledDeltaToField_104_2A7498")))
void AddScaledDeltaToField_104_2A7498(int a0, float f12) {
    int s0 = a0;
    float r = func_002DA038(*(int*)(s0 + 0xF0), *(float*)(s0 + 0x104), f12 * D_007479FC);
    *(float*)(s0 + 0x104) = func_001F7D48(*(float*)(s0 + 0x104) + r);
}
