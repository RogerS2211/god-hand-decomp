/* func_002D8DE0 — writes a flag (0x1E) and clears a counter in a
 * far sub-block (a0+0x10000 base). Compiled with sn-2.95.3-136. */

__attribute__((section(".text.func_002D8DE0")))
void func_002D8DE0(void *a0) {
    char *p = (char *)a0 + 0x10000;
    *(signed char *)(p + 0x6170) = 0x1E;
    *(int *)(p + 0x6284) = 0;
}
