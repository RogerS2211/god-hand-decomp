/* TU: cOl2b [object] - recovered C++ class. */
#include "include_asm.h"
typedef struct CGUnk_00180310
{
  unsigned char unk[0xA28];
} CGUnk_00180310_t;

__attribute__((section(".text.cOl2b_setOpen")))
void cOl2b_setOpen(CGUnk_00180310_t *a0)
{
  int v0 = *((int *) (((unsigned char *) a0) + 0xA24));
  if (v0 == 1)
  {
    return;
  }
  a0->unk[0x2F4] = 1;
  a0->unk[0x2F5] = 0;
  a0->unk[0x2F6] = 0;
  a0->unk[0x2F7] = 0;
}

__attribute__((section(".text.cOl2b_setClose")))
void cOl2b_setClose(unsigned char *a0)
{
  int new_var;
  new_var = *((int *) (a0 + 0xA24));
  if (new_var == 2)
  {
    return;
  }
  a0[0x2F4] = 2;
 do { a0[0x2F7] = 0; } while (0);
  a0[0x2F5] = 0;
  a0[0x2F6] = 0;
}

__attribute__((section(".text.cOl2b_isActive")))
unsigned char cOl2b_isActive(unsigned char *a0) {
    return a0[0xA28];
}
