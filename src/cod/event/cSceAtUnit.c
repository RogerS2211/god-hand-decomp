/* TU: cSceAtUnit [event] - recovered C++ class. */

__attribute__((section(".text.cSceAtUnit_ActTypeSet")))
void cSceAtUnit_ActTypeSet(char *obj, int a1, int a2) {
    obj[0x3A] = a1;
    obj[0x54] = a2;
}
