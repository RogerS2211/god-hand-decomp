/* func_0027FB48 — +0x2F6 phase machine (record fields 0x78/0x7C, mode 5): phase 0
 * fires func_002A8578, sets +0x5F0=1 and advances; both phases step moveMotion and
 * clear the 0x2F4..0x2F7 phase block when it reports done.  sn-2.95.3-136. */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int moveMotion(void *a0);
__attribute__((section(".text.func_0027FB48")))
void func_0027FB48(void *a0){ char *s0=(char*)a0; int v0;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0: v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0x78)+v0,*(int*)(v0+0x7C)+v0,0.0f,5,0,0);
  *(int*)(s0+0x5F0)=1;
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1: if(moveMotion(s0)!=0){ *(unsigned char*)(s0+0x2F4)=0; *(unsigned char*)(s0+0x2F5)=0;
   *(unsigned char*)(s0+0x2F6)=0; *(unsigned char*)(s0+0x2F7)=0; } break; } }
