/* TU: cOmb3 [object] - recovered C++ class. */

__attribute__((section(".text.cOmb3_SetPointTbl")))
void cOmb3_SetPointTbl(void *a0, int a1, short a2) {
    *(int *)((char *)a0 + 0x604) = a1;
    *(short *)((char *)a0 + 0x608) = a2;
}
