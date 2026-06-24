/* TU: cOmb0 [object] - recovered C++ class. */
#include "include_asm.h"

extern int D_00462FC0;
void cCollisionSolidManage_CreateSphere(void *a, void *b, void *c, void *d, float e);
struct sph { int a; float b; int c; float d; };

__attribute__((section(".text.cOmb0_SetCollision")))
void cOmb0_SetCollision(char *a0)
{
    struct sph s;
    a0[0x62C] = 1;
    s.a = 0;
    s.b = 1.75f;
    s.c = 0;
    s.d = 1.0f;
    cCollisionSolidManage_CreateSphere(&D_00462FC0, a0, a0 + 0x80, &s, 1.75f);
}

