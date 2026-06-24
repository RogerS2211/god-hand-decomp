/* TU: cOmSub [object] - recovered C++ class. */
#include "include_asm.h"

struct cOmSub_move_entry { short off; short pad; int (*fn)(); };
extern struct cOmSub_move_entry D_00429D80[3];

__attribute__((section(".text.cOmSub_move")))
int cOmSub_move(char *a0) {
    struct cOmSub_move_entry tbl[3];
    int idx;
    if (*(int *)(a0 + 0x8) == 0) return 0;
    memcpy(tbl, D_00429D80, 0x18);
    idx = *(unsigned char *)(a0 + 0x2);
    return tbl[idx].fn(a0 + tbl[idx].off);
}

INCLUDE_ASM("nonmatching", cOmSub_initMove1_pos);

INCLUDE_ASM("nonmatching", cOmSub_initMove1_ang);

INCLUDE_ASM("nonmatching", cOmSub_setEndPos);

INCLUDE_ASM("nonmatching", cOmSub_setReverse);
