/* ee-2.9-991111 matched TU. */

extern int D_00755C08;
extern unsigned char D_00755BF8[];
extern unsigned char D_00755C10[];

__attribute__((section(".text.func_003203B0")))
void *func_003203B0(void) {
    if (D_00755C08 == 0) {
        D_00755C08 = 1;
        func_003A52F0(D_00755BF8, 0, 0x10);
        *(int*)(D_00755BF8 + 0x4) = (int)D_00755C10;
    }
    return D_00755BF8;
}
