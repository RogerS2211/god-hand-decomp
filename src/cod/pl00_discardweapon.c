/* pl00_DiscardWeapon — if the player holds a weapon object (0x698), release it
 * (func_001CF8B0) and null the slot.  sn-2.95.3-136. */

extern void func_001CF8B0(void *);

__attribute__((section(".text.pl00_DiscardWeapon")))
void pl00_DiscardWeapon(void *a0) {
    void *p = *(void **)((char *)a0 + 0x698);
    if (!p)
        return;
    func_001CF8B0(p);
    *(int *)((char *)a0 + 0x698) = 0;
}
