/* TU: cSnd [sound] - recovered C++ class. */
extern int func_002CB3A8(void *a0, int a1);
extern void *GetIndexedEntry_2CC4B8(void *a0, int a1);
extern int cSeData_IsAlive(void *p);
extern int func_002CFC88(void *p);
extern int D_0044CE48[];
extern void *func_002CBEC0(void *a0);
extern int func_002CDF18(void *p, short a1, int a2, int a3, int a4, int a5, int a6);
extern void func_002CD4A8(int a0, float f12);
extern void func_002CD470(int a0, float f12);
extern int func_002D22B0(int a0, int a1, int a2);
extern void func_002CCB10(int a0);
extern int func_002D2228(int a0);
extern int func_002CC9C0(int a0, int a1, int a2, int a3, unsigned int a4, int a5, int a6);
extern void ClearActiveBit_2CCAC8(int a0);
extern int func_002CC900(int a0, int a1, int a2, int a3, unsigned int a4, int a5, int a6);
extern void SetSequenceParam_373A18(int a0, int a1);

void func_002CD500(int, int, float);
void func_002CD4E0(int, float, float);
void UpdateSequenceNodeWeighted_373560(int, int, float);
float GetSequenceBlendWeight_373938(int, int);
void func_002CD4A8(int, float);
void func_002CD470(int, float);

__attribute__((section(".text.cSnd_SeCall")))
int cSnd_SeCall(void *a0, int a1, short a2, int a3, int a4, int a5)
{
    void *p;
    p = (void *)GetIndexedEntry_2CC4B8(a0, a1);
    if (cSeData_IsAlive(p) == 0)
        return 0;
    p = (void *)func_002CBEC0(a0);
    if ((int)p == 0)
        return 0;
    if (a3 == 0)
        return func_002CDF18(p, (short)a1, a2, (short)a4, (short)a5, 0, 0);
    return func_002CDE28(p, (short)a1, a2, a3, a4, a5);
}
#include "include_asm.h"

__attribute__((section(".text.cSnd_EmSeCheck")))
int cSnd_EmSeCheck(void *a0, int a1)
{
    int s1;
    int *p;
    unsigned int i;

    s1 = func_002CB3A8(a0, a1);
    if (s1 <= 0)
        s1 = a1;

    p = D_0044CE48;
    i = 0;
    do {
        void *e = GetIndexedEntry_2CC4B8(a0, *p);
        if (cSeData_IsAlive(e) != 0) {
            e = GetIndexedEntry_2CC4B8(a0, *p);
            if (*(int *)((char *)e + 0x3C) == s1) {
                e = GetIndexedEntry_2CC4B8(a0, *p);
                if (func_002CFC88(e) != 1)
                    return *p;
            }
        }
        i++;
        p++;
    } while (i < 0xC);

    return -1;
}
__attribute__((section(".text.cSnd_SeCall_2CB8A0")))
int cSnd_SeCall_2CB8A0(void *a0, int a1, short a2, short a3, short a4, int a5, int a6)
{
    void *p;
    p = GetIndexedEntry_2CC4B8(a0, a1);
    if (cSeData_IsAlive(p) == 0)
        return 0;
    p = func_002CBEC0(a0);
    if ((int)p == 0)
        return 0;
    return func_002CDF18(p, (short)a1, a2, a3, a4, a5, a6);
}
__attribute__((section(".text.cSnd_SeFadeOut")))
int cSnd_SeFadeOut(int a0, int a1, short a2)
{
    if (a1 == 0)
        return -1;
    return func_00375050(a1, a2);
}


__attribute__((section(".text.cSnd_SeEndCk")))
int cSnd_SeEndCk(void)
{
    return func_002CBF48() == 0;
}


__attribute__((section(".text.cSnd_BattleBgmAllPause")))
void cSnd_BattleBgmAllPause(int *a0, float a1)
{
    int *node;
    for (node = (int *)a0[6]; node != 0; node = (int *)node[0x88 / 4]) {
        if (node[0xB0 / 4] != 2)
            func_002CD500((int)node, 0x100000, a1);
    }
}


__attribute__((section(".text.cSnd_BgmEventSet")))
void cSnd_BgmEventSet(int a0, int a1, int a2, int a3)
{
    int r;
    r = func_002D2228(a0);
    if (r != 0)
        func_002CC9C0(r, 0, a1, 5, 0xFFFFFFFF, a2, a3);
}


INCLUDE_ASM("nonmatching", cSnd_BgmEventStart);

__attribute__((section(".text.cSnd_BgmEventFade")))
void cSnd_BgmEventFade(int a0, int a1, float f1, float f2, float f3)
{
    int node;
    node = func_002D22B0(a0, 0, a1);
    if (node != 0) {
        if (0.0f <= f3) {
            float w = GetSequenceBlendWeight_373938(node, 0);
            UpdateSequenceNodeWeighted_373560(node, -1, w * f3);
        }
        func_002CD4E0(node, f2, f1);
    }
}


__attribute__((section(".text.cSnd_BgmEventStop")))
void cSnd_BgmEventStop(int *a0, int a1)
{
    int *node;
    int flags;
    int v;

    a0[0xB0 / 4] &= 0xEFFFFFFF;
    a0[0xAC / 4] &= 0xEFFFFFFF;
    for (node = (int *)a0[6]; node != 0; node = (int *)node[0x88 / 4]) {
        if (node[0x94 / 4] == 5) {
            if (a1 != 1)
                func_002CD4A8((int)node, 0.0f);
        } else {
            flags = node[0x98 / 4];
            if (flags & 0x1000) {
                v = flags & ~0x1000;
                node[0x98 / 4] = v;
                if ((v & 0x1FF00) == 0 && node[0xB0 / 4] != 2)
                    func_002CD470((int)node, 15.0f);
            }
        }
    }
}
__attribute__((section(".text.cSnd_BgmEvDataEnd")))
void cSnd_BgmEvDataEnd(int *a0)
{
    int *node;
    int r;
    for (node = (int *)a0[6]; node != 0; node = (int *)node[0x88 / 4]) {
        if (node[0x8C / 4] - 0x80 == 1)
            func_002CD4A8((int)node, 10.0f);
    }
    r = cSnd_GetBgmData((int)a0, 1);
    func_002CFF90(r);
}


__attribute__((section(".text.cSnd_BgmEvSet")))
int cSnd_BgmEvSet(int a0, int a1, int a2)
{
    int r;
    r = func_002D22B0(a0, a1, a2);
    if (r != 0)
        func_002CCB10(r);
    r = func_002D2228(a0);
    if (r == 0)
        return 0;
    return func_002CC9C0(r, a1, a2, 4, 0xFFFFFFFFu, 0, 0) != 0;
}
__attribute__((section(".text.cSnd_BgmEvStart")))
int cSnd_BgmEvStart(int a0, int a1, int a2, int a3)
{
    int node;
    node = func_002D22B0(a0, a1, a2);
    if (node != 0) {
        if (*(int *)(node + 0x98) & 1)
            ClearActiveBit_2CCAC8(node);
        return 1;
    }
    node = func_002D2228(a0);
    if (node == 0)
        return 0;
    if (func_002CC900(node, a1, a2, 4, 0xFFFFFFFFu, 0, 0) == 0)
        return 0;
    SetSequenceParam_373A18(node, a3);
    return 1;
}
__attribute__((section(".text.cSnd_BgmEvPause")))
void cSnd_BgmEvPause(int *a0, int a1, int a2)
{
    int *node;
    for (node = (int *)a0[6]; node != 0; node = (int *)node[0x88 / 4]) {
        if ((a2 == -1 ||
             ((node[0x8C / 4] - 0x80) == a1 && node[0x90 / 4] == a2)) &&
            node[0x94 / 4] == 4)
            UpdateSequenceNodeSetFlag_373488((int)node);
    }
}


__attribute__((section(".text.cSnd_BgmEvReStart")))
void cSnd_BgmEvReStart(int *a0, int a1, int a2, int a3)
{
    int *node;
    for (node = (int *)a0[6]; node != 0; node = (int *)node[0x88 / 4]) {
        if ((a2 == -1 ||
             ((node[0x8C / 4] - 0x80) == a1 && node[0x90 / 4] == a2)) &&
            node[0x94 / 4] == 4) {
            ClearActiveBit_2CCAC8((int)node);
            if (a3 >= 0)
                SetSequenceParam_373A18((int)node, a3);
        }
    }
}
__attribute__((section(".text.cSnd_BgmEvAllSuspend")))
void cSnd_BgmEvAllSuspend(int *a0, float a1)
{
    int *node;
    for (node = (int *)a0[6]; node != 0; node = (int *)node[0x88 / 4]) {
        node[0x98 / 4] |= 0x800;
        func_002CD4A8((int)node, a1);
    }
}


__attribute__((section(".text.cSnd_BgmEvAllSignal")))
void cSnd_BgmEvAllSignal(int *a0, float a1)
{
    int *node;
    int flags;
    int v;
    for (node = (int *)a0[6]; node != 0; node = (int *)node[0x88 / 4]) {
        flags = node[0x98 / 4];
        if (flags & 0x800) {
            v = flags & ~0x800;
            node[0x98 / 4] = v;
            if ((v & 0x1FF00) == 0 && node[0xB0 / 4] != 2)
                func_002CD470((int)node, a1);
        }
    }
}


INCLUDE_ASM("nonmatching", cSnd_BgmHitBeSet);
