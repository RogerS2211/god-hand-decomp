/* CustomIDWork_SetChildNoDisp */
__attribute__((section(".text.CustomIDWork_SetChildNoDisp")))
void CustomIDWork_SetChildNoDisp(int a0,int a1){int p=*(int*)(a0+4);if(p==0)return;if(a1)*(int*)(p+0x2C)|=8;else *(int*)(p+0x2C)&=~8;}
