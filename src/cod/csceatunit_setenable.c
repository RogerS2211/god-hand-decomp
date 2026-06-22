/* cSceAtUnit_SetEnable — set the enable bit (0x1 at 0x34); if the unit type
 * (0x35) is 9, notify func_002C0E20.  sn-2.95.3-136. */

extern void func_002C0E20(void *);

__attribute__((section(".text.cSceAtUnit_SetEnable")))
void cSceAtUnit_SetEnable(void *a0) {
    *(signed char *)((char *)a0 + 0x34) |= 1;
    if (*(unsigned char *)((char *)a0 + 0x35) == 9)
        func_002C0E20(a0);
}
