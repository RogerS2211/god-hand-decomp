extern void func_001B6FB8(void*);
/* func_0017EEA0 — init (func_001B6FB8), set bit 0x10000 in field +0x250, return 1. sn-2.95.3-136. */
__attribute__((section(".text.func_0017EEA0")))
int func_0017EEA0(void *a0){ func_001B6FB8(a0); *(int*)((char*)a0+0x250)|=0x10000; return 1; }
