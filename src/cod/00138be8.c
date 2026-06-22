#include "godhand/vu0.h"

/* func_00138BE8 — composite object constructor: run the base constructors for
 * the object and its sub-objects (func_00139BC8, func_001380A8 at 0x530 and
 * 0xC90), set a vtable at 0x530+0x35C, zero a quadword block, and run the
 * remaining field/child initialisers.  sn-2.95.3-136. */

extern void *func_00139BC8(void *);
extern void *func_001380A8(void *);
extern void InitObjectFields364_1398D0(void *);
extern void func_00137A48(void *);
extern void func_00138C70(void *);
extern int D_0041D8F8;

__attribute__((section(".text.func_00138BE8")))
void *func_00138BE8(void *a0) {
    char *s1 = (char *)a0 + 0x530;
    func_00139BC8(a0);
    func_001380A8(s1);
    *(int **)(s1 + 0x35C) = &D_0041D8F8;
    VU0_SQC2_VF0(a0, 0x8A0);
    VU0_SQC2_VF0(a0, 0x8B0);
    VU0_SQC2_VF0(a0, 0x8C0);
    VU0_SQC2_VF0(a0, 0x8E0);
    VU0_SQC2_VF0(a0, 0x8F0);
    VU0_SQC2_VF0(a0, 0x900);
    InitObjectFields364_1398D0((char *)a0 + 0x920);
    func_001380A8((char *)a0 + 0xC90);
    func_00137A48((char *)a0 + 0xFF4);
    *(int *)((char *)a0 + 0xFF0) = 0;
    func_00138C70(a0);
    return a0;
}
