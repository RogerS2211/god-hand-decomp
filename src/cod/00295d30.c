/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern unsigned char D_0044A870[];
extern void func_0026E988(void*, int, int, int, float);
extern void func_0026E7A8(int a0, int a1);
extern void func_00297660(void *a0);
extern int D_00569B70;

__attribute__((section(".text.SetClampedShortParam_295D30")))
void SetClampedShortParam_295D30(void *a0, int a1) {
    if (FindResolveActor_295978(a0)) {
        char *p = *(char **)((char *)a0 + 4);
        if (a1 >= *(short *)(p + 0x548)) {
            *(short *)(p + 0x54A) = *(unsigned short *)(p + 0x548);
        } else {
            *(short *)(p + 0x54A) = (short)a1;
        }
    }
}

__attribute__((section(".text.SetByteParam531_295EE0")))
void SetByteParam531_295EE0(void *a0, char a1) {
    if (FindResolveActor_295978(a0)) {
        *(char *)(*(char **)((char *)a0 + 4) + 0x531) = a1;
    }
}

__attribute__((section(".text.func_00295F28")))
int func_00295F28(void *a0){
 char *p;
 if(!FindResolveActor_295978(a0)) return 0;
 p=*(char**)((char*)a0+4);
 return func_003A5678(D_0044A870,*(int*)(p+0x4AC))?0:Obj0000_IsSet_Field_16D0_Bit_1_26ECC0(*(void**)((char*)a0+4));
}

__attribute__((section(".text.func_00295F80")))
void func_00295F80(void *a0,int a1,int a2,int a3,float f){
 if(FindResolveActor_295978(a0)){
  char *p=*(char**)((char*)a0+4);
  if(*(short*)(p+0x54A)>0){
   if(func_003A5678(D_0044A870,*(int*)(p+0x4AC))==0){
    func_0026E988(*(void**)((char*)a0+4),a1,a2,a3,f);
   }
  }
 }
}

__attribute__((section(".text.func_00296018")))
int func_00296018(void *a0){
 char *p;
 if(!FindResolveActor_295978(a0)) return 0;
 p=*(char**)((char*)a0+4);
 return func_003A5678(D_0044A870,*(int*)(p+0x4AC))?0:func_0026EA28(*(void**)((char*)a0+4));
}

__attribute__((section(".text.ForwardE7A8Call_296070")))
void ForwardE7A8Call_296070(void *a0, int a1) {
    void *s0 = a0;
    int s1 = a1;
    if (FindResolveActor_295978(s0)) {
        int *v0 = *(int**)((char*)s0 + 4);
        if (func_003A5678(&D_0044A870, *(int*)((char*)v0 + 0x4AC)) == 0)
            func_0026E7A8(*(int*)((char*)s0 + 4), s1);
    }
}

__attribute__((section(".text.ResetObjectState_2962B0")))
void ResetObjectState_2962B0(void *a0) {
    *(int *)((char *)a0 + 0x38) = GetSubObjAt180_1F9FF0(&D_00569B70);
    func_00297660(a0);
    *(char *)((char *)a0 + 0x34) = 0;
    *(int *)((char *)a0 + 0) = 0;
}
