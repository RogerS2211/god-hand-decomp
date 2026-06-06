/* TU: cOmBase [object] - recovered C++ class. */

__attribute__((section(".text.cOmBase_setMeshDispFromLayer")))
void cOmBase_setMeshDispFromLayer(void *a0, int a1, int a2) {
    char *v1 = (char *)cModel_getMeshPtr(a0, 0);
    if (v1 != 0) {
        do {
            if (*(unsigned char *)(v1 + 0x40C) == a1) {
                if (a2 == 1) {
                    *(int *)(v1 + 0x380) &= 0xFFFFFFFE;
                } else {
                    *(int *)(v1 + 0x380) |= 1;
                }
            }
            v1 = *(char **)(v1 + 0x404);
        } while (v1 != 0);
    }
}
