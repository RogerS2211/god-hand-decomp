extern void func_001B6FB8(void*);
/* func_001B37D0 — init (func_001B6FB8), clear byte +0x2F4, return 1. sn-2.95.3-136. */
__attribute__((section(".text.func_001B37D0")))
int func_001B37D0(void *a0){ func_001B6FB8(a0); *(char*)((char*)a0+0x2F4)=0; return 1; }
