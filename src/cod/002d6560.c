/* CustomIDWork_SetMessNo */
__attribute__((section(".text.CustomIDWork_SetMessNo")))
void CustomIDWork_SetMessNo(int a0,int a1){int p=*(int*)(a0+4);if(p)*(short*)(p+0x90)=a1;}
