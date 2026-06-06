/* TU: cScenario [event] - recovered C++ class. */
extern void SetFieldsCESignalSemaSleep_2D5AA0(int a0, int a1);

__attribute__((section(".text.cScenario_waitEventStartOk")))
void cScenario_waitEventStartOk(void *a0) {
    char *s0 = (char *)a0;
    char *s1 = s0 + 0x1C;
    while (func_002C3E40(s0) == 0) {
        SetFieldsCESignalSemaSleep_2D5AA0(*(int *)(s1 + 4), 1);
    }
}

__attribute__((section(".text.cScenario_setCam")))
int cScenario_setCam(void *a0, int a1) {
    return LoadScreenOverlay_2C3F10(a0, func_0031CE38(a1));
}
