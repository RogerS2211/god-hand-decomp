/* func_0027CF40 — +0x2F6 phase machine; phase 0 picks func_002A8578 record fields
 * by the +0x2F7 sub-flag (0xB0/0xB4 when set, else 0xB8/0xBC; mode 3), advances;
 * both phases step func_00157C18.  sn-2.95.3-136. */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int func_00157C18(void *a0);
__attribute__((section(".text.func_0027CF40")))
void func_0027CF40(void *a0){ char *s0=(char*)a0; int v0;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0:
  if(*(unsigned char*)(s0+0x2F7)){ v0=*(int*)(s0+0x304);
   func_002A8578(s0,*(int*)(v0+0xB0)+v0,*(int*)(v0+0xB4)+v0,0.0f,3,0,0); }
  else { v0=*(int*)(s0+0x304);
   func_002A8578(s0,*(int*)(v0+0xB8)+v0,*(int*)(v0+0xBC)+v0,0.0f,3,0,0); }
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1: func_00157C18(s0); break; } }
