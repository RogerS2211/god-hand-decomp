extern int D_0044AEF8;

/* func_002A98A8 — object init: zero fields + set vtable/data pointer, return obj. */

__attribute__((section(".text.func_002A98A8")))
void * func_002A98A8(void *a0){
  *(int*)((char*)a0+0x0)=0;
  *(int**)((char*)a0+0x18)=&D_0044AEF8;
  *(int*)((char*)a0+0x4)=0;
  *(int*)((char*)a0+0xC)=0;
  *(int*)((char*)a0+0x8)=0;
  *(int*)((char*)a0+0x14)=0;
  *(signed char*)((char*)a0+0x10)=0;
  return a0;
}
