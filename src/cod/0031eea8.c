/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern char D_00450FD8[];

__attribute__((section(".text.SetField_0_4_8_31EEA8")))
void SetField_0_4_8_31EEA8(int *a0, int a1, int a2) {
    if (a0 == 0) {
        return;
    }
    *(int*)((char*)a0 + 8) = a2;
    *(int*)((char*)a0 + 0) = a1;
    *(int*)((char*)a0 + 4) = (int)D_00450FD8;
}
