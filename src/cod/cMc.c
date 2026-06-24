/* TU: cMc - recovered C++ class. */
extern void *PTR_DAT_003c23a4;
extern void ObjTrans(void);
extern void func_002AF028(void *);
#include "include_asm.h"

INCLUDE_ASM("nonmatching", cMc_Move);

__attribute__((section(".text.cMc_Trans")))
void cMc_Trans(void) {
    ObjTrans();
    func_002AF028(PTR_DAT_003c23a4);
}
