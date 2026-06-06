/* TU: cOm5e [object] - recovered C++ class. */

__attribute__((section(".text.cOm5e_setStop")))
void cOm5e_setStop(void *a0) {
    *(char *)((char *)a0 + 0x2F4) = 1;
    *(char *)((char *)a0 + 0x2F5) = 0;
    *(char *)((char *)a0 + 0x2F6) = 0;
    *(char *)((char *)a0 + 0x2F7) = 0;
}
