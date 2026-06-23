/* func_0027C6D0 — +0x2F6 phase machine (record fields 0x30/0x34, mode 5): phase 0
 * triggers a sound (cSnd_SeCall_2CBA48) and func_002A8578, advances; both phases
 * step moveMotion and reset the 0x2F4..0x2F7 phase block when done.  sn-2.95.3-136.
 * (cSnd_SeCall_2CBA48 declared int-returning so SN keeps the record ptr in v1.) */

extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int moveMotion(void *a0);
extern int cSnd_SeCall_2CBA48(void *a, int b, int c, void *d, int e, int f, int g, int h);
extern int D_005FEE00[];

__attribute__((section(".text.func_0027C6D0")))
void func_0027C6D0(void *a0){ char *s0=(char*)a0; int v0;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0:
  cSnd_SeCall_2CBA48(D_005FEE00,1,0,s0,0,0,0,0);
  v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0x30)+v0,*(int*)(v0+0x34)+v0,0.0f,5,0,0);
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1: if(moveMotion(s0)!=0){ *(unsigned char*)(s0+0x2F4)=0; *(unsigned char*)(s0+0x2F5)=0;
   *(unsigned char*)(s0+0x2F6)=0; *(unsigned char*)(s0+0x2F7)=0; } break; } }
