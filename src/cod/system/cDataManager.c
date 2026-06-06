/* TU: cDataManager [system] - recovered C++ class. */

__attribute__((section(".text.cDataManager_seeDataAddress")))
int cDataManager_seeDataAddress(void *a0) {
    int r = func_001FEE00(a0);
    if (r >= 0)
        return *(int*)(*(int*)((char*)a0+8) + r*0x5C + 0x10);
    return 0;
}

__attribute__((section(".text.cDataManager_clear")))
void cDataManager_clear(unsigned char *a0) {
    int i = *(int *)(a0 + 0x4);
    i--;
    while (i != -1) {
        func_001FF448(*(unsigned char **)(a0 + 0x8) + i * 0x5C);
        i--;
    }
}
