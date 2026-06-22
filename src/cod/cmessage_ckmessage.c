/* cMessage_ckMessage — return whether a message window exists for id a1
 * (func_002AED40 returns non-null).  sn-2.95.3-136. */

extern void *func_002AED40(void *, int);

__attribute__((section(".text.cMessage_ckMessage")))
int cMessage_ckMessage(void *a0, int a1) {
    return func_002AED40(a0, a1 & 0xFFFF) != 0;
}
