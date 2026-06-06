extern int func_0034DD70(char *a0, unsigned int a1);

__attribute__((section(".text.SetFieldIfUnset_359218")))
int SetFieldIfUnset_359218(char *a0, int a1) {
    int v1 = *(int *)(a0 + 0x58);
    if (v1 == 0) {
        *(int *)(a0 + 0x58) = a1;
        return 0;
    }
    if (v1 == a1) {
        return 0;
    }
    return func_0034DD70(a0, 0xFF000207U);
}
