/* delObj — if a0 is non-null, dispatch its virtual destructor: the handler at
 * (*(a0+0x214))->0xC, called with a0 advanced by the short offset at +0x8 and
 * mode 3.  sn-2.95.3-136. */

__attribute__((section(".text.delObj")))
void delObj(void *a0) {
    void *vt;
    short ofs;
    if (!a0)
        return;
    vt = *(void **)((char *)a0 + 0x214);
    ofs = *(short *)((char *)vt + 0x8);
    ((void (*)(void *, int)) * (void **)((char *)vt + 0xC))((char *)a0 + ofs, 3);
}
