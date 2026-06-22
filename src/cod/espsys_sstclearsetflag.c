/* espSys_sstClearSetFlag — reset effect slot 0x40 (group 2) via func_00306330,
 * then clear the flag word at 0x414.  sn-2.95.3-136. */

extern void func_00306330(int, int);

__attribute__((section(".text.espSys_sstClearSetFlag")))
void espSys_sstClearSetFlag(void *a0) {
    func_00306330(0x40, 2);
    *(int *)((char *)a0 + 0x414) = 0;
}
