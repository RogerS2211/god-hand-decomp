/* cMessage_closeMessNo — look up the message window for id a1 (func_002AED40);
 * if found, close it (func_002B2400) and return 1, else 0.  sn-2.95.3-136. */

extern void *func_002AED40(void *, int);
extern void func_002B2400(void *);

__attribute__((section(".text.cMessage_closeMessNo")))
int cMessage_closeMessNo(void *a0, int a1) {
    void *p = func_002AED40(a0, a1 & 0xFFFF);
    if (!p)
        return 0;
    func_002B2400(p);
    return 1;
}
