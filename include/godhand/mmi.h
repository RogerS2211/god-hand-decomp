/* include/godhand/mmi.h -- EE-core MMI (multimedia / 128-bit integer SIMD)
 * whole-routine intrinsics.
 *
 * # Why these are whole-function macros, not per-op primitives
 *
 * A handful of retail matrix routines are pure 128-bit register shuffles built
 * from the EE's MMI ops (`lq`/`sq`, `pextlw`/`pextuw`, `pcpyld`/`pcpyud`),
 * sometimes interleaved with COP2/VU0 ops in the SAME instruction stream.  ee-
 * gcc 2.x has no C operator and no `__builtin_*` for these ops, and -- unlike
 * the COP2 helpers in `godhand/vu0.h`, where each op is an independent inline-
 * asm statement GCC can schedule -- these routines pass intermediate values
 * between ops through fixed GPRs (`$8`..`$15`) inside ONE asm block with an
 * explicit clobber list.  Splitting them into per-op macros (separate asm
 * blocks) would break that hand-allocated register dataflow and change the
 * emitted bytes, so the faithful representation is one asm block per routine.
 *
 * # Why this header exists (the cheat-scanner exemption)
 *
 * The inline-asm cheat scanner (scripts/checks/inline_asm_staged.py) rejects
 * raw `__asm__` in a `.c` *body* -- that is how a pasted-disassembly fake match
 * is caught.  But these routines have NO C form, so their honest home is a
 * sanctioned intrinsics header, exactly like `godhand/vu0.h`.  This header is
 * therefore on the scanner's `_INTRINSIC_HEADER_ALLOWLIST`; the `.c` files that
 * use it stay a clean macro composition and remain fully scanned.  See
 * DECISIONS.md D-027 (which extends the D-026 reasoning from COP2 to MMI).
 *
 * # The .set noreorder framing
 *
 * Each macro wraps its block in `.set push ; .set noreorder ; ... ; .set pop`,
 * matching retail: it pins instruction order so neither ee-gcc's scheduler nor
 * ee-as's reorder pass can move instructions across the shuffle.  No explicit
 * pipeline nops are added (same empirical finding as the vu0.h load/store
 * class); the macros reproduce retail's exact instruction text, so the built
 * bytes are unchanged (the retail-ELF sha256 gate is the proof).
 *
 * # Scope (lazy-vendor: add on demand, do NOT speculatively populate)
 *
 *   MMI_TRANSPOSE_MATRIX4(dst, src)   -- transpose a 4x4 matrix (src -> dst)
 *   MMI_INVERSE_RT_MATRIX(dst, src)   -- transpose the 3x3 basis + inverse-
 *                                        rotate the translation (src -> dst)
 *   MMI_COPY3Q_VADD(dst, src, add)    -- copy 3 quadwords src->dst and store
 *                                        dst.0x30 = src.0x30 + *add (vadd.xyz)
 */
#ifndef GODHAND_MMI_H
#define GODHAND_MMI_H

/* MMI_TRANSPOSE_MATRIX4(dst, src): full 4x4 matrix transpose via pextlw/pextuw
 * (interleave the rows word-wise) then pcpyld/pcpyud (recombine into columns).
 * src/dst are 0x40-byte matrices; rows at 0x0/0x10/0x20/0x30. */
#define MMI_TRANSPOSE_MATRIX4(dst, src)                                \
    __asm__ __volatile__(                                              \
        ".set push\n.set noreorder\n"                                  \
        "lq $8, 0x0(%1)\n"                                             \
        "lq $9, 0x10(%1)\n"                                            \
        "lq $10, 0x20(%1)\n"                                           \
        "lq $11, 0x30(%1)\n"                                           \
        "pextlw $12, $9, $8\n"                                         \
        "pextuw $13, $9, $8\n"                                         \
        "pextlw $14, $11, $10\n"                                       \
        "pextuw $15, $11, $10\n"                                       \
        "pcpyld $8, $14, $12\n"                                        \
        "pcpyud $9, $12, $14\n"                                        \
        "pcpyld $10, $15, $13\n"                                       \
        "pcpyud $11, $13, $15\n"                                       \
        "sq $8, 0x0(%0)\n"                                             \
        "sq $9, 0x10(%0)\n"                                            \
        "sq $10, 0x20(%0)\n"                                           \
        "sq $11, 0x30(%0)\n"                                           \
        ".set pop\n"                                                   \
        : : "r"(dst), "r"(src)                                         \
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory")

/* MMI_INVERSE_RT_MATRIX(dst, src): build the inverse of a rigid-body (rotation
 * + translation) matrix.  Transpose the upper-left 3x3 basis via the MMI
 * shuffle (the rotation inverse), zero $vf4 to extract a zero quadword, then
 * transform the negated translation by the transposed basis through the VU0
 * mulax/madday/maddz accumulator and store the result. */
#define MMI_INVERSE_RT_MATRIX(dst, src)                                \
    __asm__ __volatile__(                                              \
        ".set push\n.set noreorder\n"                                  \
        "lq $8, 0x0(%1)\n"                                             \
        "lq $9, 0x10(%1)\n"                                            \
        "lq $10, 0x20(%1)\n"                                           \
        "lqc2 $vf4, 0x30(%1)\n"                                        \
        "vmove.xyzw $vf5, $vf4\n"                                      \
        "vsub.xyz $vf4, $vf4, $vf4\n"                                  \
        "vmove.xyzw $vf9, $vf4\n"                                      \
        "qmfc2.ni $11, $vf4\n"                                         \
        "pextlw $12, $9, $8\n"                                         \
        "pextuw $13, $9, $8\n"                                         \
        "pextlw $14, $11, $10\n"                                       \
        "pextuw $15, $11, $10\n"                                       \
        "pcpyld $8, $14, $12\n"                                        \
        "pcpyud $9, $12, $14\n"                                        \
        "pcpyld $10, $15, $13\n"                                       \
        "qmtc2.ni $8, $vf6\n"                                          \
        "qmtc2.ni $9, $vf7\n"                                          \
        "qmtc2.ni $10, $vf8\n"                                         \
        "vmulax.xyz ACC, $vf6, $vf5\n"                                 \
        "vmadday.xyz ACC, $vf7, $vf5\n"                                \
        "vmaddz.xyz $vf4, $vf8, $vf5\n"                                \
        "vsub.xyz $vf4, $vf9, $vf4\n"                                  \
        "sq $8, 0x0(%0)\n"                                             \
        "sq $9, 0x10(%0)\n"                                            \
        "sq $10, 0x20(%0)\n"                                           \
        "sqc2 $vf4, 0x30(%0)\n"                                        \
        ".set pop\n"                                                   \
        : : "r"(dst), "r"(src)                                         \
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory")

/* MMI_COPY3Q_VADD(dst, src, add): copy the three quadwords at src 0x0/0x10/0x20
 * to dst via MMI lq/sq, and store dst.0x30 = src.0x30 + *add (vadd.xyz on the
 * COP2 unit).  Used to offset a matrix's translation row while copying its
 * basis. */
#define MMI_COPY3Q_VADD(dst, src, add)                                 \
    __asm__ __volatile__(                                              \
        ".set push\n.set noreorder\n"                                  \
        "lqc2 $vf4, 0x0(%2)\n"                                         \
        "lqc2 $vf5, 0x30(%1)\n"                                        \
        "lq $7, 0x0(%1)\n"                                             \
        "lq $8, 0x10(%1)\n"                                            \
        "lq $9, 0x20(%1)\n"                                            \
        "vadd.xyz $vf5, $vf5, $vf4\n"                                  \
        "sq $7, 0x0(%0)\n"                                             \
        "sq $8, 0x10(%0)\n"                                            \
        "sq $9, 0x20(%0)\n"                                            \
        "sqc2 $vf5, 0x30(%0)\n"                                        \
        ".set pop\n"                                                   \
        : : "r"(dst), "r"(src), "r"(add)                               \
        : "$7", "$8", "$9", "memory")

#endif /* GODHAND_MMI_H */
