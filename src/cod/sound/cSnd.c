/* TU: cSnd [sound] - recovered C++ class. */

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

INCLUDE_ASM("nonmatching", cSnd_EmSeCheck);

INCLUDE_ASM("nonmatching", cSnd_SeCall_2CB8A0);

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


INCLUDE_ASM("nonmatching", cSnd_BgmEventStop);

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


INCLUDE_ASM("nonmatching", cSnd_BgmEvSet);

INCLUDE_ASM("nonmatching", cSnd_BgmEvStart);

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


INCLUDE_ASM("nonmatching", cSnd_BgmEvReStart);

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
