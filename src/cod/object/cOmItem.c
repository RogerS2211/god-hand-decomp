/* TU: cOmItem [object] - recovered C++ class. */

__attribute__((section(".text.cOmItem_setGetRangeLong")))
void cOmItem_setGetRangeLong(void *a0, int a1) {
    if (a1 == 1) {
        *(unsigned char *)((char *)a0 + 0x676) = *(unsigned char *)((char *)a0 + 0x676) | 0x4;
    } else {
        *(unsigned char *)((char *)a0 + 0x676) = *(unsigned char *)((char *)a0 + 0x676) & 0xFB;
    }
}

__attribute__((section(".text.cOmItem_setScrCheck")))
void cOmItem_setScrCheck(void *a0, int a1) {
    if (a1 == 1) {
        *(unsigned char *)((char *)a0 + 0x676) = *(unsigned char *)((char *)a0 + 0x676) | 0x1;
    } else {
        *(unsigned char *)((char *)a0 + 0x676) = *(unsigned char *)((char *)a0 + 0x676) & 0xFE;
    }
}

__attribute__((section(".text.cOmItem_setFixPos")))
void cOmItem_setFixPos(void *a0) {
    int *vt = *(int **)((char *)a0 + 0x214);
    short off = *(short *)((char *)vt + 0x70);
    void (*fp)(void *) = *(void (**)(void *))((char *)vt + 0x74);
    fp((char *)a0 + off);
    *(unsigned char *)((char *)a0 + 0x676) =
        *(unsigned char *)((char *)a0 + 0x676) | 2;
}
