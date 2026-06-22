/* cScenario_taskExec_2C3890 — run the scenario task manager at a0+0x1C, then
 * post-process its result via func_002C3968(scenario, result), returning the
 * result.  The do-while(0) block boundary pins the s0/s1 allocation to retail
 * (found via decomp-permuter).  sn-2.95.3-136. */

extern void *cTaskManager_execute(void *);
extern void func_002C3968(void *, void *);

__attribute__((section(".text.cScenario_taskExec_2C3890")))
void *cScenario_taskExec_2C3890(void *a0) {
    void *v0 = cTaskManager_execute((char *)a0 + 0x1C);
    do {
        func_002C3968(a0, v0);
        return v0;
    } while (0);
}
