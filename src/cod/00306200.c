/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern unsigned char D_003C3CFC;
extern void func_0030ECF8(int a0);
extern void func_002A9538(int a0, int a1, int a2);
extern void func_003009F8(int a0, int a1);
extern void func_002FB5C0(int a0, int a1);

__attribute__((section(".text.EnsureInitThenForward_2A9538_30EE08")))
void EnsureInitThenForward_2A9538_30EE08(int a0, int a1, int a2) {
    if (D_003C3CFC == 0) {
        func_0030ECF8(0);
    }
    func_002A9538(a2, a0, a1);
}

__attribute__((section(".text.KillEffect")))
void KillEffect(int a0, int a1, int a2) {
    if (a0 == 0 && a1 == -1) {
        return;
    }
    switch (a2) {
    case 0:
        func_003009F8(a0, a1);
        break;
    case 1:
        func_002FB5C0(a0, a1);
        break;
    case 2:
        func_002FB5C0(a0, a1);
        func_003009F8(a0, a1);
        break;
    }
}

__attribute__((section(".text.CreateObj")))
int CreateObj(int a0)
{
    return func_0030FB20(a0, func_0030FAC8(a0));
}
