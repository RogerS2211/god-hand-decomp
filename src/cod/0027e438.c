/* func_0027E438 — +0x2F6 phase machine (record fields 0x190/0x194, mode 0): phase
 * 0 fires func_002A8578 and advances; both phases step func_00157C18 then add a unit
 * (1.0f) scaled vector into the +0x100 and +0xF0 fields.  sn-2.95.3-136. */
extern void func_002A8578(void *a0, int a1, int a2, float f, int a3, int t0, int t1);
extern int func_00157C18(void *a0);
extern void AddScaledVecToField_100_14F9F0(void *a0, float s);
extern void AddScaledXfmVecToField_F0_14F928(void *a0, float s);
__attribute__((section(".text.func_0027E438")))
void func_0027E438(void *a0){ char *s0=(char*)a0; int v0;
 switch(*(unsigned char*)(s0+0x2F6)){
 case 0: v0=*(int*)(s0+0x304);
  func_002A8578(s0,*(int*)(v0+0x190)+v0,*(int*)(v0+0x194)+v0,0.0f,0,0,0);
  *(unsigned char*)(s0+0x2F6)=*(unsigned char*)(s0+0x2F6)+1;
 case 1: func_00157C18(s0); AddScaledVecToField_100_14F9F0(s0,1.0f);
  AddScaledXfmVecToField_F0_14F928(s0,1.0f); break; } }
