/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void CustomIDWork_SetDisp(char *a0, int a1);
extern struct T32 D_0042B5B0;
extern int CustomIDWork_SetNumber(int a0, int a1);

__attribute__((section(".text.SetCustomIDDispOneOrAll_1DD258")))
void SetCustomIDDispOneOrAll_1DD258(char *a0, int a1, int a2)
{
    int i;

    if (a2 != 0) {
        if (a1 == 0x4D) {
            for (i = 0; i < 0x4D; i++) {
                if (i != 0)
                    CustomIDWork_SetDisp(a0 + 0x60 + i * 0x7C, 1);
            }
        } else if (a1 != 0) {
            CustomIDWork_SetDisp(a0 + (a1 * 0x7C + 0x60), 1);
        }
    } else {
        if (a1 == 0x4D) {
            for (i = 0; i < 0x4D; i++) {
                if (i != 0)
                    CustomIDWork_SetDisp(a0 + 0x60 + i * 0x7C, 0);
            }
        } else if (a1 != 0) {
            CustomIDWork_SetDisp(a0 + (a1 * 0x7C + 0x60), 0);
        }
    }
}

__attribute__((section(".text.SetCustomIDDispOneOrAll_1F4778")))
void SetCustomIDDispOneOrAll_1F4778(char *a0, int a1, int a2)
{
    if (a2 != 0) {
        if (a1 == 0x6F) {
            char *s0 = a0 + 0x60;
            int s1;
            for (s1 = 0x6E; s1 >= 0; s1--) {
                CustomIDWork_SetDisp(s0, 1);
                s0 += 0x7C;
            }
        } else {
            CustomIDWork_SetDisp(a0 + (a1 * 0x7C + 0x60), 1);
        }
    } else {
        if (a1 == 0x6F) {
            char *s0 = a0 + 0x60;
            int s1;
            for (s1 = 0x6E; s1 >= 0; s1--) {
                CustomIDWork_SetDisp(s0, 0);
                s0 += 0x7C;
            }
        } else {
            CustomIDWork_SetDisp(a0 + (a1 * 0x7C + 0x60), 0);
        }
    }
}

struct T32 { int v[8]; };


__attribute__((section(".text.SetCustomIDNumberIndexed_1DD648")))
int SetCustomIDNumberIndexed_1DD648(int a0, unsigned int a1, int a2) {
    unsigned int i = a1 & 0xFFFF;
    if (i < 8) {
        struct T32 buf;
        int t;
        buf = D_0042B5B0;
        t = buf.v[i] * 0x7C + 0x60;
        return CustomIDWork_SetNumber(a0 + t, a2);
    }
}
