/* cMessage_getMessageAddr — two-level table lookup keyed by a 16-bit id
 * (top nibble selects a table pointer, low 12 bits index an 8-byte entry).
 * Compiled with sn-2.95.3-136. */

__attribute__((section(".text.cMessage_getMessageAddr")))
void *cMessage_getMessageAddr(void *a0, unsigned short a1) {
    unsigned idx = a1;
    unsigned hi = (idx >> 12) << 2;
    unsigned lo = (idx & 0xFFF) << 3;
    char *base = *(char **)((char *)a0 + hi);
    return base + *(int *)(base + lo + 4);
}
