extern void func_001B6FB8(void*);
extern void func_0017DCB8(void*);
/* func_0017D680 — init (func_001B6FB8), forward to func_0017DCB8, return 1. sn-2.95.3-136. */
__attribute__((section(".text.func_0017D680")))
int func_0017D680(void *a0){ func_001B6FB8(a0); func_0017DCB8(a0); return 1; }
