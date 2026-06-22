/* cGameObj_setSuspend — when a1==1 set the suspend flags (0x8000 at 0x250,
 * 0x8 at 0x5A0); otherwise clear them.  sn-2.95.3-136. */

__attribute__((section(".text.cGameObj_setSuspend")))
void cGameObj_setSuspend(void *a0, int a1) {
    if (a1 == 1)
        *(int *)((char *)a0 + 0x250) |= 0x8000;
    else
        *(int *)((char *)a0 + 0x250) &= 0xFFFF7FFF;
    if (a1 == 1)
        *(int *)((char *)a0 + 0x5A0) |= 0x8;
    else
        *(int *)((char *)a0 + 0x5A0) &= ~0x8;
}
