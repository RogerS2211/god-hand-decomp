/* func_0027F8D8 — +0x2F6 phase machine: phase 0 fires func_002A8578 (params from
 * +0x304 record, fields 0x64/0x68) and advances; both phases step func_00157C18, and
 * when it reports done the 0x2F4..0x2F7 phase block is cleared.  sn-2.95.3-136. */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int func_00157C18(void *a0);
__attribute__((section(".text.func_0027F8D8")))
void func_0027F8D8(void *a0){ char *s0=(char*)a0; int v0;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0: v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0x64)+v0,*(int*)(v0+0x68)+v0,0.0f,5,0,0);
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1:
  if(func_00157C18(s0)!=0){ *(unsigned char*)(s0+0x2F4)=0; *(unsigned char*)(s0+0x2F5)=0;
   *(unsigned char*)(s0+0x2F6)=0; *(unsigned char*)(s0+0x2F7)=0; }
  break; } }
