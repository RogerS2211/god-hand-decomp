/* SN ProDG ee-gcc 2.95.3 matched TU. */
/* src/cod/001fa0.c — func_001FA010: score-band classifier (LEAF).
 *
 * Reads *(s16*)((*arg0) + 0x1C) and bisects it against the 5-int threshold
 * table D_003BF160 = {1000, 3000, 4000, 4000, 5000}, returning a band 1..5
 * via ((i<3)?i:4)+1.  Hot: 167 call sites (notably func_0021A538).
 *
 * NON_MATCHING partial.  The default `us` build compiles the
 * `#else INCLUDE_ASM` branch (byte-exact retail carve; full ELF sha256
 * unchanged); the `us-nm` build (-DNON_MATCHING, scripts/score_nm.sh)
 * compiles this clean-C body and scores its fuzzy %.  Exact match owed: the
 * target compiler is sn-2.95.3-136 and 27/28 insns already match (loop body
 * + tail are byte-exact); the residual is an sn prologue v0/v1 register
 * coloring that source restructuring can't force.  Permuter-pending. */
#include "include_asm.h"

extern int D_003BF160[];

#ifdef NON_MATCHING
__attribute__((section(".text.func_001FA010")))
int func_001FA010(void **arg0)
{
    int *p; int new_var3; int i; int r;
    if (*arg0 == 0) return 0;
    p = D_003BF160; i = 0;
    if (*(short *)((char *)*arg0 + 0x1C) >= *p) {
        i = 1;
loop:
        p += 1; i += 1;
        if (i < 5) {
            if (*(short *)((char *)*arg0 + 0x1C) >= *p) goto loop;
        }
    }
    new_var3 = i < 3; r = 4; if (new_var3) r = i;
    return r + 1;
}
#else
INCLUDE_ASM("nonmatching", func_001FA010);
#endif
