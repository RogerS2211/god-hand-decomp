/* cObjBase_KageInit — store the shadow params (a2 at 0x44C, a1 at 0x450), then
 * initialise the two shadow slots (0x750 apart) via func_0015EAC8.
 * sn-2.95.3-136. */

extern void func_0015EAC8(int);

__attribute__((section(".text.cObjBase_KageInit")))
void cObjBase_KageInit(void *a0, int a1, int a2) {
    int i, off;
    *(int *)((char *)a0 + 0x44C) = a2;
    *(int *)((char *)a0 + 0x450) = a1;
    off = 0;
    for (i = 1; i >= 0; i--) {
        func_0015EAC8(*(int *)((char *)a0 + 0x450) + off);
        off += 0x750;
    }
}
