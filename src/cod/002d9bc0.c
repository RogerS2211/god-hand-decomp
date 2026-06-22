/* cWorldTime_gameInit — zero the time field. */

__attribute__((section(".text.cWorldTime_gameInit")))
void cWorldTime_gameInit(void *a0) { *(int *)((char *)a0 + 0) = 0; }
