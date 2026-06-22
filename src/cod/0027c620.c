/* func_0027C620 — +0x2F6 phase machine (record fields 0x28/0x2C, mode 5): phase 0
 * fires func_002A8578 and registers a render struct (InitRenderStruct_2A8608,
 * 0xBC/0x1C, flags from +0x15B0), advances; both phases step func_00157C18 and reset
 * the 0x2F4..0x2F7 phase block when done.  sn-2.95.3-136. */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int func_00157C18(void *a0);
extern void InitRenderStruct_2A8608(void *a0, int a1, int a2, int a3, int t0, int t1);
__attribute__((section(".text.func_0027C620")))
void func_0027C620(void *a0){ char *s0=(char*)a0; int v0;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0: v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0x28)+v0,*(int*)(v0+0x2C)+v0,0.0f,5,0,0);
  InitRenderStruct_2A8608(s0,0xBC,0x1C,0,2,*(int*)(s0+0x15B0));
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1: if(func_00157C18(s0)!=0){ *(unsigned char*)(s0+0x2F4)=0; *(unsigned char*)(s0+0x2F5)=0;
   *(unsigned char*)(s0+0x2F6)=0; *(unsigned char*)(s0+0x2F7)=0; } break; } }
