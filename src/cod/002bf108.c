/* func_002BF108 — returns a pointer into the free-room table: for slot
 * a1<0x10, into the block at a0->0x0 (offset 0x1610 + a1*4); otherwise into a0
 * itself (offset 0x1618 + a1*4). Compiled with ee-2.9-991111. */

__attribute__((section(".text.func_002BF108")))
void *func_002BF108(void *a0, int a1) {
    if ((unsigned)a1 < 0x10) return *(char **)a0 + ((a1 << 2) + 0x1610);
    return (char *)a0 + ((a1 << 2) + 0x1618);
}
