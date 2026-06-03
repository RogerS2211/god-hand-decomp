/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void func_00296CA8(void *a0);
extern void func_00296EF0(void *a0);

__attribute__((section(".text.func_00296C28")))
int func_00296C28(void *a0) {
    char *s = (char*)a0;
    switch (*(char*)(s + 5)) {
    case 0:
        func_00296CA8(s);
        *(unsigned char*)(s + 5) = *(unsigned char*)(s + 5) + 1;
    case 1:
        if (func_00296DD8(s)) {
            func_00296EF0(s);
            *(char*)(s + 7) = 0;
            *(char*)(s + 5) = 0;
            *(char*)(s + 6) = 0;
            *(char*)(s + 4) = 4;
            return 1;
        }
        return 0;
    }
    return 0;
}
