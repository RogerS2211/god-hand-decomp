extern int D_0044D1C8;

/* func_002D50C0 — object init: zero fields + set vtable/data pointer, return obj. */

__attribute__((section(".text.func_002D50C0")))
void * func_002D50C0(void *a0){
  *(int*)((char*)a0+0x0)=0;
  *(int**)((char*)a0+0x30)=&D_0044D1C8;
  *(int*)((char*)a0+0x4)=0;
  *(short*)((char*)a0+0xC)=0;
  *(short*)((char*)a0+0xE)=0;
  *(int*)((char*)a0+0x2C)=0;
  return a0;
}
