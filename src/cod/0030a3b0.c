/* sceVu0TransposeMatrix — transpose a 4x4 matrix (a1 -> a0) using the EE's
 * 128-bit MMI parallel-extend / parallel-copy ops. A pure SIMD register shuffle,
 * expressed as a single inline-asm block. */

__attribute__((section(".text.sceVu0TransposeMatrix")))
void sceVu0TransposeMatrix(void *a0, void *a1) {
    __asm__ __volatile__(
        ".set push\n.set noreorder\n"
        "lq $8, 0x0(%1)\n"
        "lq $9, 0x10(%1)\n"
        "lq $10, 0x20(%1)\n"
        "lq $11, 0x30(%1)\n"
        "pextlw $12, $9, $8\n"
        "pextuw $13, $9, $8\n"
        "pextlw $14, $11, $10\n"
        "pextuw $15, $11, $10\n"
        "pcpyld $8, $14, $12\n"
        "pcpyud $9, $12, $14\n"
        "pcpyld $10, $15, $13\n"
        "pcpyud $11, $13, $15\n"
        "sq $8, 0x0(%0)\n"
        "sq $9, 0x10(%0)\n"
        "sq $10, 0x20(%0)\n"
        "sq $11, 0x30(%0)\n"
        ".set pop\n"
        : : "r"(a0), "r"(a1)
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}
