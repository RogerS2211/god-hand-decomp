/* include/godhand/vu0.h — VU0 (COP2) macromode inline-asm helpers.
 *
 * # Why this header is project-local (not `include/sce/vu0.h`)
 *
 * The SCE PS2 SDK 3.0.20 does not ship a `<sce/vu0.h>` with
 * COP2 macromode intrinsics.  ee-gcc 2.96 has no `__builtin_vu_*`
 * surface either: every VU0 emission in retail code goes through
 * hand-written inline assembly.  This header is therefore a
 * project-local **idiom-stabilising** wrapper, not a vendored SDK
 * stub.  Per the lazy-vendor rule, if a canonical SCE header
 * with these intrinsics ever surfaces, this header is superseded
 * and moved/dropped accordingly.
 *
 * # The pipeline-delay nop convention
 *
 * **Empirically, for the load/store COP2 ops covered
 * here (`sqc2`, `lqc2`), ee-as does NOT auto-insert pipeline
 * nops in any tested mode (`.set noreorder`, `.set reorder`,
 * or default).**  Retail (`func_0027B768`) has 6 back-to-back
 * `sqc2 $vf0, off($s0)` with NO nops between them; a minimal
 * 3-sqc2 standalone .s file assembled with ee-as under each
 * `.set` mode also produces zero inter-op nops.  This
 * falsifies the assumption that ee-as inserts exactly 1 nop
 * per VU0 op for the quadword load/store class.  The universal
 * claim that ee-as inserts pipeline-delay nops even under `.set
 * noreorder` does NOT hold for sqc2/lqc2 in practice.
 *
 * Each macro therefore expands to a `.set noreorder` block
 * containing **only** the COP2 instruction (no extra nop):
 *
 *   .set push ; .set noreorder ; <COP2 op> ; .set pop
 *
 * The `.set noreorder` framing is still load-bearing — it
 * pins instruction order so ee-gcc's scheduler cannot reorder
 * around the inline asm and ee-as's `.set reorder` pass
 * cannot pull an unrelated instruction up into a delay slot
 * inside the macro.  But the explicit nop is dropped because
 * adding it would produce 8 B per macro vs the 4 B retail
 * actually uses, breaking byte equality (8-byte body inflation
 * per quadword zero-init).
 *
 * **Open question** (out of scope here): the q-pipeline ops
 * (`vsqrt`/`vdiv`/`vwaitq`) and some MAC/EFU sequences DO have
 * documented inter-op hazards in the EE Core Architecture
 * Manual.  Whether ee-as inserts nops for those is unverified
 * by the sqc2/lqc2 test.  When the first q-pipeline op surfaces,
 * test it the same way (build + objdump diff) before extending
 * this header with q-pipeline macros.
 *
 * # Scope
 *
 * This header ships only the macros that the active matching
 * tasks need.  Add more on demand; do NOT speculatively populate
 * (lazy-vendor pattern).  Today's covered ops:
 *
 *   VU0_SQC2_VF0(base, off)  -- store $vf0 (hard-zero) quadword
 *   VU0_SQC2(reg, base, off) -- store $vf<reg> quadword
 *   VU0_LQC2(reg, base, off) -- load quadword into $vf<reg>
 *
 * Not covered yet (file a follow-up + add when a real task needs
 * them):
 *
 *   - Vector arithmetic (vadd / vsub / vmul / vmaxw / vminw)
 *   - Q-pipeline ops (vsqrt / vdiv / vwaitq)
 *   - GPR <-> VU0 transfers (qmtc2 / qmfc2 / cfc2 / ctc2)
 *   - Float<->int conversion (vftoi* / vitof*)
 *
 * # Usage
 *
 *   #include "godhand/vu0.h"
 *
 *   void func_0027B768(void *obj) {
 *       VU0_SQC2_VF0(obj, 0x00);
 *       VU0_SQC2_VF0(obj, 0x10);
 *       VU0_SQC2_VF0(obj, 0x20);
 *       ...
 *   }
 *
 * The `"memory"` clobber on the store macros prevents GCC from
 * reordering memory accesses around the inline asm.  The `base`
 * pointer is an input constraint (`"r"`) so GCC will allocate it
 * to any GPR; the offset is a literal integer (`%2`) inlined into
 * the asm template.
 *
 * # Reopen triggers for this header
 *
 *   - First byte-match attempt that fails because the nop count
 *     is wrong: re-investigate the ee-as hazard analyser (skill
 *     § What could still go wrong #1) and adjust.
 *   - A canonical SCE `<sce/vu0.h>` surfaces: supersede + move
 *     this header to `include/sce/vu0.h` with the intrinsic
 *     names from the SDK.
 *   - GCC's clobber list forces a spill not in retail: tighten
 *     the constraint set (e.g. drop `"memory"` if static analysis
 *     proves no aliasing).
 */
#ifndef GODHAND_VU0_H
#define GODHAND_VU0_H

/* VU0_SQC2_VF0(base, off): "zero-init this quadword".
 *
 * Expands to:
 *     .set push
 *     .set noreorder
 *     sqc2  $vf0, off(base)
 *     .set pop
 *
 * $vf0 is hard-zero by VU0 hardware convention (reads as
 * (x=0, y=0, z=0, w=1.0)).  Storing $vf0 zero-fills the
 * 128 bits at base+off in one instruction.  Use for object
 * init, struct zeroing, GS packet header init, etc.
 *
 * `base` is any pointer expression (cast as needed); `off` is a
 * 16-bit-signed literal byte offset.
 */
#define VU0_SQC2_VF0(base, off)                                        \
    __asm__ __volatile__ (                                             \
        ".set push\n"                                                  \
        ".set noreorder\n"                                             \
        "sqc2  $vf0, %1(%0)\n"                                         \
        ".set pop\n"                                                   \
        :                                                              \
        : "r"((void *)(base)), "i"((int)(off))                         \
        : "memory")

/* VU0_SQC2(reg, base, off): store $vf<reg> quadword.
 *
 * `reg` is a register-number literal in [1, 31] (use VU0_SQC2_VF0
 * for $vf0 — the zero-init case is the dominant pattern in our
 * corpus and gets its own macro for readability).
 *
 * Expands to:
 *     .set push
 *     .set noreorder
 *     sqc2  $vf<reg>, off(base)
 *     .set pop
 */
#define VU0_SQC2(reg, base, off)                                       \
    __asm__ __volatile__ (                                             \
        ".set push\n"                                                  \
        ".set noreorder\n"                                             \
        "sqc2  $vf" #reg ", %1(%0)\n"                                  \
        ".set pop\n"                                                   \
        :                                                              \
        : "r"((void *)(base)), "i"((int)(off))                         \
        : "memory")

/* VU0_LQC2(reg, base, off): load quadword into $vf<reg>.
 *
 * Dual of VU0_SQC2.  `reg` is a register-number literal in
 * [1, 31] ($vf0 is read-only by VU0 hardware convention, so
 * loading into it is meaningless).
 *
 * Expands to:
 *     .set push
 *     .set noreorder
 *     lqc2  $vf<reg>, off(base)
 *     .set pop
 *
 * Note: `lqc2` follows the same no-explicit-nop convention as
 * the sqc2 macros (the empirically falsified nop assumption
 * covers stores; loads are expected to follow the same rule
 * but the first lqc2 byte-match attempt should re-confirm
 * before relying on it).  If
 * an `lqc2`-bearing function fails to byte-match because of a
 * missing pipeline nop, revisit the assumption and add an
 * explicit-nop variant.
 */
#define VU0_LQC2(reg, base, off)                                       \
    __asm__ __volatile__ (                                             \
        ".set push\n"                                                  \
        ".set noreorder\n"                                             \
        "lqc2  $vf" #reg ", %1(%0)\n"                                  \
        ".set pop\n"                                                   \
        :                                                              \
        : "r"((void *)(base)), "i"((int)(off))                         \
        : "memory")

/* VU0_VADD_XYZ(dst, s1, s2): $vf<dst>.xyz = $vf<s1>.xyz + $vf<s2>.xyz.
 * A compute-class COP2 op with no inter-op nop (same empirical finding as the
 * lqc2/sqc2 load/store class — see the header preamble); the `.set noreorder`
 * framing only pins order around the inline asm. */
#define VU0_VADD_XYZ(dst, s1, s2)                                      \
    __asm__ __volatile__ (                                             \
        ".set push\n"                                                  \
        ".set noreorder\n"                                             \
        "vadd.xyz $vf" #dst ", $vf" #s1 ", $vf" #s2 "\n"               \
        ".set pop\n")

/* VU0_VMOVE_XYZW(dst, src): $vf<dst> = $vf<src> (all four fields). */
#define VU0_VMOVE_XYZW(dst, src)                                       \
    __asm__ __volatile__ (                                             \
        ".set push\n.set noreorder\n"                                  \
        "vmove.xyzw $vf" #dst ", $vf" #src "\n"                        \
        ".set pop\n")

/* VU0_VMR32_XYZW(dst, src): $vf<dst> = $vf<src> rotated (x<-y<-z<-w<-x). */
#define VU0_VMR32_XYZW(dst, src)                                       \
    __asm__ __volatile__ (                                             \
        ".set push\n.set noreorder\n"                                  \
        "vmr32.xyzw $vf" #dst ", $vf" #src "\n"                        \
        ".set pop\n")

#endif /* GODHAND_VU0_H */
