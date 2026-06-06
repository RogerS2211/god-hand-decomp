/* TU: cModel [gfx] - recovered C++ class. */

__attribute__((section(".text.cModel_getMeshPtr")))
int cModel_getMeshPtr(char *a0, int a1) {
    int v1 = a1 - 1;
    int v0 = *(int *)(a0 + 0x25C);
    if (a1 != 0) {
        do {
            v0 = *(int *)(v0 + 0x404);
            if (v0 == 0) {
                return *(int *)(a0 + 0x25C);
            }
            v1 = v1 - 1;
        } while (v1 != -1);
    }
    return v0;
}
