/* func_002D0630: `func_002D0658(0.0f)` — forwarding call with a float arg. */
extern void func_002D0658(float);
__attribute__((section(".text.func_002D0630")))
void func_002D0630(void) { func_002D0658(0.0f); }

/* func_002C2A98: chain — alloc via func_002C3118(a0,a1); if non-null,
 * tail-process via func_002C0ED0(obj, a2); else return 0. */
extern void *func_002C3118(void *a0, void *a1);
extern void *func_002C0ED0(void *obj, void *a2);
__attribute__((section(".text.func_002C2A98")))
void *func_002C2A98(void *a0, void *a1, void *a2) {
    void *v0 = func_002C3118(a0, a1);
    if (v0 == 0) return 0;
    return func_002C0ED0(v0, a2);
}

/* func_002BF108: pointer-arithmetic getter — DEFERRED.  The natural body
 * compiles to the right 10 insns but SN -O2 emits a branch-likely
 * (`beqzl`) with the shared `a1<<2` hoisted before the compare, whereas
 * retail uses a plain `beqz` with the shift in its delay slot.  Matching
 * needs branch-likely suppression (a per-TU `-mno-branch-likely` would
 * destabilize the other SN TUs); left for a focused codegen-flag pass. */

/* func_00297C20: gated predicate.  If a global flag bit is set, return
 * whether obj->byte_4 == 3; else 0. */
extern int D_00747A84;
__attribute__((section(".text.func_00297C20")))
int func_00297C20(signed char *a0) {
    if (!(D_00747A84 & 0x20000000))
        return 0;
    return a0[4] == 3;
}

/* func_00295AB8: getter with a guard call.  If func_00295978(a0) is 0,
 * return &D_00747B00; else return obj->field_4->field_F0. */
extern int D_00747B00;
extern int func_00295978(void *a0);
__attribute__((section(".text.func_00295AB8")))
void *func_00295AB8(void *a0) {
    if (func_00295978(a0) == 0)
        return &D_00747B00;
    return *(void **)(*(char **)((char *)a0 + 4) + 0xF0);
}

/* func_002E76F8: constructor — store vtable at obj+0xF0, register via
 * func_002D9158, then init via func_002FBE28(obj, a1). */
extern int D_0044E640;
extern int D_00604700;
extern void func_002D9158(void *a, unsigned short b, int c);
extern void func_002FBE28(void *obj, void *a1);
__attribute__((section(".text.func_002E76F8")))
void func_002E76F8(void *obj, void *a1) {
    *(int **)((char *)obj + 0xF0) = &D_0044E640;
    func_002D9158(&D_00604700, *(unsigned short *)((char *)obj + 0x2B2),
                  *(int *)((char *)obj + 0x2B4));
    func_002FBE28(obj, a1);
}
