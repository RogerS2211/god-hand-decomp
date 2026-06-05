/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00785E68;
extern unsigned char D_00426420[];
extern unsigned char D_00785798[];
extern void func_001C3BE8(void);
extern void func_0031EEA8(void *, unsigned char *, unsigned char *);
extern int D_00426438;
extern void func_001C27E8(void *);
extern void Obj0000_Set_Byte_54(char *, int);
extern char D_00574380[];
extern void func_001FE278(void *, int);
extern void ResetField214FreeField180_1C2820(void *, int);
extern int D_00785E78;
extern int D_00426508;
extern int D_00426520;
extern int D_00785E88;
extern int D_004265F0;
extern int D_00426608;

__attribute__((section(".text.GetObjW17bClassDesc_19E670")))
void *GetObjW17bClassDesc_19E670(void) {
    if (D_00785E68 == 0) {
        func_001C3BE8();
        func_0031EEA8(&D_00785E68, D_00426420, D_00785798);
    }
    return &D_00785E68;
}

#include "godhand/vu0.h"





__attribute__((section(".text.InitObjW17bSlots_19E6C0")))
void *InitObjW17bSlots_19E6C0(void *a0) {
    char *p;
    int i;
    func_001C27E8(a0);
    p = (char *)a0 + 0x620;
    *(int **)((char *)a0 + 0x214) = &D_00426438;
    for (i = 5; i != -1; i--) {
        VU0_SQC2_VF0(p, 0x00);
        VU0_SQC2_VF0(p, 0x10);
        VU0_SQC2_VF0(p, 0x20);
        VU0_SQC2_VF0(p, 0x30);
        VU0_SQC2_VF0(p, 0x40);
        Obj0000_Set_Byte_54(p, 0);
        p += 0x60;
    }
    return a0;
}

__attribute__((section(".text.ResetObjW17bVtableAndFree_19E748")))
void ResetObjW17bVtableAndFree_19E748(void *a0, int a1) {
    *(int *)((char *)a0 + 0x214) = (int)&D_00426438;
    if (*(int *)((char *)a0 + 0x600) != 0) {
        func_001FE278(D_00574380, *(int *)((char *)a0 + 0x600));
        *(int *)((char *)a0 + 0x600) = 0;
    }
    ResetField214FreeField180_1C2820(a0, a1);
}

__attribute__((section(".text.GetObjW17cClassDesc_19E8E8")))
int *GetObjW17cClassDesc_19E8E8(void) {
    if (D_00785E78 == 0) {
        func_001C3BE8();
        func_0031EEA8(&D_00785E78, &D_00426508, &D_00785798);
    }
    return &D_00785E78;
}

#include "godhand/vu0.h"





__attribute__((section(".text.InitObjW17cSlots_19E938")))
void *InitObjW17cSlots_19E938(void *a0) {
    char *p;
    int i;
    func_001C27E8(a0);
    *(int *)((char *)a0 + 0x214) = (int)&D_00426520;
    p = (char *)a0 + 0x620;
    for (i = 5; i != -1; i--) {
        VU0_SQC2_VF0(p, 0);
        VU0_SQC2_VF0(p, 0x10);
        VU0_SQC2_VF0(p, 0x20);
        VU0_SQC2_VF0(p, 0x30);
        VU0_SQC2_VF0(p, 0x40);
        Obj0000_Set_Byte_54(p, 0);
        p += 0x60;
    }
    return a0;
}

__attribute__((section(".text.ResetObjW17cVtableAndFree_19E9C0")))
void ResetObjW17cVtableAndFree_19E9C0(void *a0, int a1) {
    int v;
    *(int *)((char *)a0 + 0x214) = (int)&D_00426520;
    v = *(int *)((char *)a0 + 0x600);
    if (v != 0) {
        func_001FE278(&D_00574380, v);
        *(int *)((char *)a0 + 0x600) = 0;
    }
    ResetField214FreeField180_1C2820(a0, a1);
}

__attribute__((section(".text.GetObjW17dClassDesc_19EB68")))
int *GetObjW17dClassDesc_19EB68(void) {
    if (D_00785E88 == 0) {
        func_001C3BE8();
        func_0031EEA8(&D_00785E88, &D_004265F0, &D_00785798);
    }
    return &D_00785E88;
}

#include "godhand/vu0.h"





__attribute__((section(".text.InitObjW17dSlots_19EBB8")))
void *InitObjW17dSlots_19EBB8(void *a0) {
    char *p;
    int i;
    func_001C27E8(a0);
    *(int *)((char *)a0 + 0x214) = (int)&D_00426608;
    p = (char *)a0 + 0x620;
    for (i = 3; i != -1; i--) {
        VU0_SQC2_VF0(p, 0);
        VU0_SQC2_VF0(p, 0x10);
        VU0_SQC2_VF0(p, 0x20);
        VU0_SQC2_VF0(p, 0x30);
        VU0_SQC2_VF0(p, 0x40);
        Obj0000_Set_Byte_54(p, 0);
        p += 0x60;
    }
    return a0;
}
