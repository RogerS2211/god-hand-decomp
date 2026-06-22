/* func_001E48E0 — register the action-button handler func_001E4920 for slot 2
 * (table D_00568288, fields 4/0x15) with the object a0.  sn-2.95.3-136. */

extern void LookupSlotPopulateFieldsAndDispatch_1F7858(void *, int, int, int, void *, void *, int);
extern char D_00568288;
extern void func_001E4920(void);

__attribute__((section(".text.func_001E48E0")))
void func_001E48E0(void *a0) {
    LookupSlotPopulateFieldsAndDispatch_1F7858(&D_00568288, 4, 0x15, 0, (void *)&func_001E4920, a0, 0);
}
