/* cCoreSave_setVital */
__attribute__((section(".text.cCoreSave_setVital")))
void cCoreSave_setVital(int a0,int a1){int s=*(int*)a0;if(s)*(int*)(s+0x84)=a1;}
