/* Byte-identical to RE4 PS2 (SLUS-21134) 0x00178448 — shared engine code.
 * Virtual dispatch: fetches the object at a0->0x0, calls its vtable[1]
 * (offset 0x4) method with a0, and returns the first word of the result. */

__attribute__((section(".text.func_003217F0")))
int func_003217F0(void *a0) {
    void *vt = *(void **)a0;
    int *(*fn)(void *) = *(int *(**)(void *))((char *)vt + 4);
    return *fn(a0);
}
