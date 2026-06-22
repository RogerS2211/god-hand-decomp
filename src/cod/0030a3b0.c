#include "godhand/mmi.h"

/* sceVu0TransposeMatrix -- transpose a 4x4 matrix (a1 -> a0) using the EE's
 * 128-bit MMI parallel-extend / parallel-copy ops.  A pure SIMD register
 * shuffle with no C form; see godhand/mmi.h. */

__attribute__((section(".text.sceVu0TransposeMatrix")))
void sceVu0TransposeMatrix(void *a0, void *a1) {
    MMI_TRANSPOSE_MATRIX4(a0, a1);
}
