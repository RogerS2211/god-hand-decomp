/* cGameObj_getRot — return the rotation field (a0+0x100). */

__attribute__((section(".text.cGameObj_getRot")))
void *cGameObj_getRot(void *a0) { return (char *)a0 + 0x100; }
