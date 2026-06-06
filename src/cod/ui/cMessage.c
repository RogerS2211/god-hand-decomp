/* TU: cMessage [ui] - recovered C++ class. */

__attribute__((section(".text.cMessage_deleteWorkId")))
int cMessage_deleteWorkId(void *a0, unsigned short a1)
{
    int v;
    v = func_002AED10(a0, a1);
    if (v == 0) {
        return 0;
    }
    func_002AEF10(a0, v);
    return 1;
}

__attribute__((section(".text.cMessage_deleteMessNo")))
int cMessage_deleteMessNo(void *a0, unsigned short a1)
{
    int v;
    v = func_002AED40(a0, a1);
    if (v == 0) {
        return 0;
    }
    func_002AEF10(a0, v);
    return 1;
}
