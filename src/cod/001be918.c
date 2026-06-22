extern void func_001B6FB8(void*);
/* func_001BE918 — init (func_001B6FB8), set bit 0x8 in field +0x5B8, return 1. sn-2.95.3-136. */
__attribute__((section(".text.func_001BE918")))
int func_001BE918(void *a0){ func_001B6FB8(a0); *(int*)((char*)a0+0x5B8)|=0x8; return 1; }
