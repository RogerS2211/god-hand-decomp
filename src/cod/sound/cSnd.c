/* TU: cSnd [sound] - recovered C++ class. */

__attribute__((section(".text.cSnd_SeCall")))
int cSnd_SeCall(void *a0, int a1, short a2, int a3, int a4, int a5)
{
    void *p;
    p = (void *)func_002CC4B8(a0, a1);
    if (func_002CFC68(p) == 0)
        return 0;
    p = (void *)func_002CBEC0(a0);
    if ((int)p == 0)
        return 0;
    if (a3 == 0)
        return func_002CDF18(p, (short)a1, a2, (short)a4, (short)a5, 0, 0);
    return func_002CDE28(p, (short)a1, a2, a3, a4, a5);
}
