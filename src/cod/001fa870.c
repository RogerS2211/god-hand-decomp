/* func_001FA870 — subtract a1 from the gold counter ((*a0)->0x20), clamp to
 * [0, 0xF423F]; if the infinite-money flag (D_00747A34 & 0x2000000) is set,
 * force it to the cap.  Re-derefs reproduce the aliasing reloads;
 * sn-2.95.3-136 branch-likely. */

extern int D_00747A34;

__attribute__((section(".text.func_001FA870")))
void func_001FA870(void *a0, int a1) {
    if (!*(void **)a0)
        return;
    *(int *)((char *)*(void **)a0 + 0x20) -= a1;
    if (*(int *)((char *)*(void **)a0 + 0x20) > 0xF423F)
        *(int *)((char *)*(void **)a0 + 0x20) = 0xF423F;
    if (*(int *)((char *)*(void **)a0 + 0x20) < 0)
        *(int *)((char *)*(void **)a0 + 0x20) = 0;
    if (D_00747A34 & 0x2000000)
        *(int *)((char *)*(void **)a0 + 0x20) = 0xF423F;
}
