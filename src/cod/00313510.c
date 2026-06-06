extern int D_00747A34;
extern char D_00754220[];

__attribute__((section(".text.func_00313510")))
void *func_00313510(void)
{
    void *p;
    if (!(D_00747A34 & 0x100000))
    {
        p = EnsureInitThenForward_2A9538_30EE08(0x1570, 0x10, D_00754220);
        if (p != 0)
        {
            func_003A52F0(p, 0, 0x1570);
            return InitObjVtableAndType_2772A8(p);
        }
    }
    return 0;
}

__attribute__((section(".text.func_00313580")))
void *func_00313580(void)
{
    void *p;
    if (!(D_00747A34 & 0x100000))
    {
        p = EnsureInitThenForward_2A9538_30EE08(0x15B0, 0x10, D_00754220);
        if (p != 0)
        {
            func_003A52F0(p, 0, 0x15B0);
            return Setup_278068(p);
        }
    }
    return 0;
}

__attribute__((section(".text.func_003135F0")))
void *func_003135F0(void)
{
    void *p;
    if (!(D_00747A34 & 0x100000))
    {
        p = EnsureInitThenForward_2A9538_30EE08(0x15E0, 0x10, D_00754220);
        if (p != 0)
        {
            func_003A52F0(p, 0, 0x15E0);
            return InitObjVtable_27B768(p);
        }
    }
    return 0;
}

__attribute__((section(".text.func_00313660")))
int func_00313660(void)
{
    void *p;
    if (D_00747A34 & 0x100000)
        return 0;
    p = EnsureInitThenForward_2A9538_30EE08(0x31B0, 0x10, D_00754220);
    if (p == 0)
        return 0;
    func_003A52F0(p, 0, 0x31B0);
    return Setup_27DD88(p);
}

__attribute__((section(".text.func_003136D0")))
int func_003136D0(void)
{
    void *p;
    if (D_00747A34 & 0x100000)
        return 0;
    p = EnsureInitThenForward_2A9538_30EE08(0x15C0, 0x10, D_00754220);
    if (p == 0)
        return 0;
    func_003A52F0(p, 0, 0x15C0);
    return InitObjVtableAndTypeFull_27EE68(p);
}

__attribute__((section(".text.func_00313740")))
int func_00313740(void)
{
    void *p;
    if (D_00747A34 & 0x100000)
        return 0;
    p = EnsureInitThenForward_2A9538_30EE08(0x15C0, 0x10, D_00754220);
    if (p == 0)
        return 0;
    func_003A52F0(p, 0, 0x15C0);
    return func_00281638(p);
}
