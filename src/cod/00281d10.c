/* func_00281D10 — +0x2F6 phase machine like func_0027F570, but the func_002A8578
 * "t0" argument is 2 when the +0x15B0 flag is set, else 0.  sn-2.95.3-136.
 * (t0's constant is held in a separate long so SN emits move/movn, not movz.) */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int moveMotion(void *a0);
__attribute__((section(".text.func_00281D10")))
void func_00281D10(void *a0){ char *s0=(char*)a0; int v0;
 int t0=0; unsigned long two=2;
 if(*(unsigned char*)(s0+0x15B0)) t0=two;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0: v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0xC)+v0,*(int*)(v0+0x10)+v0,0.0f,5,t0,0);
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1: moveMotion(s0); break; } }
