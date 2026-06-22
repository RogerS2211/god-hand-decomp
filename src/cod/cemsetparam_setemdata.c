/* cEmSetParam_setEmData — if the enemy-set record validates (func_00294B98),
 * apply all of its parameters (cEmSetParam_setEmAll).  sn-2.95.3-136. */

extern int func_00294B98(void *);
extern void cEmSetParam_setEmAll(void *);

__attribute__((section(".text.cEmSetParam_setEmData")))
void cEmSetParam_setEmData(void *a0) {
    if (func_00294B98(a0))
        cEmSetParam_setEmAll(a0);
}
