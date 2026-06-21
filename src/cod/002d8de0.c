/* cWorldLight_Gaibu_set_off — writes a flag (0x1E) and clears a counter in a
 * far sub-block (a0+0x10000 base). Compiled with sn-2.95.3-136. */

__attribute__((section(".text.cWorldLight_Gaibu_set_off")))
void cWorldLight_Gaibu_set_off(void *a0) {
    char *p = (char *)a0 + 0x10000;
    *(signed char *)(p + 0x6170) = 0x1E;
    *(int *)(p + 0x6284) = 0;
}
