/* func_00278878 — sets +0x54C=3.0f, then a +0x2F6 phase machine (record fields
 * 0x1C/0x20, mode 2); on func_00157C18 completion it re-arms the phase block to
 * 0x2F5=2, then adds the 1.0f-scaled vectors.  sn-2.95.3-136. */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int func_00157C18(void *a0);
extern void AddScaledVecToField_100_14F9F0(void *a0, float s);
extern void AddScaledXfmVecToField_F0_14F928(void *a0, float s);
__attribute__((section(".text.func_00278878")))
void func_00278878(void *a0){ char *s0=(char*)a0; int v0;
 *(float*)(s0+0x54C)=3.0f;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0: v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0x1C)+v0,*(int*)(v0+0x20)+v0,0.0f,2,0,0);
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1:
  if(func_00157C18(s0)!=0){ *(unsigned char*)(s0+0x2F4)=0; *(unsigned char*)(s0+0x2F5)=2;
   *(unsigned char*)(s0+0x2F6)=0; *(unsigned char*)(s0+0x2F7)=0; }
  AddScaledVecToField_100_14F9F0(s0,1.0f);
  AddScaledXfmVecToField_F0_14F928(s0,1.0f); break; } }
