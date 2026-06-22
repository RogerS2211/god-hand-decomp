extern void func_001B6FB8(void*);
/* func_00178870 — init (func_001B6FB8), clear field +0x600, return 1. sn-2.95.3-136. */
__attribute__((section(".text.func_00178870")))
int func_00178870(void *a0){ func_001B6FB8(a0); *(int*)((char*)a0+0x600)=0; return 1; }
