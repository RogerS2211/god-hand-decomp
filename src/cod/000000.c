#include "include_asm.h"

/* ------------------------------------------------------------------ */
/* Externs unified across the 7-function D_0044BED0 cluster.          */
/* ------------------------------------------------------------------ */
extern unsigned char *PTR_DAT_003c23a4;  /* 0x003C23A4: pointer in .data */
extern char D_003C2555;                  /* 0x003C2555: 1-byte flag in .data */
extern int D_0044BED0;                   /* 0x0044BED0: first int of rodata table */
extern int D_005FEAC0;                   /* 0x005FEAC0: BSS word */
extern int D_00747A80;                   /* 0x00747A80: BSS word */
extern int D_00747A94;                   /* 0x00747A94: BSS word */
extern int D_00747A98;                   /* 0x00747A98: BSS word */


__attribute__((section(".text.func_0013C5C8")))
void func_0013C5C8(void *a0) {
    char *p = (char *)a0;
    *(int *)(p + 0x50) = 0;
    *(int *)(p + 0x54) = 0;
    *(int *)(p + 0x58) = 0;
    *(int *)(p + 0x5C) = 0;
    *(int *)(p + 0x60) = 0;
    *(int *)(p + 0x64) = 0;
    *(int *)(p + 0x68) = 0;
    *(int *)(p + 0x6C) = 0;
    *(short *)(p + 0x70) = 0;
    *(short *)(p + 0x72) = 0;
    p[0x74] = 0;
    p[0x75] = 0;
    p[0x76] = 0;
    p[0x77] = 0;
    p[0x78] = 0;
    p[0x79] = 0;
    p[0x7A] = 0;
    p[0x7B] = 0;  /* second-to-last -> delay slot */
    p[0x7C] = 0;  /* last -> scheduled first */
}

INCLUDE_ASM("nonmatching", func_00100000);

__attribute__((section(".text.func_0014E768")))
void func_0014E768(void) {

}

__attribute__((section(".text.func_0014E928")))
void func_0014E928(void) {

}

__attribute__((section(".text.func_0014E4C8")))
void func_0014E4C8(void) {}

__attribute__((section(".text.func_0014B638")))
unsigned char func_0014B638(unsigned char *arg0) { return arg0[0x2B1]; }

__attribute__((section(".text.func_0010BE10")))
void func_0010BE10(char *arg0) { arg0[0x2F4] = 0; }

__attribute__((section(".text.func_00134648")))
void func_00134648(int *arg0, int arg1) { *((int *)((char *)arg0 + 0x8)) = arg1; }

__attribute__((section(".text.func_0013E3F8")))
void func_0013E3F8(char *arg0) { arg0[0x104] = 0; }

__attribute__((section(".text.func_00133B98")))
void func_00133B98(void) {}

__attribute__((section(".text.func_001352F0")))
void func_001352F0(void) {}

__attribute__((section(".text.func_00138238")))
void func_00138238(void) {}

__attribute__((section(".text.func_0013C750")))
void func_0013C750(void) {}

__attribute__((section(".text.func_0013D148")))
void func_0013D148(void) {}

__attribute__((section(".text.func_0013E2F8")))
void func_0013E2F8(void) {}

__attribute__((section(".text.func_001415E0")))
void func_001415E0(void) {}

__attribute__((section(".text.func_00141620")))
void func_00141620(void) {}

__attribute__((section(".text.func_00146F90")))
void func_00146F90(void) {}

__attribute__((section(".text.func_00100318")))
void func_00100318(void) {}

/* The section attribute pins this function to the `.text.func_00100320`
 * slot the build-time lcf reserves for it (per-function .text sections
 * are needed for multi-carve TUs). */
__attribute__((section(".text.func_00100320")))
int func_00100320(void) { return 1; }

/* 10 matched candidates */
__attribute__((section(".text.func_00150128")))
void func_00150128(char *arg0, int arg1) {
    arg0[0x140] = arg1;
}

__attribute__((section(".text.func_001595E8")))
void func_001595E8(int *arg0, int arg1) {
    *((int *)((char *)arg0 + 0x424)) = arg1;
}

__attribute__((section(".text.func_001595F0")))
int func_001595F0(int *arg0) {
    return *((int *)((char *)arg0 + 0x424));
}

__attribute__((section(".text.func_0015F2A8")))
void func_0015F2A8(void) {}

__attribute__((section(".text.func_0015FB98")))
void func_0015FB98(void) {}

__attribute__((section(".text.func_0015FBA0")))
void func_0015FBA0(void) {}

__attribute__((section(".text.func_00161610")))
void func_00161610(void) {}

__attribute__((section(".text.func_00161618")))
void func_00161618(void) {}

__attribute__((section(".text.func_00161620")))
void func_00161620(void) {}

__attribute__((section(".text.func_00164978")))
void func_00164978(void) {}

__attribute__((section(".text.func_00366B80")))
void func_00366B80(char *a0, int a1, unsigned int a2) {
    signed char c = (signed char)a1;
    unsigned int rem = a2 & 0xF;
    a0 += a2;  /* advance a0 BEFORE the if check (always executes = in delay slot) */
    if (rem) {
        do {
            --a0;
            *a0 = c;
        } while (--rem);
    }
    a2 >>= 4;
    if (a2) {
        do {
            --a0; --a2;
            *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0; *a0 = c;
            --a0;
            *a0 = c;
        } while (a2);
    }
}

/* ====================================================================== */
/* 13 hand-decompiled function bodies                                     */
/* (integration-bug rolled back; manual re-merge here)                    */
/* ====================================================================== */

__attribute__((section(".text.func_002B1290")))
unsigned short func_002B1290(void) {
    return *(unsigned short *)(PTR_DAT_003c23a4 + 0xBEE);
}

__attribute__((section(".text.func_002B65F0")))
void func_002B65F0(void) {
    D_003C2555 = 1;
}

/* D_0044BED0 cluster — 7 byte-identical accessor functions */
__attribute__((section(".text.func_002BA4D8")))
void func_002BA4D8(char *arg0) {
    *(int **)(arg0 + 0x100) = &D_0044BED0;
}

__attribute__((section(".text.func_002BA580")))
void func_002BA580(char *arg0) {
    *(int **)(arg0 + 0x100) = &D_0044BED0;
}

__attribute__((section(".text.func_002BA6E8")))
void func_002BA6E8(char *arg0) {
    *(int **)(arg0 + 0x100) = &D_0044BED0;
}

__attribute__((section(".text.func_002BA818")))
void func_002BA818(char *arg0) {
    *(int **)(arg0 + 0x100) = &D_0044BED0;
}

__attribute__((section(".text.func_002BA8D0")))
void func_002BA8D0(char *arg0) {
    *(int **)(arg0 + 0x100) = &D_0044BED0;
}

__attribute__((section(".text.func_002BA938")))
void func_002BA938(char *arg0) {
    *(int **)(arg0 + 0x100) = &D_0044BED0;
}

__attribute__((section(".text.func_002BAA30")))
void func_002BAA30(char *arg0) {
    *(int **)(arg0 + 0x100) = &D_0044BED0;
}

__attribute__((section(".text.func_002BF780")))
void func_002BF780(int *arg0) {
    D_00747A80 = arg0[0x70 / 4];
}

__attribute__((section(".text.func_002C23E0")))
int func_002C23E0(int arg0) {
    D_005FEAC0 = arg0;
    return 0;
}

__attribute__((section(".text.func_002DB6B0")))
int func_002DB6B0(void) {
    return D_00747A94;
}

__attribute__((section(".text.func_002DB6C0")))
int func_002DB6C0(void) {
    return D_00747A98;
}

__attribute__((section(".text.func_00138BB8")))
void func_00138BB8(void) {}

__attribute__((section(".text.func_00173900")))
unsigned char func_00173900(unsigned char *a0) {
    return a0[0x54];
}

__attribute__((section(".text.func_00173998")))
void func_00173998(int *a0, int a1) {
    *(int *)((char *)a0 + 0x50) = a1;
}

__attribute__((section(".text.func_00178978")))
void func_00178978(void) {}

__attribute__((section(".text.func_0017B810")))
unsigned char func_0017B810(unsigned char *a0) {
    return a0[0x601];
}

__attribute__((section(".text.func_0017B818")))
int func_0017B818(char *a0) {
    return (unsigned char)a0[0x600];
}

__attribute__((section(".text.func_0017E2F0")))
void func_0017E2F0(void) {}

__attribute__((section(".text.func_0017E7D0")))
unsigned char func_0017E7D0(unsigned char *a0) {
    return a0[0x601];
}

__attribute__((section(".text.func_0017EDC8")))
void func_0017EDC8(void) {}

__attribute__((section(".text.func_0017F1C8")))
void func_0017F1C8(void) {
}

__attribute__((section(".text.func_0017F218")))
unsigned char func_0017F218(unsigned char *a0) {
    return a0[0x600];
}

__attribute__((section(".text.func_0017FAF0")))
unsigned char func_0017FAF0(unsigned char *a0) {
    return a0[0x764];
}

__attribute__((section(".text.func_0017FD78")))
void func_0017FD78(void) {}

__attribute__((section(".text.func_00180688")))
int func_00180688(char *a0) {
    return *(int *)(a0 + 0xA24);
}

__attribute__((section(".text.func_00180690")))
unsigned char func_00180690(unsigned char *a0) {
    return a0[0xA28];
}

__attribute__((section(".text.func_001812B0")))
void func_001812B0(void) {}

__attribute__((section(".text.func_001815A8")))
void func_001815A8(void) {}

__attribute__((section(".text.func_001815D0")))
unsigned char func_001815D0(unsigned char *a0) {
    return a0[0x770];
}

__attribute__((section(".text.func_001815D8")))
unsigned char func_001815D8(unsigned char *a0) {
    return a0[0x771];
}

__attribute__((section(".text.func_00186670")))
unsigned char func_00186670(unsigned char *a0) {
    return a0[0x65B];
}

__attribute__((section(".text.func_001B35C8")))
void func_001B35C8(void) {}

__attribute__((section(".text.func_001B38C8")))
void func_001B38C8(void) {}

__attribute__((section(".text.func_001B80A8")))
void func_001B80A8(void) {
}

__attribute__((section(".text.func_001B8640")))
unsigned char func_001B8640(unsigned char *a0) {
    return a0[0x600];
}

__attribute__((section(".text.func_001B8718")))
unsigned char func_001B8718(unsigned char *a0) {
    return a0[0x601];
}

__attribute__((section(".text.func_001BD778")))
void func_001BD778(unsigned char *a0) {
    a0[0x775] = 0;
}

__attribute__((section(".text.func_001BDD90")))
unsigned char func_001BDD90(unsigned char *a0) {
    return a0[0x774];
}

__attribute__((section(".text.func_001BDD98")))
unsigned char func_001BDD98(unsigned char *a0) {
    return a0[0x775];
}

__attribute__((section(".text.func_001BE060")))
void func_001BE060(void) {}

__attribute__((section(".text.func_001BEA18")))
void func_001BEA18(void) {}

__attribute__((section(".text.func_001BFCE0")))
void func_001BFCE0(void) {
}

__attribute__((section(".text.func_001C2370")))
void func_001C2370(char *a0) {
    *(int *)(a0 + 0x630) = 0;
}

__attribute__((section(".text.func_001C5F40")))
int func_001C5F40(void) {
    return 1;
}

__attribute__((section(".text.func_001D0C10")))
int func_001D0C10(char *a0) {
    return *(int *)(a0 + 0x68C);
}

__attribute__((section(".text.func_001D0C18")))
void func_001D0C18(int *a0) {
    *(int *)((char *)a0 + 0x68C) = 0;
}

__attribute__((section(".text.func_001D4B70")))
void func_001D4B70(void) {}

__attribute__((section(".text.func_001DCE60")))
void func_001DCE60(void) {}

__attribute__((section(".text.func_001DEBE8")))
void func_001DEBE8(char *a0, int a1) {
    a0[0x56] = (char)a1;
}

__attribute__((section(".text.func_001ED488")))
void func_001ED488(char *a0, int a1) {
    *(int *)(a0 + 0x162C) = a1;
}

__attribute__((section(".text.func_001EF740")))
void func_001EF740(void) {}

__attribute__((section(".text.func_00194550")))
void func_00194550(void) {
}

__attribute__((section(".text.func_00195FE0")))
void func_00195FE0(void) {}

__attribute__((section(".text.func_001A4F10")))
unsigned char func_001A4F10(unsigned char *a0) {
    return a0[0x761];
}

__attribute__((section(".text.func_001A4F18")))
unsigned int func_001A4F18(unsigned char *a0) {
    return a0[0x760];
}

__attribute__((section(".text.func_001A4F20")))
void func_001A4F20(char *a0, int a1) {
    a0[0x763] = (char)a1;
}

__attribute__((section(".text.func_001A4F28")))
void func_001A4F28(unsigned char *a0, int a1) {
    ((unsigned char *)a0)[0x762] = (unsigned char)a1;
}

__attribute__((section(".text.func_001A4F30")))
void func_001A4F30(char *a0, int a1) {
    *(int *)(a0 + 0x790) = a1;
}

__attribute__((section(".text.func_001A50F0")))
int func_001A50F0(int a0) {
    return a0 + 0x780;
}

__attribute__((section(".text.func_001A50F8")))
int func_001A50F8(int a0) {
    return a0 + 0x780;
}

__attribute__((section(".text.func_001A6550")))
void func_001A6550(void) {}

__attribute__((section(".text.func_001A80F0")))
void func_001A80F0(int *a0, int a1) {
    *(int *)((char *)a0 + 0x628) = a1;
}

__attribute__((section(".text.func_001A8680")))
void func_001A8680(void) {}

__attribute__((section(".text.func_001A8838")))
void func_001A8838(void) {}

__attribute__((section(".text.func_001A97E0")))
void func_001A97E0(void) {
}

__attribute__((section(".text.func_001ADA78")))
unsigned char func_001ADA78(unsigned char *a0) {
    return a0[0x60D];
}

__attribute__((section(".text.func_001ADA80")))
unsigned char func_001ADA80(unsigned char *a0) {
    return a0[0x60E];
}

__attribute__((section(".text.func_001B0978")))
void func_001B0978(void) {}

__attribute__((section(".text.func_001B0AE0")))
void func_001B0AE0(void) {}

__attribute__((section(".text.func_001B1598")))
void func_001B1598(void) {}

__attribute__((section(".text.func_001B15A0")))
void func_001B15A0(void) {}

__attribute__((section(".text.func_001F0490")))
void func_001F0490(void) {
}

__attribute__((section(".text.func_001F05F0")))
void func_001F05F0(void) {
}

__attribute__((section(".text.func_001F07B8")))
void func_001F07B8(void) {}

__attribute__((section(".text.func_001F0870")))
void func_001F0870(void) {}

__attribute__((section(".text.func_001F0A20")))
void func_001F0A20(void) {
}

__attribute__((section(".text.func_001F0E10")))
void func_001F0E10(void) {
}

__attribute__((section(".text.func_001F1140")))
void func_001F1140(void) {}

__attribute__((section(".text.func_001F15B8")))
void func_001F15B8(void) {}

extern int D_003C80A8;

__attribute__((section(".text.func_00325610")))
int func_00325610(void) {
    return D_003C80A8;
}

extern unsigned char D_00756080[];

__attribute__((section(".text.func_003306C8")))
unsigned char *func_003306C8(void) {
    return D_00756080;
}

extern int D_003D9DD8;

__attribute__((section(".text.func_003331C0")))
void func_003331C0(int a0) {
    D_003D9DD8 = a0;
}

int D_003DA394;

__attribute__((section(".text.func_00335348")))
void func_00335348(int a0) {
    D_003DA394 = a0;
}

extern int D_003E9D5C;

__attribute__((section(".text.func_0033C718")))
int func_0033C718(void) {
    return D_003E9D5C;
}

extern unsigned char D_003EC7E0[];

__attribute__((section(".text.func_003452B0")))
void *func_003452B0(void) {
    return D_003EC7E0;
}

extern int D_003EE078;

__attribute__((section(".text.func_003463F8")))
int func_003463F8(void) {
    return D_003EE078;
}

extern int D_003EE2C0;

__attribute__((section(".text.func_0034AFE0")))
int func_0034AFE0(void) {
    return D_003EE2C0;
}

extern int D_003EE2F4;

__attribute__((section(".text.func_00356348")))
void func_00356348(int a0) {
    D_003EE2F4 = a0;
}

int D_003EE2BC;

__attribute__((section(".text.func_00358A28")))
void func_00358A28(int a0) {
    D_003EE2BC = a0;
}


__attribute__((section(".text.func_00358A38")))
int func_00358A38(void) {
    return D_003EE2BC;
}

extern unsigned char D_00459FA8[];

__attribute__((section(".text.func_0035F8A8")))
unsigned char *func_0035F8A8(void) {
    return D_00459FA8;
}

int D_003EE34C;

__attribute__((section(".text.func_0035FC18")))
void func_0035FC18(int a0) {
    D_003EE34C = a0;
}


__attribute__((section(".text.func_0035FC28")))
int func_0035FC28(void) {
    return D_003EE34C;
}

extern int D_003EE804;

__attribute__((section(".text.func_00360720")))
int func_00360720(void) {
    return D_003EE804;
}

extern unsigned char D_0045A1B0[];

__attribute__((section(".text.func_00360790")))
unsigned char *func_00360790(void) {
    return D_0045A1B0;
}

long long D_003EEA70;

__attribute__((section(".text.func_00360C58")))
long long func_00360C58(void) {
    return D_003EEA70;
}

long long D_003EEA70;

__attribute__((section(".text.func_00360C80")))
void func_00360C80(long long a0) {
    D_003EEA70 = a0;
}

extern char D_003EEA90[];

__attribute__((section(".text.func_00360D18")))
char *func_00360D18(void) {
    return D_003EEA90;
}

extern char D_003EEA98[];

__attribute__((section(".text.func_00365EB0")))
void *func_00365EB0(void) {
    return D_003EEA98;
}

extern int D_003F1FF0;

__attribute__((section(".text.func_0036CCA8")))
int func_0036CCA8(void) {
    return D_003F1FF0;
}

extern unsigned char D_0045A478[];

__attribute__((section(".text.func_0036D0E8")))
unsigned char *func_0036D0E8(void) {
    return D_0045A478;
}

extern int D_0076A7A4;

__attribute__((section(".text.func_003756F0")))
int func_003756F0(void) {
    return D_0076A7A4;
}

extern unsigned char D_003F8560[];

__attribute__((section(".text.func_00395388")))
unsigned char *func_00395388(void) {
    return D_003F8560;
}

int *PTR_DAT_003fa62c;

__attribute__((section(".text.func_003A4FB8")))
int func_003A4FB8(void) {
    return (int)PTR_DAT_003fa62c;
}

extern unsigned char D_0045FB80[];

__attribute__((section(".text.func_003AD118")))
unsigned char *func_003AD118(void) {
    return D_0045FB80;
}

extern int D_003C80A4;

__attribute__((section(".text.func_00325620")))
int func_00325620(void) {
    return D_003C80A4 != 0;
}

typedef signed char signed char;
typedef unsigned char unsigned char;
typedef signed short short;
typedef unsigned short unsigned short;
typedef signed int int;
typedef unsigned int unsigned int;
typedef signed long long long long;
typedef unsigned long long unsigned long long;
typedef float f32;
typedef double f64;
typedef int M2C_UNK;
typedef signed char M2C_UNK8;
typedef short M2C_UNK16;
typedef int M2C_UNK32;
typedef long long M2C_UNK64;
typedef struct CGUnk_0013C5C8
{
  unsigned char unk[0xA0];
} CGUnk_0013C5C8_t;
typedef struct CGUnk_0010B5C8
{
  unsigned char unk[0x300];
} CGUnk_0010B5C8_t;
typedef struct CGListNode_001346C8
{
  unsigned char unk[0x20];
} CGListNode_001346C8_t;
typedef struct CGUnk_0013E3F8
{
  unsigned char unk[0x110];
} CGUnk_0013E3F8_t;
typedef struct CGUnk_00134648
{
  unsigned char unk[0x10];
} CGUnk_00134648_t;
typedef struct CGObj293
{
  unsigned char unk[0x590];
} CGObj293_t;
extern unsigned char D_0041EDF0[];
extern unsigned char D_00466448[];
extern unsigned char cMcLoaderState[0x1108];
extern unsigned char D_0044A7B0[];
extern int D_786768;
extern int D_786778;
extern int D_0045D350;
extern int D_0045D360;
extern int D_00460DB0;
typedef struct CGObj38B8
{
  unsigned char unk[0x60];
} CGObj38B8_t;
extern volatile int D_003D848C;
__attribute__((section(".text.func_003313E0")))
int func_003313E0(void)
{
  return D_003D848C;
}

extern volatile int D_003D8488;
__attribute__((section(".text.func_003313F0")))
void func_003313F0(int a0)
{
  D_003D8488 = a0;
}


__attribute__((section(".text.func_0034B290")))
int func_0034B290(int a0) {
    D_003EE2C0 = a0;
    return 0;
}

extern int D_0076B080;

__attribute__((section(".text.func_003754F0")))
void func_003754F0(void *arg0) {
    D_0076B080 = *(int *)((char *)arg0 + 0xA4);
}

extern char D_003C2554;

__attribute__((section(".text.func_002B6598")))
void func_002B6598(void) {
    D_003C2555 = 0;
    D_003C2554 = 0;
}

extern int D_00747A44;

__attribute__((section(".text.func_002BE968")))
int *func_002BE968(int *arg0) {
    *arg0 = D_00747A44;
    return arg0;
}

extern void *D_0044D388;

__attribute__((section(".text.func_002D9E18")))
void *func_002D9E18(void **a0) {
    *a0 = &D_0044D388;
    return a0;
}

extern int D_00451008;

__attribute__((section(".text.func_0031F360")))
void *func_0031F360(void **a0) {
    *a0 = &D_00451008;
    return a0;
}

extern int D_00451020;

__attribute__((section(".text.func_0031F3F8")))
void *func_0031F3F8(void *arg0) {
    *(int **)arg0 = &D_00451020;
    return arg0;
}

extern int D_00451270;

__attribute__((section(".text.func_00321848")))
void *func_00321848(void **a0) {
    *a0 = &D_00451270;
    return a0;
}

extern int D_00451288;

__attribute__((section(".text.func_003218E0")))
void *func_003218E0(void *a0) {
    *(int **)a0 = &D_00451288;
    return a0;
}

int D_003D1410;
int D_003D1414;

__attribute__((section(".text.func_0032AB58")))
void func_0032AB58(int a0) {
    D_003D1410 = a0;
    D_003D1414 = a0;
}

extern int D_003D90D4;
extern int D_003D90D8;

__attribute__((section(".text.func_003329D0")))
void func_003329D0(int a0, int a1) {
    D_003D90D4 = a0;
    D_003D90D8 = a1;
}

extern int D_003D9F6C;
extern int D_003D9F70;

__attribute__((section(".text.func_00334230")))
void func_00334230(int a0, int a1) {
    D_003D9F6C = a0;
    D_003D9F70 = a1;
}

extern int D_003DECFC;
extern int D_003DED00;

__attribute__((section(".text.func_003364F8")))
void func_003364F8(int a0, int a1) {
    D_003DECFC = a0;
    D_003DED00 = a1;
}

extern int D_007588A0[2];

__attribute__((section(".text.func_0033BC18")))
void func_0033BC18(int a0, int a1) {
    D_007588A0[0] = a0;
    D_007588A0[1] = a1;
}

struct {
    int x;
    int y;
} D_007588A8;

__attribute__((section(".text.func_0033BC30")))
void func_0033BC30(int a0, int a1) {
    D_007588A8.x = a0;
    D_007588A8.y = a1;
}

extern int D_007588C0[2];

__attribute__((section(".text.func_0033BF88")))
void func_0033BF88(int a0, int a1) {
    D_007588C0[0] = a0;
    D_007588C0[1] = a1;
}

extern int D_007588C8[2];

__attribute__((section(".text.func_0033BFA0")))
void func_0033BFA0(int a0, int a1) {
    D_007588C8[0] = a0;
    D_007588C8[1] = a1;
}

extern int D_003EC454;
extern int D_003EC458;

__attribute__((section(".text.func_00340438")))
void func_00340438(int a0, int a1) {
    D_003EC454 = a0;
    D_003EC458 = a1;
}

extern unsigned char D_003EE088[];

__attribute__((section(".text.func_00348920")))
void *func_00348920(int a0) {
    return (void *)(D_003EE088 + a0 * 8);
}

extern int D_003EE340[2];

__attribute__((section(".text.func_0035F958")))
void func_0035F958(int a0, int a1) {
    D_003EE340[0] = a0;
    D_003EE340[1] = a1;
}

extern unsigned char D_003BAFE0[];

__attribute__((section(".text.func_00372C68")))
void *func_00372C68(void *arg0) {
    *(void **)((unsigned char *)arg0 + 0x80) = (void *)D_003BAFE0;
    return arg0;
}

extern int D_003FC7AC;
extern int D_003FC7B0;

__attribute__((section(".text.func_003B9D98")))
void func_003B9D98(int a0, int a1) {
    D_003FC7AC = a0;
    D_003FC7B0 = a1;
}


__attribute__((section(".text.func_002B8978")))
unsigned int func_002B8978(void) {
    unsigned int v = D_00747A80 & 0x10000000U;
    return (unsigned int)(0U < v);
}

extern int D_00450FF0;

__attribute__((section(".text.func_0031F2A8")))
int *func_0031F2A8(int *a0, int a1) {
    a0[0] = a1;
    a0[1] = (int)&D_00450FF0;
    return a0;
}

extern int D_00451038;

__attribute__((section(".text.func_0031F488")))
int *func_0031F488(int *a0, int a1) {
    a0[0] = a1;
    a0[1] = (int)&D_00451038;
    return a0;
}

extern int D_003EB308[];

__attribute__((section(".text.func_00324808")))
int func_00324808(int a0) {
    return D_003EB308[a0] + 0x10;
}

extern long long D_003C8100;

__attribute__((section(".text.func_00324E98")))
void func_00324E98(void) {
    D_003C8100 += 1;
}

extern int D_003D04CC;

__attribute__((section(".text.func_003284A0")))
int func_003284A0(void) {
    return ++D_003D04CC;
}

int D_003D1428;

__attribute__((section(".text.func_0032A148")))
int func_0032A148(void) {
    return ++D_003D1428;
}

int D_003D84B0;

__attribute__((section(".text.func_003320E0")))
void func_003320E0(void) {
    D_003D84B0 += 1;
}


__attribute__((section(".text.func_00360C40")))
int func_00360C40(void) {
    return (unsigned long long)D_003EEA70 < 2;
}

extern int PTR_DAT_003c4f00;

__attribute__((section(".text.func_00321218")))
int func_00321218(int a0) {
    unsigned long v0 = PTR_DAT_003c4f00;
    int new_var;
    new_var = v0;
    PTR_DAT_003c4f00 = a0;
    return new_var;
}

extern int D_003E3A80;

__attribute__((section(".text.func_00338960")))
int func_00338960(void) {
    return ++D_003E3A80;
}


__attribute__((section(".text.func_00338978")))
void func_00338978(void) {
    D_003E3A80--;
}

int D_003EC450;

__attribute__((section(".text.func_00340520")))
int func_00340520(void) {
    return --D_003EC450;
}

extern int D_003FC50C;

__attribute__((section(".text.func_003B9D68")))
int func_003B9D68(void) {
    return ++D_003FC50C;
}


__attribute__((section(".text.func_003B9D80")))
int func_003B9D80(void) {
    return --D_003FC50C;
}

typedef struct {
    unsigned char unk[0x5D8];
    int field_5D8;
    unsigned char pad[4];
    int field_5E0;
} CGUnk_007474A0_t;

extern CGUnk_007474A0_t D_007474A0;

__attribute__((section(".text.func_001615D0")))
void func_001615D0(unsigned char *a0) {
    *(int *)(a0 + 0x68) = D_007474A0.field_5D8;
    *(int *)(a0 + 0x6C) = D_007474A0.field_5E0;
}

extern unsigned char *PTR_DAT_003bd6e8;

__attribute__((section(".text.func_001F75B0")))
void func_001F75B0(void) {
    unsigned char *base = PTR_DAT_003bd6e8 + 0x1380;
    base[0x94] = base[0x94] & 0xFE;
}

extern int D_00747A0C;

__attribute__((section(".text.func_001F9E90")))
void func_001F9E90(int **a0) {
    int *ptr = *a0;
    if (ptr == 0) return;
    *(int *)((char *)ptr + 0x178) = D_00747A0C;
}


__attribute__((section(".text.func_001F9EB0")))
void func_001F9EB0(int **a0) {
    int *ptr = *a0;
    if (ptr != 0) {
        D_00747A0C = *(int *)((char *)ptr + 0x178);
    }
}


__attribute__((section(".text.func_002B1270")))
int func_002B1270(int a0, unsigned char *a1) {
    unsigned int idx = (unsigned int)(*(unsigned short *)(a1 + 2)) << 2;
    return *(int *)((unsigned char *)PTR_DAT_003c23a4 + idx + 0xBDC);
}

__attribute__((section(".text.func_003951B0")))
void func_003951B0(void) {
    __asm__ volatile("nop; nop");
}

__attribute__((section(".text.func_003951C0")))
void func_003951C0(void) {
    __asm__ volatile("nop; nop");
}

__attribute__((section(".text.func_003951D0")))
void func_003951D0(void) {
    __asm__ volatile("nop; nop");
}

__attribute__((section(".text.Obj0000_Set_Byte_54")))
__attribute__((section(".text.Obj0000_Set_Byte_54")))
void Obj0000_Set_Byte_54(char *arg0, int arg1) {
    arg0[0x54] = arg1;
}

extern unsigned char D_0061B670;

__attribute__((section(".text.Obj0000_Get_Byte_D_0061B670")))
__attribute__((section(".text.Obj0000_Get_Byte_D_0061B670")))
int Obj0000_Get_Byte_D_0061B670(void) {
    return D_0061B670;
}

__attribute__((section(".text.Obj0000_Set_Byte_2F5_If_Field_618_GE_29")))
void Obj0000_Set_Byte_2F5_If_Field_618_GE_29(CGUnk_0010B5C8_t *arg0)
{
  if ((*((int *) (((unsigned char *) arg0) + 0x618))) >= 0x29)
  {
    *(((unsigned char *) arg0) + 0x2F7) = 0;
 do { *(((unsigned char *) arg0) + 0x2F5) = 1; *(((unsigned char *) arg0) + 0x2F6) = 0; } while (0);
  }
}

__attribute__((section(".text.Obj0000_Clear_Field_28_And_Ptr4_Field_30_34")))
__attribute__((section(".text.Obj0000_Clear_Field_28_And_Ptr4_Field_30_34")))
void Obj0000_Clear_Field_28_And_Ptr4_Field_30_34(char *a0) {
    char *ptr = *(char * volatile *)(a0 + 0x4);
    if (ptr == 0) return;
    *(int *)(a0 + 0x28) = 0;
    *(int *)(ptr + 0x30) = 0;
    ptr = *(char * volatile *)(a0 + 0x4);
    *(int *)(ptr + 0x34) = 0;
}

extern int D_003D8408;
void func_003302B0(void *, void *, int);

__attribute__((section(".text.Tramp_003302B0_003302E0")))
__attribute__((section(".text.Tramp_003302B0_003302E0")))
void Tramp_003302B0_003302E0(void *a0) {
    func_003302B0(&D_003D8408, a0, 0);
}

__attribute__((section(".text.Tramp_003A52F0_00333AD8")))
__attribute__((section(".text.Tramp_003A52F0_00333AD8")))
void Tramp_003A52F0_00333AD8(void) {
    extern void func_003A52F0(void *a0, int a1, int a2);
    extern char D_003D9DC0[];
    func_003A52F0(D_003D9DC0, 0, 0x10);
}

extern void (*D_003E9D30)(void);

__attribute__((section(".text.Tramp_003E9D30_0033C4C0")))
__attribute__((section(".text.Tramp_003E9D30_0033C4C0")))
void Tramp_003E9D30_0033C4C0(void) {
    D_003E9D30();
}

typedef struct CGUnk_00343E00 { unsigned char unk[0x1D0]; } CGUnk_00343E00_t;

extern void func_003395A0(int a0, int a1, int a2);

__attribute__((section(".text.Obj0000_Call_003395A0_Field_1C4_1C8_1CC")))
void Obj0000_Call_003395A0_Field_1C4_1C8_1CC(CGUnk_00343E00_t *arg0) {
    int a0 = *(int *)((unsigned char *)arg0 + 0x1C4);
    int a1 = *(int *)((unsigned char *)arg0 + 0x1C8);
    int a2 = *(int *)((unsigned char *)arg0 + 0x1CC);
    func_003395A0(a0, a1, a2);
}

extern int func_00359EC0(int);

__attribute__((section(".text.Obj0000_Call_00359EC0_Field_3C")))
int Obj0000_Call_00359EC0_Field_3C(int *a0) {
    int v0 = 0;
    if (a0 != 0) {
        v0 = *(int *)((char *)a0 + 0x3C);
    }
    return func_00359EC0(v0);
}

extern int func_0035A128(int);

__attribute__((section(".text.Obj0000_Call_0035A128_Field_3C")))
int Obj0000_Call_0035A128_Field_3C(unsigned char *arg0) {
    int v0;
    if (arg0 == 0) {
        v0 = 0;
    } else {
        v0 = *(int *)(arg0 + 0x3C);
    }
    return func_0035A128(v0);
}

extern void func_00328C80(void *);

__attribute__((section(".text.Obj0000_Call_00328C80_If_NonNull")))
void Obj0000_Call_00328C80_If_NonNull(void *arg0) {
    if (arg0 == 0) {
        return;
    }
    func_00328C80(arg0);
}

extern void func_0034C378();

__attribute__((section(".text.Obj0000_Call_0034C378_Field_1F44")))
void Obj0000_Call_0034C378_Field_1F44(unsigned char *a0, void *a1, void *a2)
{
    func_0034C378(a0, *(int *)(a0 + 0x1F44), a1, a2);
}

__attribute__((section(".text.Obj0000_Set_Field_E48_If_Field_E6C_NE_MAX")))
__attribute__((section(".text.Obj0000_Set_Field_E48_If_Field_E6C_NE_MAX")))
void Obj0000_Set_Field_E48_If_Field_E6C_NE_MAX(unsigned char *a0) {
    unsigned char *ptr = a0 + 0xE48;
    if (*(int *)(ptr + 0x24) == 0x7FFFFFFF) return;
    *(int *)(ptr) = 1;
}

__attribute__((section(".text.Obj0000_Pack_U64_Fields")))
void Obj0000_Pack_U64_Fields(unsigned long long *a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    *a0 = ((unsigned long long)a1 << 32) | ((unsigned long long)a2 << 28) | (unsigned long long)a3;
}

__attribute__((section(".text.Obj0000_Get_Field_44_LT_1_If_Field_48_In_1_4")))
__attribute__((section(".text.Obj0000_Get_Field_44_LT_1_If_Field_48_In_1_4")))
int Obj0000_Get_Field_44_LT_1_If_Field_48_In_1_4(unsigned char *a0) {
    int v1 = *(int *)(a0 + 0x48);
    if ((unsigned int)(v1 - 1) >= 4) {
        return 1;
    }
    return (unsigned int)*(int *)(a0 + 0x44) < 1;
}

extern int D_00766CD8;

__attribute__((section(".text.Obj0000_Set_D_00766CD8_Check_Field_0_NE_1")))
__attribute__((section(".text.Obj0000_Set_D_00766CD8_Check_Field_0_NE_1")))
int Obj0000_Set_D_00766CD8_Check_Field_0_NE_1(int *a0) {
    int v1;
    int v0;
    D_00766CD8 = (int)a0;
    if (a0 == 0) {
        return -1;
    }
    v1 = *a0 ^ 1;
    v0 = -1;
    if (v1 != 0) {
        v0 = 0;
    }
    return v0;
}

__attribute__((section(".text.Obj0000_Set_Field_3BC_Triple")))
__attribute__((section(".text.Obj0000_Set_Field_3BC_Triple")))
void Obj0000_Set_Field_3BC_Triple(unsigned char *a0, int a1, int a2, int a3, int a4) {
    int *p = (int *)(a0 + 0x3BC + a1 * 12);
    p[0] = a2;
    p[1] = a3;
    p[2] = a4;
}

__attribute__((section(".text.Tramp_003356B0_00335610")))
__attribute__((section(".text.Tramp_003356B0_00335610")))
void Tramp_003356B0_00335610(int a0, int a1) {
    func_003356B0(a0, a1, 0, 0, 0xFFFFF);
}

extern void *D_00766D44;

__attribute__((section(".text.Obj0000_Set_D_00766D44_Check_Field_188_NE_2")))
__attribute__((section(".text.Obj0000_Set_D_00766D44_Check_Field_188_NE_2")))
int Obj0000_Set_D_00766D44_Check_Field_188_NE_2(int *a0) {
    D_00766D44 = (void *)a0;
    if (a0 == 0) {
        return -1;
    }
    return (*(int *)((char *)a0 + 0x188) ^ 2) == 0 ? 0 : -1;
}

extern int func_0036CD98(int);

__attribute__((section(".text.Obj0000_Get_Field_3B4_Via_func_0036CD98")))
int Obj0000_Get_Field_3B4_Via_func_0036CD98(unsigned char *a0) {
    int v0 = 0;
    if (a0 != 0) {
        v0 = *(int *)(a0 + 0x3B4);
    }
    return func_0036CD98(v0);
}

extern int *D_0076A5D8;

__attribute__((section(".text.Obj0000_Set_D_0076A5D8_Check_Field_0_EQ_2")))
__attribute__((section(".text.Obj0000_Set_D_0076A5D8_Check_Field_0_EQ_2")))
int Obj0000_Set_D_0076A5D8_Check_Field_0_EQ_2(int *a0) {
    int v1;
    D_0076A5D8 = (int *)a0;
    if (a0 == 0) {
        return -1;
    }
    v1 = *a0 ^ 0x2;
    return v1 == 0 ? 0 : -1;
}

__attribute__((section(".text.Obj0000_Set_Field_11C_Triple")))
__attribute__((section(".text.Obj0000_Set_Field_11C_Triple")))
void Obj0000_Set_Field_11C_Triple(unsigned char *a0, int a1, int a2, int a3, int a4) {
    int *entry = (int *)(a0 + 0x11C + a1 * 12);
    entry[0] = a2;
    entry[1] = a3;
    entry[2] = a4;
}

typedef struct CGUnk_00180310
{
  unsigned char unk[0xA28];
} CGUnk_00180310_t;
__attribute__((section(".text.Obj0000_Set_Bytes_2F4_If_Field_A24_NE_1")))
void Obj0000_Set_Bytes_2F4_If_Field_A24_NE_1(CGUnk_00180310_t *a0)
{
  int v0 = *((int *) (((unsigned char *) a0) + 0xA24));
  if (v0 == 1)
  {
    return;
  }
  a0->unk[0x2F4] = 1;
  a0->unk[0x2F5] = 0;
  a0->unk[0x2F6] = 0;
  a0->unk[0x2F7] = 0;
}

__attribute__((section(".text.Obj0000_Set_Bytes_2F4_2F7_2F5_2F6_If_Field_A24_NE_2")))
void Obj0000_Set_Bytes_2F4_2F7_2F5_2F6_If_Field_A24_NE_2(unsigned char *a0)
{
  int new_var;
  new_var = *((int *) (a0 + 0xA24));
  if (new_var == 2)
  {
    return;
  }
  a0[0x2F4] = 2;
 do { a0[0x2F7] = 0; } while (0);
  a0[0x2F5] = 0;
  a0[0x2F6] = 0;
}

__attribute__((section(".text.Obj0000_Set_Short_88_If_LT_1000")))
void Obj0000_Set_Short_88_If_LT_1000(void *a0, short a1) {
    if ((unsigned short)a1 < 1000) {
        *(short *)((signed char *)(*(void **)a0) + 0x88) = a1;
    }
}

__attribute__((section(".text.Obj0000_Set_D_003FAE30_Field_10_Zero")))
__attribute__((section(".text.Obj0000_Set_D_003FAE30_Field_10_Zero")))
void Obj0000_Set_D_003FAE30_Field_10_Zero(void) {
    extern char D_003FAE30[];
    *(int *)(D_003FAE30 + 0x10) = 0;
}

__attribute__((section(".text.Tramp_001F7DF8_00101E28")))
__attribute__((section(".text.Tramp_001F7DF8_00101E28"))) void Tramp_001F7DF8_00101E28(void)
{
 do { func_001F7DF8(); } while (0);
}

__attribute__((section(".text.Tramp_func_0014EA50_0010B760")))
__attribute__((section(".text.Tramp_func_0014EA50_0010B760"))) void Tramp_func_0014EA50_0010B760(void)
{
 do { func_0014EA50(); } while (0);
}

__attribute__((section(".text.Tramp_func_0014EFA8_0012BBE0")))
void Tramp_func_0014EFA8_0012BBE0(void)
{
 do { func_0014EFA8(); } while (0);
}

__attribute__((section(".text.Tramp_func_002AAC28_0013C508")))
__attribute__((section(".text.Tramp_func_002AAC28_0013C508"))) void Tramp_func_002AAC28_0013C508(void)
{
 do { func_002AAC28(); } while (0);
}

__attribute__((section(".text.Tramp_func_0030A548_00147528")))
__attribute__((section(".text.Tramp_func_0030A548_00147528"))) void Tramp_func_0030A548_00147528(void)
{
  func_0030A548();
 do { } while (0);
}

__attribute__((section(".text.Tramp_func_0030A2E0_00147548")))
void func_0030A2E0(void);
__attribute__((section(".text.Tramp_func_0030A2E0_00147548"))) void Tramp_func_0030A2E0_00147548(void)
{
  func_0030A2E0();
 do { } while (0);
}

__attribute__((section(".text.Tramp_func_0030A2B0_001508D8")))
__attribute__((section(".text.Tramp_func_0030A2B0_001508D8"))) void Tramp_func_0030A2B0_001508D8(void)
{
  func_0030A2B0();
 do { } while (0);
}

__attribute__((section(".text.func_0015B080")))
void func_0015B080(void)
{
  func_0015B0F0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_0015B0C0_0015B0A0")))
void Tramp_func_0015B0C0_0015B0A0(void)
{
 do { func_0015B0C0(); } while (0);
}

__attribute__((section(".text.func_00161288")))
__attribute__((section(".text.func_00161288"))) void func_00161288(unsigned char *a0)
{
 do { func_0015FD18(a0, *((int *) (0x48 + a0))); } while (0);
}

__attribute__((section(".text.func_001612A8")))
__attribute__((section(".text.func_001612A8")))
void func_001612A8(void)
{
  func_0015FF10();
  do { } while (0);
}

__attribute__((section(".text.func_00161970")))
__attribute__((section(".text.func_00161970")))
void func_00161970(void)
{
  func_002AAC28();
  do { } while (0);
}

__attribute__((section(".text.func_00161BB0")))
__attribute__((section(".text.func_00161BB0")))
void func_00161BB0(void)
{
  func_001614D0();
  do { } while (0);
}

__attribute__((section(".text.func_00162278")))
__attribute__((section(".text.func_00162278")))
void func_00162278(void)
{
  func_002AAC28();
  do { } while (0);
}

__attribute__((section(".text.func_00166618")))
__attribute__((section(".text.func_00166618")))
void func_00166618(void)
{
  func_001614D0();
  do { } while (0);
}

__attribute__((section(".text.func_001673B0")))
__attribute__((section(".text.func_001673B0")))
void func_001673B0(void)
{
  func_001614D0();
  do { } while (0);
}

__attribute__((section(".text.func_001682A8")))
__attribute__((section(".text.func_001682A8")))
void func_001682A8(void)
{
  func_002AAC28();
  do { } while (0);
}

__attribute__((section(".text.func_0016F5E8")))
__attribute__((section(".text.func_0016F5E8")))
void func_0016F5E8(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Obj0000_Set_Short_202")))
__attribute__((section(".text.Obj0000_Set_Short_202")))
void Obj0000_Set_Short_202(unsigned char *a0)
{
  do { func_0016B1F8(a0, *((short *) (0x202 + a0))); } while (0);
}

__attribute__((section(".text.Obj0000_Set_Short_204")))
__attribute__((section(".text.Obj0000_Set_Short_204")))
void Obj0000_Set_Short_204(unsigned char *a0)
{
    do { func_0016B1F8(a0, *((short *)(a0 + 0x204))); } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_0016F8E0")))
__attribute__((section(".text.Tramp_func_001C29D0_0016F8E0")))
void Tramp_func_001C29D0_0016F8E0(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_0016FBD8")))
__attribute__((section(".text.Tramp_func_001C29D0_0016FBD8")))
void Tramp_func_001C29D0_0016FBD8(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_0016FE48")))
__attribute__((section(".text.Tramp_func_001C29D0_0016FE48")))
void Tramp_func_001C29D0_0016FE48(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00170130")))
__attribute__((section(".text.Tramp_func_001C29D0_00170130")))
void Tramp_func_001C29D0_00170130(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00170418")))
__attribute__((section(".text.Tramp_func_001C29D0_00170418")))
void Tramp_func_001C29D0_00170418(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BFB80_001706E0")))
__attribute__((section(".text.Tramp_func_001BFB80_001706E0")))
void Tramp_func_001BFB80_001706E0(void)
{
  func_001BFB80();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BFB80_00170970")))
__attribute__((section(".text.Tramp_func_001BFB80_00170970")))
void Tramp_func_001BFB80_00170970(void)
{
  func_001BFB80();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BFB80_00170C00")))
__attribute__((section(".text.Tramp_func_001BFB80_00170C00")))
void Tramp_func_001BFB80_00170C00(void)
{
  func_001BFB80();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BFB80_00170E90")))
__attribute__((section(".text.Tramp_func_001BFB80_00170E90")))
void Tramp_func_001BFB80_00170E90(void)
{
  func_001BFB80();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BFB80_00171000")))
__attribute__((section(".text.Tramp_func_001BFB80_00171000")))
void Tramp_func_001BFB80_00171000(void)
{
  func_001BD6B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_001717A0")))
__attribute__((section(".text.Tramp_func_001B79B0_001717A0")))
void Tramp_func_001B79B0_001717A0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BD6B0_00171C20")))
__attribute__((section(".text.Tramp_func_001BD6B0_00171C20")))
void Tramp_func_001BD6B0_00171C20(void)
{
  func_001BD6B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00173198")))
__attribute__((section(".text.Tramp_func_001B79B0_00173198")))
void Tramp_func_001B79B0_00173198(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_001741E8")))
__attribute__((section(".text.Tramp_func_001B79B0_001741E8")))
void Tramp_func_001B79B0_001741E8(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00174FB0")))
__attribute__((section(".text.Tramp_func_001B79B0_00174FB0")))
void Tramp_func_001B79B0_00174FB0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00176738")))
__attribute__((section(".text.Tramp_func_001B79B0_00176738")))
void Tramp_func_001B79B0_00176738(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00177DC0")))
__attribute__((section(".text.Tramp_func_001B79B0_00177DC0")))
void Tramp_func_001B79B0_00177DC0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_001784F8")))
__attribute__((section(".text.Tramp_func_001C29D0_001784F8")))
void Tramp_func_001C29D0_001784F8(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_001787A0")))
__attribute__((section(".text.Tramp_func_001C29D0_001787A0")))
void Tramp_func_001C29D0_001787A0(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_001789F8")))
__attribute__((section(".text.Tramp_func_001B79B0_001789F8")))
void Tramp_func_001B79B0_001789F8(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00178CC0")))
__attribute__((section(".text.Tramp_func_001C29D0_00178CC0")))
void Tramp_func_001C29D0_00178CC0(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00178F58")))
__attribute__((section(".text.Tramp_func_001C29D0_00178F58")))
void Tramp_func_001C29D0_00178F58(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00179798")))
__attribute__((section(".text.Tramp_func_001B79B0_00179798")))
void Tramp_func_001B79B0_00179798(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017A508")))
__attribute__((section(".text.Tramp_func_001B79B0_0017A508")))
void Tramp_func_001B79B0_0017A508(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017B548")))
__attribute__((section(".text.Tramp_func_001B79B0_0017B548")))
void Tramp_func_001B79B0_0017B548(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017C008")))
__attribute__((section(".text.Tramp_func_001B79B0_0017C008")))
void Tramp_func_001B79B0_0017C008(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BD6B0_0017C5B0")))
__attribute__((section(".text.Tramp_func_001BD6B0_0017C5B0")))
void Tramp_func_001BD6B0_0017C5B0(void)
{
  func_001BD6B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017CE18")))
__attribute__((section(".text.Tramp_func_001B79B0_0017CE18")))
void Tramp_func_001B79B0_0017CE18(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BC0A0_0017D560")))
__attribute__((section(".text.Tramp_func_001BC0A0_0017D560")))
void Tramp_func_001BC0A0_0017D560(void)
{
  func_001BC0A0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017DB40")))
__attribute__((section(".text.Tramp_func_001B79B0_0017DB40")))
void Tramp_func_001B79B0_0017DB40(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017E658")))
__attribute__((section(".text.Tramp_func_001B79B0_0017E658")))
void Tramp_func_001B79B0_0017E658(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BC0A0_0017EA28")))
__attribute__((section(".text.Tramp_func_001BC0A0_0017EA28")))
void Tramp_func_001BC0A0_0017EA28(void)
{
  func_001BC0A0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BD6B0_0017EB98")))
__attribute__((section(".text.Tramp_func_001BD6B0_0017EB98")))
void Tramp_func_001BD6B0_0017EB98(void)
{
  func_001BD6B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017EDD0")))
__attribute__((section(".text.Tramp_func_001B79B0_0017EDD0")))
void Tramp_func_001B79B0_0017EDD0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017F1D0")))
__attribute__((section(".text.Tramp_func_001B79B0_0017F1D0")))
void Tramp_func_001B79B0_0017F1D0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BC0A0_0017F470")))
__attribute__((section(".text.Tramp_func_001BC0A0_0017F470")))
void Tramp_func_001BC0A0_0017F470(void)
{
  func_001BC0A0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017F990")))
__attribute__((section(".text.Tramp_func_001B79B0_0017F990")))
void Tramp_func_001B79B0_0017F990(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0017FD80")))
__attribute__((section(".text.Tramp_func_001B79B0_0017FD80")))
void Tramp_func_001B79B0_0017FD80(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_001815B0")))
__attribute__((section(".text.Tramp_func_001B79B0_001815B0")))
void Tramp_func_001B79B0_001815B0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BC0A0_001817C8")))
__attribute__((section(".text.Tramp_func_001BC0A0_001817C8")))
void Tramp_func_001BC0A0_001817C8(void)
{
  func_001BC0A0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00182020")))
__attribute__((section(".text.Tramp_func_001B79B0_00182020")))
void Tramp_func_001B79B0_00182020(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00182818")))
__attribute__((section(".text.Tramp_func_001C29D0_00182818")))
void Tramp_func_001C29D0_00182818(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00182FD8")))
__attribute__((section(".text.Tramp_func_001B79B0_00182FD8")))
void Tramp_func_001B79B0_00182FD8(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BFB80_001834F0")))
__attribute__((section(".text.Tramp_func_001BFB80_001834F0")))
void Tramp_func_001BFB80_001834F0(void)
{
  func_001BFB80();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_001837D8")))
__attribute__((section(".text.Tramp_func_001C29D0_001837D8")))
void Tramp_func_001C29D0_001837D8(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00184A20")))
__attribute__((section(".text.Tramp_func_001B79B0_00184A20")))
void Tramp_func_001B79B0_00184A20(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_0014EFA8_001866A0")))
__attribute__((section(".text.Tramp_func_0014EFA8_001866A0")))
void Tramp_func_0014EFA8_001866A0(void)
{
  func_0014EFA8();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BC0A0_00186928")))
__attribute__((section(".text.Tramp_func_001BC0A0_00186928")))
void Tramp_func_001BC0A0_00186928(void)
{
  func_001BC0A0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00187190")))
__attribute__((section(".text.Tramp_func_001B79B0_00187190")))
void Tramp_func_001B79B0_00187190(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00187958")))
__attribute__((section(".text.Tramp_func_001C29D0_00187958")))
void Tramp_func_001C29D0_00187958(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00187C18")))
__attribute__((section(".text.Tramp_func_001C29D0_00187C18")))
void Tramp_func_001C29D0_00187C18(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_00188528")))
__attribute__((section(".text.Tramp_func_001B79B0_00188528")))
void Tramp_func_001B79B0_00188528(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00188C88")))
__attribute__((section(".text.Tramp_func_001C29D0_00188C88")))
void Tramp_func_001C29D0_00188C88(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00188F10")))
__attribute__((section(".text.Tramp_func_001C29D0_00188F10")))
void Tramp_func_001C29D0_00188F10(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0018A110")))
__attribute__((section(".text.Tramp_func_001B79B0_0018A110")))
void Tramp_func_001B79B0_0018A110(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0018AD88")))
__attribute__((section(".text.Tramp_func_001B79B0_0018AD88")))
void Tramp_func_001B79B0_0018AD88(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0018BAA0")))
__attribute__((section(".text.Tramp_func_001B79B0_0018BAA0")))
void Tramp_func_001B79B0_0018BAA0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0018C8A8")))
__attribute__((section(".text.Tramp_func_001B79B0_0018C8A8")))
void Tramp_func_001B79B0_0018C8A8(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0018D698")))
__attribute__((section(".text.Tramp_func_001B79B0_0018D698")))
void Tramp_func_001B79B0_0018D698(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0018E450")))
__attribute__((section(".text.Tramp_func_001B79B0_0018E450")))
void Tramp_func_001B79B0_0018E450(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_0018EC28")))
__attribute__((section(".text.Tramp_func_001C29D0_0018EC28")))
void Tramp_func_001C29D0_0018EC28(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BFB80_0018EE38")))
__attribute__((section(".text.Tramp_func_001BFB80_0018EE38")))
void Tramp_func_001BFB80_0018EE38(void)
{
  func_001BFB80();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BC0A0_0018F0A0")))
__attribute__((section(".text.Tramp_func_001BC0A0_0018F0A0")))
void Tramp_func_001BC0A0_0018F0A0(void)
{
  func_001BC0A0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_0018FBF0")))
__attribute__((section(".text.Tramp_func_001B79B0_0018FBF0")))
void Tramp_func_001B79B0_0018FBF0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_001915B8")))
__attribute__((section(".text.Tramp_func_001B79B0_001915B8")))
void Tramp_func_001B79B0_001915B8(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00191CC8")))
__attribute__((section(".text.Tramp_func_001C29D0_00191CC8")))
void Tramp_func_001C29D0_00191CC8(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BC0A0_00191F30")))
__attribute__((section(".text.Tramp_func_001BC0A0_00191F30")))
void Tramp_func_001BC0A0_00191F30(void)
{
  func_001BC0A0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001BC0A0_00192198")))
__attribute__((section(".text.Tramp_func_001BC0A0_00192198")))
void Tramp_func_001BC0A0_00192198(void)
{
  func_001BC0A0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001B79B0_001928B0")))
__attribute__((section(".text.Tramp_func_001B79B0_001928B0")))
void Tramp_func_001B79B0_001928B0(void)
{
  func_001B79B0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00192BC8")))
__attribute__((section(".text.Tramp_func_001C29D0_00192BC8")))
void Tramp_func_001C29D0_00192BC8(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00192EF8")))
__attribute__((section(".text.Tramp_func_001C29D0_00192EF8")))
void Tramp_func_001C29D0_00192EF8(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Tramp_func_001C29D0_00193180")))
__attribute__((section(".text.Tramp_func_001C29D0_00193180")))
void Tramp_func_001C29D0_00193180(void)
{
  func_001C29D0();
  do { } while (0);
}

__attribute__((section(".text.Obj0000_Set_Fields_1EC_280_Zero")))
void Obj0000_Set_Fields_1EC_280_Zero(unsigned char *a0, unsigned char *a1)
{
    int v1 = *(int *)(a1 + 0x18);
    int *p = (int *)(a0 + 0x1EC);
    int a2 = *(int *)(a1 + 0x1C);
    int *q = (int *)(a0 + 0x280);
    int i = 0x1F;

    p[0] = v1;
    p[1] = a2;
    p[2] = *(int *)(a1 + 0x18);
    p[3] = 0;
    *(int *)(a0 + 0x200) = 0;

    do {
        i = i - 1;
        *q = 0;
        q = q - 1;
    } while (i >= 0);
}

typedef struct {
    void **vtbl;
} ObjVT;

__attribute__((section(".text.Obj0000_Call_Vtbl6_Vtbl8_Field_1_0034C680")))
int Obj0000_Call_Vtbl6_Vtbl8_Field_1_0034C680(ObjVT *obj, int a1, int a2) {
    int local[2];
    int s1 = (unsigned int)a1 < 1U;
    ((void (*)(ObjVT *, int, int, int *))obj->vtbl[6])(obj, a1, a2, local);
    ((void (*)(ObjVT *, int, int *))obj->vtbl[8])(obj, s1, local);
    return local[1];
}

void func_003A6D78(void);
void func_003A6DE0(void);
void func_003A6E60(void);
void func_003A6EC8(void);

typedef struct {
    int unk_00;      /* 0x00 */
    int unk_04;      /* 0x04 */
    int unk_08;      /* 0x08 */
    short unk_0C;      /* 0x0C */
    short unk_0E;      /* 0x0E */
    int unk_10;      /* 0x10 */
    int unk_14;      /* 0x14 -- not touched */
    int unk_18;      /* 0x18 */
    void *unk_1C;    /* 0x1C */
    void (*fn_20)(void); /* 0x20 */
    void (*fn_24)(void); /* 0x24 */
    void (*fn_28)(void); /* 0x28 */
    void (*fn_2C)(void); /* 0x2C */
    int unk_30[9];   /* 0x30 -- not touched, pad to 0x54 */
    int unk_54;      /* 0x54 */
} CGUnk_3A6188_t;

__attribute__((section(".text.Obj0000_Setup_Fields_00_04_08_0C_0E_10_18_1C_20_24_28_2C_54")))
void Obj0000_Setup_Fields_00_04_08_0C_0E_10_18_1C_20_24_28_2C_54(CGUnk_3A6188_t *a0, short a1, short a2, int a3) {
    a0->unk_00 = 0;
    a0->unk_04 = 0;
    a0->unk_08 = 0;
    a0->unk_0C = a1;
    a0->unk_0E = a2;
    a0->unk_10 = 0;
    a0->unk_18 = 0;
    a0->unk_1C = (void *)a0;
    a0->fn_20 = func_003A6D78;
    a0->fn_24 = func_003A6DE0;
    a0->fn_28 = func_003A6E60;
    a0->fn_2C = func_003A6EC8;
    a0->unk_54 = a3;
}

__attribute__((section(".text.Obj0000_Call_FnFC_Field_100_94_90_Scaled")))
void Obj0000_Call_FnFC_Field_100_94_90_Scaled(unsigned char *arg0)
{
  signed char b;
  int a2;
  int f4;
  int a1;
  int a0arg;
  void (*fn)(int, int, int);
  a2 = *((int *) (arg0 + 0x90));
  f4 = *((int *) (arg0 + 0xF4));
  b = *((signed char *) (arg0 + 0xE));
  a1 = *((int *) (arg0 + 0x94));
  a2 = a2 * b;
  fn = *((void (**)(int, int, int)) (arg0 + 0xFC));
  a1 = a1 - f4;
  ;
  a1 = (a1 < 0) ? (a1 + 0x7FFFFFFF) : (a1);
  fn(*((int *) (arg0 + 0x100)), a1, a2 << 1);
  *((int *) (arg0 + 0xF4)) = *((int *) (arg0 + 0x94));
}

extern int D_0045A460;
extern unsigned char D_0045A470;

extern int func_00369F20(int, unsigned int);

__attribute__((section(".text.Obj0000_Check_D_0045A460_Magic_And_D_0045A470_Val")))
int Obj0000_Check_D_0045A460_Magic_And_D_0045A470_Val(void)
{
    if (D_0045A460 != (int)0x5A5A5A5A) {
        return func_00369F20(0, 0xFF03FF02U);
    }
    if (D_0045A470 != 4) {
        while (1) {
            ((void(*)(void))(unsigned int)-1)();
        }
    }
    return 0;
}

typedef struct { unsigned char unk[0x5D8]; int field_5D8; unsigned char pad[4]; int field_5E0; } D007474A0_t;

__attribute__((section(".text.Obj0000_Set_D_007474A0_Fields_5D8_5E0")))
__attribute__((section(".text.Obj0000_Set_D_007474A0_Fields_5D8_5E0")))
void Obj0000_Set_D_007474A0_Fields_5D8_5E0(unsigned char *a0) {
    D_007474A0.field_5D8 = *(int *)(a0 + 0x68);
    D_007474A0.field_5E0 = *(int *)(a0 + 0x6C);
}

__attribute__((section(".text.Obj0000_Or_Field_B90_Bit_A1")))
__attribute__((section(".text.Obj0000_Or_Field_B90_Bit_A1")))
void Obj0000_Or_Field_B90_Bit_A1(int **a0, int a1) {
    int *ptr = *a0;
    if (ptr == 0) return;
    *(int *)((char *)ptr + 0xB90) |= (1 << a1);
}

typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
} Entry344FD8;

typedef struct {
    unsigned char pad[0xB4];
    int fB4;
    int fB8;
    int fBC;
    Entry344FD8 entries[8];
} Obj344FD8;

__attribute__((section(".text.Obj0000_Init_Fields_B4_B8_BC_Entries")))
void Obj0000_Init_Fields_B4_B8_BC_Entries(Obj344FD8 *a0) {
    int i;
    a0->fB4 = 0;
    a0->fB8 = 0;
    a0->fBC = 0;
    for (i = 0; i <= 7; i++) {
        a0->entries[i].f0 = 0;
        a0->entries[i].f4 = 0;
        a0->entries[i].f8 = 0;
        a0->entries[i].fC = 0;
        a0->entries[i].f10 = 0x11;
    }
}

/* func_00359218 lives in its own TU (src/cod/func_00359218.c) with
 * -f=-freorder-blocks dropped via compile_config.json::compile_units,
 * See the
 * sibling TU header for the matching rationale.  */

extern void func_0034FA28(void *obj, int *out0, int *out4);
extern void func_0034F718(void *obj);
extern void func_0034FAD8(void *obj);
extern void func_0034F930(void *obj);
extern void func_0034FB70(void *obj);
extern void func_0034FC20(void *obj);

__attribute__((section(".text.func_0034F6C0")))
void func_0034F6C0(void *obj) {
    int out0;
    int out4;
    func_0034FA28(obj, &out0, &out4);
    func_0034F718(obj);
    func_0034FAD8(obj);
    func_0034F930(obj);
    func_0034FB70(obj);
    func_0034FC20(obj);
}


__attribute__((section(".text.func_0012C748")))
int func_0012C748(char *a0) { return *(int *)(a0 + 0x5FC) != 0; }

__attribute__((section(".text.func_00138F88")))
int func_00138F88(char *a0, int a1) { return a1 & *(int *)(a0 + 0x1028); }

__attribute__((section(".text.func_0013C808")))
void func_0013C808(char *a0) { *(int *)(a0 + 0x94) = 0; *(int *)(a0 + 0x9C) = 0; }

__attribute__((section(".text.func_00158CC8")))
float func_00158CC8(int a0, float *a1) { return a1[2]; }

__attribute__((section(".text.func_00124E58")))
void func_00124E58(char *a0) { *(int *)(a0 + 0x640) = 0; a0[0x648] = 0; }

__attribute__((section(".text.func_001F6FA0")))
int func_001F6FA0(void) { return 1; }

__attribute__((section(".text.func_001FFE08")))
void func_001FFE08(char *a0) { *(short *)a0 = 0; }

__attribute__((section(".text.func_002006B0")))
int func_002006B0(int a0) { return a0 & 0xFFFF; }

__attribute__((section(".text.func_00200AB0")))
int func_00200AB0(int a0) { return a0; }

__attribute__((section(".text.func_002019F8")))
int func_002019F8(char *a0) { return *(unsigned char *)(a0 + 0x110C); }

__attribute__((section(".text.func_0020D138")))
int func_0020D138(void) { return 0; }

__attribute__((section(".text.func_001F1B18")))
void func_001F1B18(void) {}

__attribute__((section(".text.func_0010A408")))
void func_0010A408(char *a0, int a1, int a2, int a3, int a4, short a5) {
    *(int*)(a0 + 0x1668) = a1;
    *(int*)(a0 + 0x1660) = a2;
    *(int*)(a0 + 0x1670) = a3;
    *(int*)(a0 + 0x1678) = a4;
    *(short*)(a0 + 0x1680) = a5;
}

__attribute__((section(".text.func_0010A420")))
void func_0010A420(char *a0, int a1, int a2, int a3, int a4, short a5) {
    *(int*)(a0 + 0x166C) = a1;
    *(int*)(a0 + 0x1664) = a2;
    *(int*)(a0 + 0x1674) = a3;
    *(int*)(a0 + 0x167C) = a4;
    *(short*)(a0 + 0x1682) = a5;
}

__attribute__((section(".text.func_0010B5B8")))
int func_0010B5B8(char *a0) {
    return *(unsigned char*)(a0 + 0x2F4) == 1;
}

__attribute__((section(".text.func_0010B698")))
int func_0010B698(char *a0) {
    int v = *(int*)(a0 + 0x15F4) & 0x400000;
    return v != 0;
}

__attribute__((section(".text.func_0010BD08")))
void func_0010BD08(char *a0, unsigned char a1) {
    *(unsigned char*)(a0 + 0x2F7) = a1;
    *(unsigned char*)(a0 + 0x2F4) = 6;
    *(unsigned char*)(a0 + 0x2F6) = 2;
    *(unsigned char*)(a0 + 0x2F5) = 0;
}

__attribute__((section(".text.func_00124FC8")))
int func_00124FC8(char *a0) {
    int v = *(int*)(a0 + 0x15F4) & 0x2;
    return v != 0;
}

__attribute__((section(".text.func_0012C0D8")))
void func_0012C0D8(char *a0) {
    *(unsigned char*)(a0 + 0x2F4) = 0;
    *(unsigned char*)(a0 + 0x2F5) = 0x45;
    *(unsigned char*)(a0 + 0x2F6) = 0;
    *(unsigned char*)(a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_0012C530")))
int func_0012C530(char *a0) {
    int v = *(int*)(a0 + 0x15F4) & 0x1000;
    return v != 0;
}

__attribute__((section(".text.func_0012CA48")))
int func_0012CA48(char *a0) {
    int v = *(int*)(a0 + 0x15F4) & 0x100000;
    return v != 0;
}

__attribute__((section(".text.func_0012CDD0")))
void func_0012CDD0(char *a0) {
    *(unsigned char*)(a0 + 0x2F4) = 0;
    *(unsigned char*)(a0 + 0x2F5) = 0x36;
    *(unsigned char*)(a0 + 0x2F6) = 0;
    *(unsigned char*)(a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_0012CED8")))
int func_0012CED8(char *a0) {
    int v = *(int*)(a0 + 0x15F4) & 0x1000000;
    return v != 0;
}

__attribute__((section(".text.func_0012CEF0")))
unsigned long long func_0012CEF0(char *a0) {
    unsigned long long v = *(unsigned char*)(a0 + 0x15F4);
    return v >> 7;
}

__attribute__((section(".text.func_001333B8")))
int func_001333B8(char *a0, unsigned short a1) {
    return *(int*)(a0 + 0x20) + ((a1 & 0xFFFF) << 3);
}

__attribute__((section(".text.func_00133B80")))
void func_00133B80(char *a0) {
    *(int*)(a0 + 0x8) = *(int*)(a0 + 0x8) & ~0x2;
}

__attribute__((section(".text.func_00139B68")))
void func_00139B68(char *a0, int a1, int a2, int a3) {
    *(int*)(a0 + 0x360) = a1;
    *(int*)(a0 + 0x364) = a2;
    *(int*)(a0 + 0x368) = a3;
}


__attribute__((section(".text.func_001D6DB0")))
int func_001D6DB0(int a0) {
    *(int*)((char*)a0 + 0x0) = 0;
    *(int*)((char*)a0 + 0x4) = 8;
    return a0;
}

__attribute__((section(".text.func_001ED7C8")))
int func_001ED7C8(int a0) {
    int v0 = *(int*)((char*)a0 + 0x0);
    *(int*)((char*)a0 + 0x348) = 0;
    v0 |= 1;
    *(int*)((char*)a0 + 0x0) = v0;
    return v0;
}

__attribute__((section(".text.func_001F1C48")))
void func_001F1C48(void) {}

__attribute__((section(".text.func_001F1ED8")))
void func_001F1ED8(void) {}

__attribute__((section(".text.func_001F5098")))
void func_001F5098(void) {}

__attribute__((section(".text.func_001F6CF8")))
void func_001F6CF8(int a0) {
    *(int*)((char*)a0 + 0x8) = 0;
    *(short*)((char*)a0 + 0xC) = 0;
    *(short*)((char*)a0 + 0xE) = 0;
    *(short*)((char*)a0 + 0x10) = 0;
    *(short*)((char*)a0 + 0x12) = 0;
    *(int*)((char*)a0 + 0x0) = 0;
}

__attribute__((section(".text.func_001F6ED8")))
void func_001F6ED8(void) {}

__attribute__((section(".text.func_001F7800")))
int func_001F7800(int a0, int a1, int a2) {
    int v0;
    a1 = (a1 << 4) + 4;
    a0 = a0 + a1;
    v0 = *(int*)((char*)a0 + 4);
    *(int*)((char*)a0 + 4) = a2;
    *(int*)((char*)a2 + 4) = v0;
    return v0;
}

__attribute__((section(".text.func_001F7B50")))
void func_001F7B50(void) {}

__attribute__((section(".text.func_001F7B58")))
void func_001F7B58(void) {}

__attribute__((section(".text.func_001F7D18")))
void func_001F7D18(void) {}

__attribute__((section(".text.func_001FA620")))
short func_001FA620(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(short*)(p + 0x1C);
}

__attribute__((section(".text.func_001FA678")))
char func_001FA678(int *a0)
{
    int p = *a0;
    if (p == 0) return 1;
    return *(char*)(p + 0x1F);
}

__attribute__((section(".text.func_001FA858")))
int func_001FA858(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(int*)(p + 0x24);
}

__attribute__((section(".text.func_001FA950")))
int func_001FA950(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(int*)(p + 0x68);
}

__attribute__((section(".text.func_001FAA00")))
int func_001FAA00(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(int*)(p + 0x6C);
}

__attribute__((section(".text.func_001FAC58")))
unsigned char func_001FAC58(int *a0)
{
    int p = *a0;
    return *(unsigned char*)(p + 0xA8);
}

__attribute__((section(".text.func_001FAC68")))
int func_001FAC68(int *a0)
{
    int p = *a0;
    if (p == 0) return 0x64;
    return *(int*)(p + 0x84);
}

__attribute__((section(".text.func_001FAC80")))
int func_001FAC80(int *a0)
{
    int p = *a0;
    if (p == 0) return 0x64;
    return *(int*)(p + 0x80);
}

__attribute__((section(".text.func_001FAE28")))
void func_001FAE28(int *a0, unsigned char a1)
{
    int p = *a0;
    if (p != 0) *(unsigned char*)(p + 0x156) = a1;
}

__attribute__((section(".text.func_001FAE40")))
void func_001FAE40(int *a0, unsigned char a1)
{
    int p = *a0;
    if (p != 0) *(unsigned char*)(p + 0x156) = a1 + *(unsigned char*)(p + 0x156);
}

__attribute__((section(".text.func_001FBED0")))
short func_001FBED0(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(short*)(p + 0x96);
}

__attribute__((section(".text.func_001FBF48")))
unsigned short func_001FBF48(int *a0)
{
    int p = *a0;
    if (p == 0) return 0;
    return *(unsigned short*)(p + 0x12);
}

__attribute__((section(".text.func_001FBF78")))
void func_001FBF78(int a0, unsigned short a1)
{
    int p = *(int*)a0;
    if (p) {
        *(short*)(p + 0x12) = a1;
    }
}

__attribute__((section(".text.func_001FC0A8")))
unsigned char func_001FC0A8(int a0)
{
    int p = *(int*)a0;
    if (!p) return 0;
    return *(unsigned char*)(p + 0xAE);
}

__attribute__((section(".text.func_001FC0C0")))
unsigned char func_001FC0C0(int a0)
{
    int p = *(int*)a0;
    if (!p) return 0;
    return *(unsigned char*)(p + 0xAF);
}

__attribute__((section(".text.func_001FC100")))
void func_001FC100(int a0, unsigned char a1)
{
    int p = *(int*)a0;
    if (p) {
        *(unsigned char*)(p + 0xAE) = a1;
        *(unsigned char*)(*(int*)a0 + 0xAF) = a1;
    }
}

__attribute__((section(".text.func_001FC120")))
void func_001FC120(int a0)
{
    int p = *(int*)a0;
    if (p) {
        *(unsigned char*)(p + 0x157) = 1;
    }
}

__attribute__((section(".text.func_001FC150")))
int func_001FC150(int a0)
{
    int p = *(int*)a0;
    if (p) {
        return *(unsigned char*)(p + 0x157) != 0;
    }
    return 0;
}

__attribute__((section(".text.func_001FC3D0")))
int func_001FC3D0(int a0)
{
    int p = *(int*)a0;
    if (!p) return 0;
    return *(int*)(p + 0xB94);
}

__attribute__((section(".text.func_001FC530")))
int func_001FC530(int a0)
{
    int p = *(int*)a0;
    if (!p) return 0;
    return *(int*)(p + 0xBA8);
}

__attribute__((section(".text.func_001FC5D0")))
unsigned short func_001FC5D0(int a0)
{
    int p = *(int*)a0;
    if (!p) return 0;
    return *(unsigned short*)(p + 0xBB6);
}

__attribute__((section(".text.func_001FC600")))
unsigned short func_001FC600(int a0)
{
    int p = *(int*)a0;
    if (!p) return 0;
    return *(unsigned short*)(p + 0xBB8);
}

__attribute__((section(".text.func_001FC630")))
void func_001FC630(int a0, int a1)
{
    int p = *(int*)a0;
    if (p) {
        *(int*)(p + 0xBBC) = *(int*)(p + 0xBBC) + a1;
    }
}

__attribute__((section(".text.func_001FC6C8")))
void func_001FC6C8(int a0)
{
    int p = *(int*)a0;
    if (p) {
        *(unsigned short*)(p + 0xBBA) = *(unsigned short*)(p + 0xBBA) & 0xFFFE;
    }
}

__attribute__((section(".text.func_001FC6E8")))
void func_001FC6E8(int a0)
{
    int p = *(int*)a0;
    if (p) {
        *(unsigned short*)(p + 0xBBA) = *(unsigned short*)(p + 0xBBA) | 1;
    }
}

__attribute__((section(".text.func_001FC708")))
int func_001FC708(int a0)
{
    int p = *(int*)a0;
    if (p) {
        return *(unsigned short*)(p + 0xBBA) & 1;
    }
    return 0;
}

__attribute__((section(".text.func_001FC740")))
int func_001FC740(int a0)
{
    int p = *(int*)a0;
    if (!p) return 0;
    return *(int*)(p + 0xBC0);
}

__attribute__((section(".text.func_00268500")))
void func_00268500(void) {}

__attribute__((section(".text.func_0026ECC0")))
int func_0026ECC0(void *a0) {
    if (*(int *)((char *)a0 + 0x16D0) & 0x2) return 1;
    return 0;
}

__attribute__((section(".text.func_0026F2F0")))
int func_0026F2F0(void *a0) {
    if (*(int *)((char *)a0 + 0x16D0) & 0x100000) return 1;
    return 0;
}

__attribute__((section(".text.func_0026F308")))
int func_0026F308(void *a0) {
    if (*(int *)((char *)a0 + 0x16D4) & 0x4) return 1;
    return 0;
}

__attribute__((section(".text.func_0026F318")))
int func_0026F318(void *a0) {
    if (*(unsigned short *)((char *)a0 + 0x3AC) & 0x4) return 1;
    return 0;
}

__attribute__((section(".text.func_00272570")))
void func_00272570(void *a0) {
    *(int *)((char *)a0 + 0x16D0) |= 0x20000000;
}

__attribute__((section(".text.func_00273630")))
void func_00273630(void) {
    char buf[24];
    (void)buf;
}

__attribute__((section(".text.func_00273D28")))
void func_00273D28(void *a0, char a1) {
    *(char *)((char *)a0 + 0x1868) = a1;
}

__attribute__((section(".text.func_00274140")))
void func_00274140(void *a0) {
    *(int *)((char *)a0 + 0x16D4) |= 0x1000;
}

__attribute__((section(".text.func_00275638")))
void func_00275638(void *a0) {
    *(int *)((char *)a0 + 0x1644) |= 0x800000;
}

__attribute__((section(".text.func_00275650")))
int func_00275650(void *a0) {
    if (*(int *)((char *)a0 + 0x16D4) & 0x2000000) return 1;
    return 0;
}

__attribute__((section(".text.func_002761B0")))
void func_002761B0(void *a0) {
    *(unsigned char *)((char *)a0 + 0x2F5) = 0x68;
    *(unsigned char *)((char *)a0 + 0x2F6) = 0x4;
    *(unsigned char *)((char *)a0 + 0x2F4) = 0;
    *(unsigned char *)((char *)a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_002761F8")))
void func_002761F8(void *a0) {
    *(int *)((char *)a0 + 0x16D4) |= 0x80000000;
}

__attribute__((section(".text.func_00276210")))
void func_00276210(void *a0) {
    *(int *)((char *)a0 + 0x16D4) &= 0x7FFFFFFF;
}

__attribute__((section(".text.func_00276468")))
int func_00276468(void *a0) {
    return *(unsigned char *)((char *)a0 + 0x17C3) != 0 ? 2 : 0;
}

__attribute__((section(".text.func_002767E0")))
int func_002767E0(int a0) { return *(int*)((char*)a0 + 0x698); }

__attribute__((section(".text.func_00277F08")))
void func_00277F08(void) {}

__attribute__((section(".text.func_00277F10")))
void func_00277F10(void) {}

__attribute__((section(".text.func_00277F78")))
void func_00277F78(void) {}

__attribute__((section(".text.func_00278000")))
void func_00278000(int a0) {
    *(char*)((char*)a0 + 0x2F4) = 0;
    *(char*)((char*)a0 + 0x2F6) = 0;
    *(char*)((char*)a0 + 0x2F5) = 4;
    *(char*)((char*)a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_00279670")))
void func_00279670(void) {}

__attribute__((section(".text.func_00279930")))
void func_00279930(void) {}

__attribute__((section(".text.func_00279C88")))
int func_00279C88(int a0) {
    *(int*)((char*)a0 + 0x1560) |= 4;
    return *(int*)((char*)a0 + 0x1560);
}

__attribute__((section(".text.func_00279E70")))
void func_00279E70(void) {}

__attribute__((section(".text.func_00279F60")))
void func_00279F60(void) {}

__attribute__((section(".text.func_0027A128")))
int func_0027A128(int a0) { return *(int*)((char*)a0 + 0x1580); }

__attribute__((section(".text.func_0027CFF8")))
void func_0027CFF8(void) {}

__attribute__((section(".text.func_0027D0D8")))
void func_0027D0D8(void) {}

__attribute__((section(".text.func_0027D0E0")))
void func_0027D0E0(void) {}

__attribute__((section(".text.func_0027D148")))
void func_0027D148(void) {}

__attribute__((section(".text.func_0027DAF0")))
void func_0027DAF0(char *a0) {
    *(char *)(a0 + 0x2F4) = 0;
    *(char *)(a0 + 0x2F5) = 2;
    *(char *)(a0 + 0x2F6) = 0;
    *(char *)(a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_0027DB08")))
void func_0027DB08(char *a0) {
    *(char *)(a0 + 0x2F4) = 0;
    *(char *)(a0 + 0x2F5) = 4;
    *(char *)(a0 + 0x2F6) = 0;
    *(char *)(a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_0027DCB8")))
void func_0027DCB8(char *a0, char a1) {
    *(char *)(a0 + 0x2F7) = a1;
    *(char *)(a0 + 0x2F5) = 9;
    *(char *)(a0 + 0x2F6) = 0;
    *(char *)(a0 + 0x2F4) = 0;
}

__attribute__((section(".text.func_0027DCD0")))
void func_0027DCD0(char *a0, char a1) {
    *(char *)(a0 + 0x2F7) = a1;
    *(char *)(a0 + 0x2F5) = 0xA;
    *(char *)(a0 + 0x2F6) = 0;
    *(char *)(a0 + 0x2F4) = 0;
}

__attribute__((section(".text.func_0027DCE8")))
void func_0027DCE8(char *a0) {
    *(char *)(a0 + 0x2F4) = 0;
    *(char *)(a0 + 0x2F5) = 3;
    *(char *)(a0 + 0x2F6) = 0;
    *(char *)(a0 + 0x2F7) = 0;
}

__attribute__((section(".text.func_0027DD00")))
int func_0027DD00(char *a0) {
    return *(int *)(a0 + 0x1560) & 0x1;
}

__attribute__((section(".text.func_0027E4E0")))
void func_0027E4E0(void) {}

__attribute__((section(".text.func_0027E5C0")))
void func_0027E5C0(void) {}

__attribute__((section(".text.func_0027E5C8")))
void func_0027E5C8(void) {}

__attribute__((section(".text.func_0027E630")))
void func_0027E630(void) {}

__attribute__((section(".text.func_00280A08")))
void func_00280A08(void) {}

__attribute__((section(".text.func_00280AE8")))
void func_00280AE8(void) {}

extern int func_003A52F0(int a0, int a1, int a2);
__attribute__((section(".text.func_00332BE0")))
int func_00332BE0(int a0) { return func_003A52F0(a0, 0, 0x48); }

extern int func_003331E0(void);
__attribute__((section(".text.func_003332B0")))
int func_003332B0(void) { return func_003331E0(); }

extern int func_00331C98(void);
__attribute__((section(".text.func_00333F60")))
int func_00333F60(void) { return func_00331C98(); }

extern int func_003A52F0(int a0, int a1, int a2);
__attribute__((section(".text.func_00334500")))
int func_00334500(int a0) { return func_003A52F0(a0, 0, 0x30); }

extern int func_00334310(void);
__attribute__((section(".text.func_00334B20")))
int func_00334B20(void) { return func_00334310(); }

extern int func_0033B658(void);
__attribute__((section(".text.func_00335CE8")))
int func_00335CE8(void) { return func_0033B658(); }

extern int func_0033B670(void);
__attribute__((section(".text.func_00335D00")))
int func_00335D00(void) { return func_0033B670(); }

extern int func_0033B658(void);
__attribute__((section(".text.func_003362E8")))
int func_003362E8(void) { return func_0033B658(); }

extern int func_0033B670(void);
__attribute__((section(".text.func_00336300")))
int func_00336300(void) { return func_0033B670(); }

extern int func_003A9228(void);
__attribute__((section(".text.func_00336360")))
int func_00336360(void) { return func_003A9228(); }

extern int func_003A52F0(int a0, int a1, int a2);
__attribute__((section(".text.func_00336588")))
int func_00336588(int a0) { return func_003A52F0(a0, 0, 0x38); }

extern int func_003406D0(int a0);
__attribute__((section(".text.func_00336E20")))
int func_00336E20(int a0) { return func_003406D0(*(int*)((char*)a0 + 0xE8)); }

extern int func_00340740(int a0, short a1);
__attribute__((section(".text.func_00336E38")))
int func_00336E38(int a0, short a1) { return func_00340740(*(int*)((char*)a0 + 0xE8), a1); }

extern int func_00340A20(int a0);
__attribute__((section(".text.func_00336E58")))
int func_00336E58(int a0) { return func_00340A20(*(int*)((char*)a0 + 0xE8)); }

extern int func_0033F130(int a0);
__attribute__((section(".text.func_00336E70")))
int func_00336E70(int a0, int a1) { return func_0033F130(a1); }

extern int func_0033B658(void);
__attribute__((section(".text.func_003389F8")))
int func_003389F8(void) { return func_0033B658(); }

extern int func_0033B670(void);
__attribute__((section(".text.func_00338A10")))
int func_00338A10(void) { return func_0033B670(); }

extern int func_00340AE8(void *a0);
extern char D_00455900[];
__attribute__((section(".text.func_00338A28")))
int func_00338A28(void) { return func_00340AE8(D_00455900); }

extern int func_00340AE8(void *a0);
extern char D_00455A60[];
__attribute__((section(".text.func_00339438")))
int func_00339438(void) { return func_00340AE8(D_00455A60); }

extern int func_00340AE8(void *a0);
extern char D_00455BB8[];
__attribute__((section(".text.func_0033A028")))
int func_0033A028(void) { return func_00340AE8(D_00455BB8); }

extern int func_00332778(int);
__attribute__((section(".text.func_0033B200")))
int func_0033B200(int a0) { return func_00332778(a0); }

extern int func_0033B568(int);
__attribute__((section(".text.func_0033B658")))
int func_0033B658(void) { return func_0033B568(1); }

extern int func_0033B5C8(int);
__attribute__((section(".text.func_0033B670")))
int func_0033B670(void) { return func_0033B5C8(1); }

extern int func_0033B568(int);
__attribute__((section(".text.func_0033B688")))
int func_0033B688(void) { return func_0033B568(2); }

extern int func_0033B568(int);
__attribute__((section(".text.func_0033B6A0")))
int func_0033B6A0(void) { return func_0033B568(4); }

extern int func_0033B5C8(int);
__attribute__((section(".text.func_0033B6B8")))
int func_0033B6B8(void) { return func_0033B5C8(2); }

extern int func_0033B5C8(int);
__attribute__((section(".text.func_0033B6D0")))
int func_0033B6D0(void) { return func_0033B5C8(4); }

extern int func_0033BC48(int);
__attribute__((section(".text.func_0033BD18")))
int func_0033BD18(void) { return func_0033BC48(0); }

extern int func_0033BC48(int);
__attribute__((section(".text.func_0033BD30")))
int func_0033BD30(void) { return func_0033BC48(1); }

extern int func_0033BC48(int);
__attribute__((section(".text.func_0033BD48")))
int func_0033BD48(void) { return func_0033BC48(2); }

extern int func_0033BC48(int);
__attribute__((section(".text.func_0033BD60")))
int func_0033BD60(void) { return func_0033BC48(3); }

extern int func_0033BC48(int);
__attribute__((section(".text.func_0033BD78")))
int func_0033BD78(void) { return func_0033BC48(4); }

extern int func_0033BC48(int);
__attribute__((section(".text.func_0033BD90")))
int func_0033BD90(void) { return func_0033BC48(5); }

extern int func_0033BC48(int);
__attribute__((section(".text.func_0033BDA8")))
int func_0033BDA8(void) { return func_0033BC48(6); }

extern int func_0033BC48(int);
__attribute__((section(".text.func_0033BDC0")))
int func_0033BDC0(void) { return func_0033BC48(7); }

extern int func_0032B300(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_00342AF0")))
int func_00342AF0(int a0, int a1, int a2, int a3) {
    return func_0032B300(a0, a1, a2, a3);
}

extern int func_0032A9F0(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_00342B08")))
int func_00342B08(int a0, int a1, int a2, int a3) {
    return func_0032A9F0(a0, a1, a2, a3);
}

extern int func_0032AAA0(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_00342B20")))
int func_00342B20(int a0, int a1, int a2, int a3) {
    return func_0032AAA0(a0, a1, a2, a3);
}

extern int func_0032B660(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_00342B38")))
int func_00342B38(int a0, int a1, int a2, int a3) {
    return func_0032B660(a0, a1, a2, a3);
}

extern int func_003443E0(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_003443C8")))
int func_003443C8(int a0, int a1, int a2, int a3) {
    return func_003443E0(a0, a1, a2, a3);
}

extern int func_00345250(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_00344F18")))
int func_00344F18(int a0, int a1, int a2, int a3) {
    return func_00345250(a0, a1, a2, a3);
}

extern int func_00348BE0(int a0);
__attribute__((section(".text.func_003452C0")))
int func_003452C0(int a0, int a1) {
    return func_00348BE0(a1);
}

extern int func_00345D58(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_00345D40")))
int func_00345D40(int a0, int a1, int a2, int a3) {
    return func_00345D58(a0, a1, a2, a3);
}

extern int func_00345EE0(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_00345EC8")))
int func_00345EC8(int a0, int a1, int a2, int a3) {
    return func_00345EE0(a0, a1, a2, a3);
}

extern int func_00346450(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_003462A8")))
int func_003462A8(int a0, int a1, int a2, int a3) {
    return func_00346450(a0, a1, a2, a3);
}

extern int func_00346450(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_003462C0")))
int func_003462C0(int a0, int a1, int a2, int a3) {
    return func_00346450(a0, a1, a2, a3);
}

extern int func_00325F20(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_003466A8")))
int func_003466A8(int a0, int a1, int a2, int a3) {
    return func_00325F20(a0, a1, a2, a3);
}

extern int func_003462D8(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_003466C0")))
int func_003466C0(int a0, int a1, int a2, int a3) {
    return func_003462D8(a0, a1, a2, a3);
}

extern int func_00346368(int a0, int a1, int a2, int a3);
__attribute__((section(".text.func_003466D8")))
int func_003466D8(int a0, int a1, int a2, int a3) {
    return func_00346368(a0, a1, a2, a3);
}

extern int func_00348BE0(int a0);
__attribute__((section(".text.func_00346BE0")))
int func_00346BE0(int a0, int a1) {
    return func_00348BE0(a1);
}







































































