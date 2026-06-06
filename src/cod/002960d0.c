/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int FindResolveActor_295978(void *a0, float f);
extern void func_0026E7A0(int a0, float f);
extern int D_0044A870;
extern void func_002736F8(int a0);
extern void func_00289028(int a0);
extern int D_0044A878;
extern void func_00289038(int a0, int a1);
extern void cEm00_setAlphaMode(int a0, int a1);

__attribute__((section(".text.ForwardE7A0Call_2960D0")))
void ForwardE7A0Call_2960D0(void *a0, float f) {
    if (FindResolveActor_295978(a0, f)) {
        int *p = *(int **)((char *)a0 + 4);
        if (func_003A5678(&D_0044A870, p[0x4AC / 4]) == 0) {
            func_0026E7A0(*(int *)((char *)a0 + 4), f);
        }
    }
}

__attribute__((section(".text.func_00296130")))
void func_00296130(void *a0, float f) {
    if (FindResolveActor_295978(a0, f)) {
        int *p = *(int **)((char *)a0 + 4);
        if (func_003A5678(&D_0044A870, p[0x4AC / 4]) == 0) {
            func_002736F8(*(int *)((char *)a0 + 4));
        }
    }
}

__attribute__((section(".text.func_00296180")))
void func_00296180(void *a0, float f) {
    if (FindResolveActor_295978(a0, f)) {
        int *p = *(int **)((char *)a0 + 4);
        if (func_003A5678(&D_0044A878, p[0x4AC / 4]) == 0) {
            func_00289028(*(int *)((char *)a0 + 4));
        }
    }
}

__attribute__((section(".text.func_002961D0")))
void func_002961D0(void *a0, int a1, float f) {
    if (FindResolveActor_295978(a0, f)) {
        int *p = *(int **)((char *)a0 + 4);
        if (func_003A5678(&D_0044A878, p[0x4AC / 4]) == 0) {
            func_00289038(*(int *)((char *)a0 + 4), a1);
        }
    }
}

__attribute__((section(".text.SetTimerByFlag_296230")))
void SetTimerByFlag_296230(void *a0, int a1, float f) {
    if (FindResolveActor_295978(a0, f)) {
        int *p = *(int **)((char *)a0 + 4);
        if (func_003A5678(&D_0044A870, p[0x4AC / 4]) == 0) {
            cEm00_setAlphaMode(*(int *)((char *)a0 + 4), a1);
            if (a1 == 0) {
                *(short *)(*(char **)((char *)a0 + 4) + 0x2AE) = 0x1770;
            } else {
                *(short *)(*(char **)((char *)a0 + 4) + 0x2AE) = 0x258;
            }
        }
    }
}
