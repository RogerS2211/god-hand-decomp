extern int D_0041D8F8;
extern int D_00424328;
extern int D_00574380;
extern void func_0030F5A0(void *obj);
extern void func_001FE278(void *a, void *b);
extern void func_001B6F38(void *obj, void *a1);

/* func_00139878: store vtable at obj+0x35C (always); call func_0030F5A0
 * only when bit 0 of the flag arg is set. */
__attribute__((section(".text.func_00139878")))
void func_00139878(void *obj, int flags) {
    *(int **)((char *)obj + 0x35C) = &D_0041D8F8;
    if (flags & 1)
        func_0030F5A0(obj);
}

/* func_00192210: store vtable at obj+0x214; if obj->field_604 is live,
 * release it via func_001FE278 and clear it; then init via func_001B6F38. */
__attribute__((section(".text.func_00192210")))
void func_00192210(void *obj, void *a1) {
    *(int **)((char *)obj + 0x214) = &D_00424328;
    if (*(int *)((char *)obj + 0x604) != 0) {
        func_001FE278(&D_00574380, *(void **)((char *)obj + 0x604));
        *(int *)((char *)obj + 0x604) = 0;
    }
    func_001B6F38(obj, a1);
}
