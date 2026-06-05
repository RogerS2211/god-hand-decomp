/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int ChangeThreadPriority(int tid, int prio);
extern int SignalSema(int sema);
extern void ExitDeleteThread(void);

struct s_002D5A48 {
    int *field_0;
    int field_4;
    int pad_8;
    short field_C;
};

__attribute__((section(".text.func_002D5A48")))
void func_002D5A48(struct s_002D5A48 *a0)
{
    a0->field_C = 0;
    if (a0->field_4 != -1) {
        ChangeThreadPriority(a0->field_4, 1);
        SignalSema(a0->field_0[10]);
        a0->field_4 = -1;
        ExitDeleteThread();
    }
}
