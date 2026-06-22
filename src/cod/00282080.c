/* func_00282080 — +0x2F6 phase machine (record fields 0x7C/0x80, mode 5) with the
 * func_002A8578 t0 = flag@0x15B0 ? 2 : 0, plus the func_00157C18-done reset of the
 * 0x2F4..0x2F7 phase block.  sn-2.95.3-136. */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int func_00157C18(void *a0);
__attribute__((section(".text.func_00282080")))
void func_00282080(void *a0){ char *s0=(char*)a0; int v0;
 int t0=0; unsigned long two=2;
 if(*(unsigned char*)(s0+0x15B0)) t0=two;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0: v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0x7C)+v0,*(int*)(v0+0x80)+v0,0.0f,5,t0,0);
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1: if(func_00157C18(s0)!=0){ *(unsigned char*)(s0+0x2F4)=0; *(unsigned char*)(s0+0x2F5)=0;
   *(unsigned char*)(s0+0x2F6)=0; *(unsigned char*)(s0+0x2F7)=0; } break; } }
