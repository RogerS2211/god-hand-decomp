/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern char D_00574380[];
extern int D_00426350;
extern void func_001FE278(void *, int);
extern void ResetField214FreeField180_1C2820(void *, int);

__attribute__((section(".text.ResetObjW17aVtableAndFree_19E4D0")))
void ResetObjW17aVtableAndFree_19E4D0(void *a0, int a1) {
    *(int *)((char *)a0 + 0x214) = (int)&D_00426350;
    if (*(int *)((char *)a0 + 0x600) != 0) {
        func_001FE278(D_00574380, *(int *)((char *)a0 + 0x600));
        *(int *)((char *)a0 + 0x600) = 0;
    }
    ResetField214FreeField180_1C2820(a0, a1);
}
