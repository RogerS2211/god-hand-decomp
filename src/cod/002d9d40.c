/* cWorldTime_setGlobalTime — set the time field. */

__attribute__((section(".text.cWorldTime_setGlobalTime")))
void cWorldTime_setGlobalTime(void *a0, int a1) { *(int *)((char *)a0 + 0) = a1; }
