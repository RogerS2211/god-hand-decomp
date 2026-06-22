/* cOmDoor_releaseObjCollision — if the door holds a collision object (0x644),
 * release it from the collision manager (D_005CAE50 via func_0012EC58) and null
 * the slot.  sn-2.95.3-136. */

extern void func_0012EC58(void *, void *);
extern char D_005CAE50;

__attribute__((section(".text.cOmDoor_releaseObjCollision")))
void cOmDoor_releaseObjCollision(void *a0) {
    void *a1 = *(void **)((char *)a0 + 0x644);
    if (!a1)
        return;
    func_0012EC58(&D_005CAE50, a1);
    *(int *)((char *)a0 + 0x644) = 0;
}
