/* TU: Poker [casino] - recovered C++ class. */
#include "include_asm.h"

extern void func_001DD340();
extern void SetCustomIDNumberIndexed_1DD648();
extern char D_003BE000[];
extern int D_00569B70;
extern void func_001D6E20();
extern void func_001D6F30();
extern void func_001DD238();
extern int GetTimerValue_1FA710();
extern void PokerId_Move();
extern void PokerId__Trans();

INCLUDE_ASM("nonmatching", Poker_Initialize);

__attribute__((section(".text.Poker_Release")))
void Poker_Release(void) {
    func_001DF940();
}


__attribute__((section(".text.Poker_SetDefaultDisp")))
void Poker_SetDefaultDisp(int a0) {
    func_001DD340(a0);
    SetCustomIDNumberIndexed_1DD648(a0, 0, 0x32);
    SetCustomIDNumberIndexed_1DD648(a0, 1, 0x14);
    SetCustomIDNumberIndexed_1DD648(a0, 2, 0xF);
    SetCustomIDNumberIndexed_1DD648(a0, 3, 0xA);
    SetCustomIDNumberIndexed_1DD648(a0, 4, 0x8);
    SetCustomIDNumberIndexed_1DD648(a0, 5, 0x8);
    SetCustomIDNumberIndexed_1DD648(a0, 6, 0x3);
    SetCustomIDNumberIndexed_1DD648(a0, 7, 0x2);
}

__attribute__((section(".text.Poker_Main")))
void Poker_Main(int a0)
{
    int s1;
    int *s0;
    int *s3;
    int i = *(unsigned char *)(a0 + 0x3024);
    short off = *(short *)(D_003BE000 + i * 8);
    void (*fn)() = *(void (**)())(D_003BE000 + i * 8 + 4);
    fn(a0 + off);

    s3 = (int *)(a0 + 0x3004);
    s1 = 4;
    s0 = s3;
    do {
        if (*s0 != 0) {
            func_001D6E20(*s0);
        }
        s1 = s1 - 1;
        s0 = s0 + 1;
    } while (s1 >= 0);

    s0 = s3;
    s1 = 4;
    do {
        if (*s0 != 0) {
            func_001D6F30(*s0);
        }
        s1 = s1 - 1;
        s0 = s0 + 1;
    } while (s1 >= 0);

    func_001DD238(a0, GetTimerValue_1FA710(&D_00569B70));
    PokerId_Move(a0);
    PokerId__Trans(a0);
}
