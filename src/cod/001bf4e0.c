extern void func_001B6FB8(void*);
/* func_001BF4E0 — init (func_001B6FB8), clear bit 0x40 in field +0x5B8, return 1. sn-2.95.3-136. */
__attribute__((section(".text.func_001BF4E0")))
int func_001BF4E0(void *a0){ func_001B6FB8(a0); *(int*)((char*)a0+0x5B8)&=~0x40; return 1; }
