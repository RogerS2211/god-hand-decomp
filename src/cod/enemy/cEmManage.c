/* TU: cEmManage [enemy] - recovered C++ class. */
extern float D_00747A14;

__attribute__((section(".text.cEmManage_GetSpeedRate")))
float cEmManage_GetSpeedRate(void *a0) {
    return *(float*)((char*)a0 + 0x548) * D_00747A14;
}
