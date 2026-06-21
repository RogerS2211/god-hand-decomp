#include "godhand/vu0.h"

/* func_0030A508 — copy three quadwords (0x0,0x10,0x20) from a1 to a0 via MMI
 * lq/sq, and store a0.0x30 = a1.0x30 + a2 (vadd.xyz). */

__attribute__((section(".text.func_0030A508")))
void func_0030A508(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set push\n.set noreorder\n"
        "lqc2 $vf4, 0x0(%2)\n"
        "lqc2 $vf5, 0x30(%1)\n"
        "lq $7, 0x0(%1)\n"
        "lq $8, 0x10(%1)\n"
        "lq $9, 0x20(%1)\n"
        "vadd.xyz $vf5, $vf5, $vf4\n"
        "sq $7, 0x0(%0)\n"
        "sq $8, 0x10(%0)\n"
        "sq $9, 0x20(%0)\n"
        "sqc2 $vf5, 0x30(%0)\n"
        ".set pop\n"
        :: "r"(a0), "r"(a1), "r"(a2) : "$7", "$8", "$9", "memory");
}
