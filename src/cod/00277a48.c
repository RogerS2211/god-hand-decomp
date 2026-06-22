/* func_00277A48 — +0x2F6 phase machine (record fields 0x54/0x58, mode 3): phase 0
 * fires func_002A8578 and advances, phases 0/1 step func_00157C18 and add the
 * 1.0f-scaled vectors. Every phase then runs func_002DDAB0 on the +0xF0 object
 * (scale 10.0f) and re-arms 0x2F5=2 when it reports done.  sn-2.95.3-136. */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int func_00157C18(void *a0);
extern void AddScaledVecToField_100_14F9F0(void *a0, float s);
extern void AddScaledXfmVecToField_F0_14F928(void *a0, float s);
extern int func_002DDAB0(void *a0, int a1, float f);
__attribute__((section(".text.func_00277A48")))
void func_00277A48(void *a0){ char *s0=(char*)a0; int v0;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0: v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0x54)+v0,*(int*)(v0+0x58)+v0,0.0f,3,0,0);
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1:
  func_00157C18(s0);
  AddScaledVecToField_100_14F9F0(s0,1.0f);
  AddScaledXfmVecToField_F0_14F928(s0,1.0f); break; }
 if(func_002DDAB0(*(void**)(s0+0xF0),0,10.0f)!=0){
  *(unsigned char*)(s0+0x2F4)=0; *(unsigned char*)(s0+0x2F5)=2;
  *(unsigned char*)(s0+0x2F6)=0; *(unsigned char*)(s0+0x2F7)=0; } }
