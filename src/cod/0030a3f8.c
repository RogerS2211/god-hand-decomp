#include "godhand/vu0.h"

/* func_0030A3F8 — transpose the upper-left 3x3 of the matrix at a1 (MMI
 * pextlw/pextuw/pcpyld/pcpyud shuffle of the three row quadwords), rotate the
 * translation row through VU0, then transform (-translation) by the transposed
 * basis and store the inverse-rotation matrix to a0.  Single inline-asm block;
 * compiler-agnostic. */

__attribute__((section(".text.func_0030A3F8")))
void func_0030A3F8(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set push\n.set noreorder\n"
        "lq $8, 0x0(%1)\n"
        "lq $9, 0x10(%1)\n"
        "lq $10, 0x20(%1)\n"
        "lqc2 $vf4, 0x30(%1)\n"
        "vmove.xyzw $vf5, $vf4\n"
        "vsub.xyz $vf4, $vf4, $vf4\n"
        "vmove.xyzw $vf9, $vf4\n"
        "qmfc2.ni $11, $vf4\n"
        "pextlw $12, $9, $8\n"
        "pextuw $13, $9, $8\n"
        "pextlw $14, $11, $10\n"
        "pextuw $15, $11, $10\n"
        "pcpyld $8, $14, $12\n"
        "pcpyud $9, $12, $14\n"
        "pcpyld $10, $15, $13\n"
        "qmtc2.ni $8, $vf6\n"
        "qmtc2.ni $9, $vf7\n"
        "qmtc2.ni $10, $vf8\n"
        "vmulax.xyz ACC, $vf6, $vf5\n"
        "vmadday.xyz ACC, $vf7, $vf5\n"
        "vmaddz.xyz $vf4, $vf8, $vf5\n"
        "vsub.xyz $vf4, $vf9, $vf4\n"
        "sq $8, 0x0(%0)\n"
        "sq $9, 0x10(%0)\n"
        "sq $10, 0x20(%0)\n"
        "sqc2 $vf4, 0x30(%0)\n"
        ".set pop\n"
        :: "r"(a0), "r"(a1)
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}
