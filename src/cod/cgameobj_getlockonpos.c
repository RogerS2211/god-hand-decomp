/* cGameObj_getLockOnPos — virtual dispatch: call the handler at (*(a0+0x214))->0x84 with
 * a0 advanced by the short offset at +0x80.  The do-while block boundaries +
 * pointer-copy chain are load-bearing for the instruction schedule (recovered
 * via decomp-permuter); a naive form is 3 words off.  sn-2.95.3-136. */

__attribute__((section(".text.cGameObj_getLockOnPos")))
void cGameObj_getLockOnPos(void *a0)
{
    void *new_var3;
    void *vt = *((void **)(((char *)a0) + 0x214));
    void **new_var4;
    void *new_var2;
    char *new_var;
    short ofs = *((short *)(vt + 0x80));
    new_var3 = vt;
    new_var2 = new_var3;
    new_var = (char *)new_var2;
    do { do { ((void (*)(void *))(*(new_var4 = (void **)(new_var + 0x84))))(((char *)a0) + ofs); } while (0); } while (0);
}
