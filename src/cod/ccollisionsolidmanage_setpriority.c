/* cCollisionSolidManage_SetPriority — resolve the collision-solid handle for
 * (a0,a1) via func_001346C8; if found, set its priority field to a2
 * (Obj0000_Set_Field_8_134648).  sn-2.95.3-136. */

extern void *func_001346C8(void *, int);
extern void Obj0000_Set_Field_8_134648(void *, int);

__attribute__((section(".text.cCollisionSolidManage_SetPriority")))
void cCollisionSolidManage_SetPriority(void *a0, int a1, int a2) {
    void *v0 = func_001346C8(a0, a1);
    if (v0)
        Obj0000_Set_Field_8_134648(v0, a2);
}
