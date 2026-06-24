/* TU: cRoomSave - recovered C++ class. */
#include "include_asm.h"

extern unsigned char *func_002BEF08(void *a0, int a1);
extern unsigned int func_002BEDD8(void *a0);

__attribute__((section(".text.cRoomSave_clearEmDeadFlag")))
int cRoomSave_clearEmDeadFlag(void *a0, int a1) {
    int i;
    unsigned char *e;
    for (i = 0; (unsigned int)i < func_002BEDD8(a0); i++) {
        e = func_002BEF08(a0, i);
        if (e != 0 && e[0x13] == a1) {
            e[0x14] = 0;
            return 1;
        }
    }
    return 0;
}
