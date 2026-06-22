/* cSceAtManager_AtDataReset_2C2838 — look up the AT unit for slot a1; if it
 * exists, reset its data via cSceAtManager_AtDataReset.  sn-2.95.3-136. */

extern void *cSceAtManager_getUnit(void *, int);
extern void cSceAtManager_AtDataReset(void *, void *);

__attribute__((section(".text.cSceAtManager_AtDataReset_2C2838")))
void cSceAtManager_AtDataReset_2C2838(void *a0, int a1) {
    void *v0 = cSceAtManager_getUnit(a0, a1 & 0xFFFF);
    if (v0)
        cSceAtManager_AtDataReset(a0, v0);
}
