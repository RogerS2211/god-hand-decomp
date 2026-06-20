extern int D_00747A30;
extern char D_00569B70[];
extern int D_0044F448;

__attribute__((section(".text.UpdateConditionalNotify_292E80")))
void UpdateConditionalNotify_292E80(int a0)
{
    if ((D_00747A30 & 0x800) == 0) {
        if (func_00292F08() == 0) {
            SetEffect(0, 0xF, 0, 0, -1, 0xFFFFFFFFu);
            MaxByte538_292EF0(a0, 2);
        }
    }
}

__attribute__((section(".text.SetCostumeFlagIfMatch_2982A0")))
void SetCostumeFlagIfMatch_2982A0(int a0)
{
    int *s1 = (int *)a0;
    unsigned short s0;
    int v1;

    if (s1 != 0) {
        s0 = *(unsigned short *)((char *)s1 + 0x2FE);
        v1 = cCoreSave_getCostumeNo(D_00569B70);
        if (s0 == 0x603) {
            if ((unsigned int)((v1 - 4) & 0xFF) < 2) {
                *(int *)((char *)s1 + 0x250) = *(int *)((char *)s1 + 0x250) | 2;
            }
        }
    }
}

__attribute__((section(".text.IsSlotUsable_2CB830")))
int IsSlotUsable_2CB830(int a0, int a1)
{
	int s2;

	s2 = 1;
	if (func_002CFC78(GetIndexedEntry_2CC4B8(a0, a1)) == 1) {
		return 1;
	}
	if (func_002CFC88(GetIndexedEntry_2CC4B8(a0, a1)) != 0) {
		s2 = 0;
	}
	return s2;
}

__attribute__((section(".text.FindActiveSlot_2CC050")))
int FindActiveSlot_2CC050(int a0)
{
	int s0;

	for (s0 = 0x14; s0 < 0x34; s0++) {
		if (func_002CFC78(*(int *)(a0 + 0x3C) + (s0 << 6)) == 1) {
			return s0;
		}
	}
	return -1;
}

#include "godhand/vu0.h"




__attribute__((section(".text.Setup_Fields_2B0_2F56C0")))
void *Setup_Fields_2B0_2F56C0(void *a0)
{
	InitObject_2FBCC8(a0);

	*(int *)((char *)a0 + 0x2B0) = 0;
	*(float *)((char *)a0 + 0x2D4) = 1.0f;
	*(int **)((char *)a0 + 0xF0) = &D_0044F448;
	*(int *)((char *)a0 + 0x2B4) = 0;
	*(int *)((char *)a0 + 0x2B8) = 0;
	*(int *)((char *)a0 + 0x2BC) = 0;
	*(int *)((char *)a0 + 0x2C0) = 0;
	*(int *)((char *)a0 + 0x2C4) = 0;
	*(int *)((char *)a0 + 0x2C8) = 0;
	*(int *)((char *)a0 + 0x2D8) = 0;
	*(int *)((char *)a0 + 0x2DC) = 0;
	VU0_SQC2_VF0(a0, 0x300);
	*(int *)((char *)a0 + 0x2F0) = 0;
	return a0;
}
