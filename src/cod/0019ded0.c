/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00426180;
extern void func_001C27E8(void *a);
extern void Obj0000_Set_Byte_54(void *a, int b);
extern int D_00574380;
extern void func_001FE278(void *a, void *b);
extern void func_001C2820(void *a, int b);
extern int D_00785E48;
extern int D_00426250;
extern int D_00785798;
extern void func_001C3BE8(void);
extern int D_00426268;
extern int D_00785E58;
extern int D_00426338;
extern int D_00426350;

#include "godhand/vu0.h"





__attribute__((section(".text.func_0019DED0")))
void *func_0019DED0(void *a0) {
    char *s0;
    int i;
    func_001C27E8(a0);
    s0 = (char*)a0 + 0x620;
    *(int*)((char*)a0 + 0x214) = (int)&D_00426180;
    for (i = 5; i != -1; i--) {
        VU0_SQC2_VF0(s0, 0x0);
        VU0_SQC2_VF0(s0, 0x10);
        VU0_SQC2_VF0(s0, 0x20);
        VU0_SQC2_VF0(s0, 0x30);
        VU0_SQC2_VF0(s0, 0x40);
        Obj0000_Set_Byte_54(s0, 0);
        s0 += 0x60;
    }
    return a0;
}

__attribute__((section(".text.func_0019DF58")))
void func_0019DF58(void *a0, int a1) {
    int v1;
    *(int*)((char*)a0 + 0x214) = (int)&D_00426180;
    v1 = *(int*)((char*)a0 + 0x600);
    if (v1 != 0) {
        func_001FE278(&D_00574380, (void*)v1);
        *(int*)((char*)a0 + 0x600) = 0;
    }
    func_001C2820(a0, a1);
}

__attribute__((section(".text.func_0019E170")))
int *func_0019E170(void) {
    if (D_00785E48 == 0) {
        func_001C3BE8();
        func_0031EEA8(&D_00785E48, &D_00426250, &D_00785798);
    }
    return &D_00785E48;
}

#include "godhand/vu0.h"





__attribute__((section(".text.func_0019E1C0")))
void *func_0019E1C0(void *a0) {
    char *s0;
    int i;
    func_001C27E8(a0);
    *(int **)((char *)a0 + 0x214) = &D_00426268;
    i = 3;
    s0 = (char *)a0 + 0x620;
    do {
        VU0_SQC2_VF0(s0, 0x0);
        VU0_SQC2_VF0(s0, 0x10);
        VU0_SQC2_VF0(s0, 0x20);
        VU0_SQC2_VF0(s0, 0x30);
        VU0_SQC2_VF0(s0, 0x40);
        Obj0000_Set_Byte_54(s0, 0);
        i--;
        s0 += 0x60;
    } while (i != -1);
    return a0;
}

__attribute__((section(".text.func_0019E248")))
void func_0019E248(void *a0, int a1) {
    int v1;
    *(int **)((char *)a0 + 0x214) = &D_00426268;
    v1 = *(int *)((char *)a0 + 0x600);
    if (v1 != 0) {
        func_001FE278(&D_00574380, v1);
        *(int *)((char *)a0 + 0x600) = 0;
    }
    func_001C2820(a0, a1);
}

__attribute__((section(".text.func_0019E3F8")))
int *func_0019E3F8(void) {
    if (D_00785E58 == 0) {
        func_001C3BE8();
        func_0031EEA8(&D_00785E58, &D_00426338, &D_00785798);
    }
    return &D_00785E58;
}

#include "godhand/vu0.h"





__attribute__((section(".text.func_0019E448")))
void *func_0019E448(void *a0) {
    char *s0;
    int i;
    func_001C27E8(a0);
    *(int **)((char *)a0 + 0x214) = &D_00426350;
    i = 9;
    s0 = (char *)a0 + 0x620;
    do {
        VU0_SQC2_VF0(s0, 0x0);
        VU0_SQC2_VF0(s0, 0x10);
        VU0_SQC2_VF0(s0, 0x20);
        VU0_SQC2_VF0(s0, 0x30);
        VU0_SQC2_VF0(s0, 0x40);
        Obj0000_Set_Byte_54(s0, 0);
        i--;
        s0 += 0x60;
    } while (i != -1);
    return a0;
}
