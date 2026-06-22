/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern int D_00747A84;
extern char D_005E8658[];
extern char D_005CAE50[];
extern char D_00462FC0[];
extern void func_002BECB0(void *a0, long a1);
extern void func_001331B8(void *a0, long a1, int a2);
extern void cCollisionSolidManage_ReleaseUnit(void *a0, void *a1);
extern void func_001B7BB8(void *a0);
extern int *D_003C2384;
extern void func_002A9DF8(int a0);
extern void cIDBase_resetAnim(int a0);

__attribute__((section(".text.SetField5B0Bit2ClearBit8_1B7908")))
void SetField5B0Bit2ClearBit8_1B7908(int a0)
{
    long v = *(unsigned int*)(a0 + 0x5B8);
    if ((v >> 9 & 1) == 0) {
        if ((D_00747A84 & 0x01000000) == 0) {
            *(int*)(a0 + 0x5B8) = *(int*)(a0 + 0x5B8) & ~0x40;
        }
    }
    func_002BECB0(D_005E8658, *(long*)(a0 + 0x538));
    func_001331B8(D_005CAE50, *(long*)(a0 + 0x540), 0);
    cCollisionSolidManage_ReleaseUnit(D_00462FC0, (void*)a0);
    func_001B7BB8((void*)a0);
    *(int*)(a0 + 0x5B0) = (*(int*)(a0 + 0x5B0) | 2) & ~8;
}

struct node {
    char pad0[4];
    struct node *prev;   /* 0x4 */
    struct node *next;   /* 0x8 */
    int c;               /* 0xC */
    int d;               /* 0x10 */
};

__attribute__((section(".text.UnlinkAndCoalesceNode_2A9680")))
void UnlinkAndCoalesceNode_2A9680(int a0, struct node *a1) {
    struct node *p;
    struct node *q;
    if (a1 != 0) {
        p = (struct node *)((char *)a1 - 0x20);
        q = p->prev;
        q->next = p->next;
        q->c = q->c + (p->d + p->c);
        p = p->next;
        if (p != 0) {
            p->prev = q;
        }
    }
}

__attribute__((section(".text.SetField380Bit2000ForTag_1B7300")))
void SetField380Bit2000ForTag_1B7300(int a0, int a1, int a2) {
    char *p = (char *)cModel_getMeshPtr(a0, 0);
    if (p != 0) {
        do {
            if (*(unsigned char *)(p + 0x40C) == a1) {
                int v;
                if (a2 == 1) {
                    v = *(int *)(p + 0x380) & 0xFFFFDFFF;
                } else {
                    v = *(int *)(p + 0x380) | 0x2000;
                }
                *(int *)(p + 0x380) = v;
            }
            p = *(char **)(p + 0x404);
        } while (p != 0);
    }
}
