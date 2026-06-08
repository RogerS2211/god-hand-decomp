/* TU: cCoreSave [system] - recovered C++ class. */
extern int D_003BF160[];
struct S001FA690 { char pad[0x10]; unsigned short f10; };
struct W001FA690 { struct S001FA690 *p; };
extern void func_001FA820(void *);
extern int func_001FB830(int *a0, unsigned int a1);
extern int D_00747A34;
#include "include_asm.h"
extern int D_00747A38;

__attribute__((section(".text.cCoreSave_getGameLevel")))
int cCoreSave_getGameLevel(void **arg0)
{
    int i;
    int r;
    if (*arg0 == 0) return 0;
    for (i = 0; i < 5; i++) {
        if (*(short *)((char *)*arg0 + 0x1C) < D_003BF160[i]) break;
    }
    r = i;
    if (i >= 3) r = 4;
    return r + 1;
}

__attribute__((section(".text.cCoreSave_setClearNum")))
void cCoreSave_setClearNum(struct W001FA690 *a0, unsigned short a1) {
    if (a0->p != 0) {
        a0->p->f10 = a1;
        if (a0->p->f10 >= 0x64) {
            a0->p->f10 = 0x63;
        }
    }
}

__attribute__((section(".text.cCoreSave_addGold")))
void cCoreSave_addGold(int *a0, int a1, int a2) {
    int *v1;
    int idx;
    int *arr;

    v1 = *(int **)a0;
    if (v1 == 0) {
        return;
    }
    idx = *(int *)((char *)v1 + 0x24);
    if (idx < 0x10) {
        arr = (int *)((char *)v1 + 0x28);
        arr[idx] = a1;
        v1 = *(int **)a0;
        *(int *)((char *)v1 + 0x24) += 1;
    }
    if (a2 == 1) {
        func_001FA820(a0);
    }
    {
        int *v0 = *(int **)a0;
        *(int *)((char *)v0 + 0x20) += a1;
    }
    v1 = *(int **)a0;
    if (*(int *)((char *)v1 + 0x20) > 999999) {
        *(int *)((char *)v1 + 0x20) = 999999;
    }
    v1 = *(int **)a0;
    if (*(int *)((char *)v1 + 0x20) < 0) {
        *(int *)((char *)v1 + 0x20) = 0;
    }
    if ((D_00747A34 & 0x2000000) != 0) {
        int *v0 = *(int **)a0;
        *(int *)((char *)v0 + 0x20) = 999999;
    }
}

__attribute__((section(".text.cCoreSave_getKeyCardNum")))
int cCoreSave_getKeyCardNum(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(int*)(p + 0x68);
}

__attribute__((section(".text.cCoreSave_getKeyNum")))
int cCoreSave_getKeyNum(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(int*)(p + 0x6C);
}

__attribute__((section(".text.cCoreSave_getReelItem")))
int cCoreSave_getReelItem(int **a0) {
    int *p = *a0;
    if (p == 0) {
        return 0;
    }
    if (D_00747A38 & 0x8000000) {
        *((unsigned char *)p + 0x156) = 6;
    }
    return *((unsigned char *)*a0 + 0x156);
}

__attribute__((section(".text.cCoreSave_setSkill")))
void cCoreSave_setSkill(int **a0, int a1, int a2)
{
    char v = (char)a2;
    if (*a0) {
        if (a1 < 0x80) {
            if (a1 < 0x72) {
                *(char *)((char *)*a0 + a1 + 0xB0) = v;
            }
        }
    }
}

__attribute__((section(".text.cCoreSave_getSkill")))
int cCoreSave_getSkill(char **a0, int a1)
{
    char *p;
    p = *a0;
    if (p == 0 || a1 >= 0x80 || a1 >= 0x72) {
        return -1;
    }
    if (D_00747A34 & 0x800000) {
        return 0;
    }
    return *(char *)(p + a1 + 0xB0);
}

__attribute__((section(".text.cCoreSave_getKillEmNum")))
short cCoreSave_getKillEmNum(int **a0, int a1) {
    short *p = (short *)*a0;
    short *q;
    if (p == 0) return 0;
    if (--a1 < 0) return 0;
    if (a1 >= 5) return 0;
    q = p + a1;
    return q[0x46];
}

__attribute__((section(".text.cCoreSave_getKillNpcNum")))
short cCoreSave_getKillNpcNum(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(short*)(p + 0x96);
}

__attribute__((section(".text.cCoreSave_addKillNpcNum")))
void cCoreSave_addKillNpcNum(int **a0) {
    int *p;
    int *q;
    p = *a0;
    if (p) {
        *(unsigned short *)((char *)p + 0x96) += 1;
        q = *a0;
        *(unsigned short *)((char *)q + 0xBB6) += 1;
    }
}

__attribute__((section(".text.cCoreSave_getCostumeNo")))
unsigned char cCoreSave_getCostumeNo(int a0)
{
    int p = *(int*)a0;
    if (!p) return 0;
    return *(unsigned char*)(p + 0xAE);
}

__attribute__((section(".text.cCoreSave_setCostumeNo")))
void cCoreSave_setCostumeNo(unsigned char **a0, unsigned int a1) {
    unsigned char *p;
    p = a0[0];
    a1 = a1 & 0xFF;
    if (p == 0) {
        return;
    }
    p[0xAF] = p[0xAE];
    a0[0][0xAE] = (unsigned char)a1;
}

__attribute__((section(".text.cCoreSave_ckPaper")))
int cCoreSave_ckPaper(int a0)
{
    int p = *(int*)a0;
    return p ? (*(unsigned char*)(p + 0x157) != 0) : 0;
}

__attribute__((section(".text.cCoreSave_addAllStageTime")))
void cCoreSave_addAllStageTime(int a0, int a1)
{
    int p = *(int*)a0;
    if (p) {
        *(int*)(p + 0xBBC) = *(int*)(p + 0xBBC) + a1;
    }
}

INCLUDE_ASM("nonmatching", cCoreSave_gameInit);

INCLUDE_ASM("nonmatching", cCoreSave_stageInit);

__attribute__((section(".text.cCoreSave_getCombo")))
int cCoreSave_getCombo(int *a0, unsigned int a1, unsigned int a2)
{
    unsigned int n;
    if (*a0 == 0) return 0;
    if (a2 >= 6) return 0;
    n = func_001FB830(a0, a1);
    if (a2 >= n) return 0;
    if (a1 >= 6) return 0;
    return *(int *)(*a0 + (a1 * 0x24 + a2 * 4) + 0x1B0);
}
