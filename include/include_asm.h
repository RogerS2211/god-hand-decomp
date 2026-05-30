#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#if !defined(M2CTX) && !defined(PERMUTER)

#ifndef INCLUDE_ASM
/* Each carved function lives in its own `.text.<NAME>` section so the
 * build-time linker script can place several carves from the same C TU
 * at distinct virtual addresses.  Without per-function sections, the
 * linker only consumes a `.o`'s `(.text*)` once, which collapses
 * multiple INCLUDE_ASM'd functions into a single contiguous block at
 * the first carve slot.
 *
 * `.pushsection`/`.popsection` brackets keep the surrounding C code in
 * the default `.text` section so plain C function bodies in the same
 * TU continue to land normally.
 */
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__( \
        ".pushsection .text." #NAME ", \"ax\"\n" \
        "    .set noat\n" \
        "    .set noreorder\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        "    .set reorder\n" \
        "    .set at\n" \
        ".popsection\n" \
    )
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME) \
    __asm__( \
        ".section .rodata\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        ".section .text" \
    )
#endif

#if INCLUDE_ASM_USE_MACRO_INC
__asm__(".include \"include/macro.inc\"\n");
#else
__asm__(".include \"include/labels.inc\"\n");
#endif

#else

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)
#endif

#endif /* !defined(M2CTX) && !defined(PERMUTER) */

#endif /* INCLUDE_ASM_H */
