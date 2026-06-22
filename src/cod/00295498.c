/* func_00295498 — look up the set-data entry for id a1 in the
 * D_005E8658 table (func_002BEF60); if found, store the user pointer a2 at its
 * 0x8 field.  sn-2.95.3-136. */

extern void *func_002BEF60(void *, int);
extern int D_005E8658;

__attribute__((section(".text.func_00295498")))
void func_00295498(void *a0, int a1, void *a2) {
    void *v0 = func_002BEF60((void *)&D_005E8658, a1);
    if (v0)
        *(void **)((char *)v0 + 0x8) = a2;
}
