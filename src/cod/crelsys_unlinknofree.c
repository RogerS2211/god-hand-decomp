/* cRelSys_unlinkNoFree — unlink REL-table entry a1 (stride 8) without freeing
 * it: if its 0x4 status byte is 1, run func_002BE670 on the entry.  The
 * shift-first index `a1*8 + (int)a0` reproduces retail's addu a0,a1,a0 ordering.
 * sn-2.95.3-136. */

extern void func_002BE670(void *);

__attribute__((section(".text.cRelSys_unlinkNoFree")))
void cRelSys_unlinkNoFree(void *a0, int a1) {
    void *p = (void *)(a1 * 8 + (int)a0);
    if (*(unsigned char *)((char *)p + 0x4) == 1)
        func_002BE670(p);
}
