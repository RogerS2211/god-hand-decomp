/* func_001FA908 — set the key-card count (field 0x68 of the save
 * record at *a0), clamped to [0, 9].  Re-derefs *a0 each access to reproduce
 * retail's aliasing reloads; sn-2.95.3-136 branch-likely. */

__attribute__((section(".text.func_001FA908")))
void func_001FA908(void *a0, int a1) {
    if (!*(void **)a0)
        return;
    *(int *)((char *)*(void **)a0 + 0x68) = a1;
    if (*(int *)((char *)*(void **)a0 + 0x68) >= 0xA)
        *(int *)((char *)*(void **)a0 + 0x68) = 9;
    if (*(int *)((char *)*(void **)a0 + 0x68) < 0)
        *(int *)((char *)*(void **)a0 + 0x68) = 0;
}
