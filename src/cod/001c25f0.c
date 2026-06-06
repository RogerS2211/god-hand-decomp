extern int D_00460D40;
extern int D_0042C348;
extern int D_00460D48;
extern int D_0042C4F8;
extern char D_00462FC0[];
extern int D_00460D50;
extern char D_0044AF10[];
extern int D_00460D58;
extern char D_0044B330[];
extern int D_00460D60;
extern char D_0044BE98[];
extern int D_00460D68;
extern int D_0044BF60;
extern int D_00460D78;
extern int D_0044D200;
extern int D_00460D80;
extern int D_0044D210;
extern int D_00460D88;
extern int D_0044D3A0;
extern int D_00460D90;
extern int D_0044D3D8;
extern int D_0044EE38;
extern int D_00460D98;
extern int D_00450098;
extern int D_00460D70;
extern int D_0045A5F8;

__attribute__((section(".text.func_001C25F0")))
void func_001C25F0(void *a0) {
    int *vt = *(int **)((char *)a0 + 0x214);
    short off = *(short *)((char *)vt + 0x70);
    void (*fp)(void *) = *(void (**)(void *))((char *)vt + 0x74);
    fp((char *)a0 + off);
    *(unsigned char *)((char *)a0 + 0x676) =
        *(unsigned char *)((char *)a0 + 0x676) | 2;
}

__attribute__((section(".text.InitStructZeroedFields_1E7960")))
void *InitStructZeroedFields_1E7960(void *a0) {
    func_003A52F0(a0, 0, 0x54);
    *(int *)((char *)a0 + 0x54) = 0;
    *(int *)((char *)a0 + 0x4) = 0;
    *(int *)((char *)a0 + 0x8) = 0;
    *(int *)((char *)a0 + 0xC) = 0;
    return a0;
}

__attribute__((section(".text.InitStructAndSubfields_1E8DA8")))
void *InitStructAndSubfields_1E8DA8(void *a0) {
    func_003A52F0(a0, 0, 0x54);
    func_001E8E88(a0);
    func_001E8EB8(a0);
    return a0;
}

__attribute__((section(".text.func_001F7C88")))
int *func_001F7C88(void) {
    if (D_00460D40 == 0) {
        func_0031EEC8(&D_00460D40, &D_0042C348);
    }
    return &D_00460D40;
}

__attribute__((section(".text.func_001FE148")))
int func_001FE148(int a0, int a1) {
    if (a1 == 0) {
        return 0;
    }
    func_001FD580(a1);
    func_001FCDB8(a1);
    return 1;
}

__attribute__((section(".text.func_001FE278")))
int func_001FE278(int a0, int a1) {
    if (a1 == 0) {
        return 0;
    }
    func_001FD580(a1);
    func_001FCDE8(a1);
    return 1;
}

__attribute__((section(".text.func_001FE4C0")))
int *func_001FE4C0(void) {
    if (D_00460D48 == 0) {
        func_0031EEC8(&D_00460D48, &D_0042C4F8);
    }
    return &D_00460D48;
}

__attribute__((section(".text.func_001FFA28")))
int func_001FFA28(int a0) {
    int v = func_001FFA68(a0);
    if (v == 0) {
        return 0;
    }
    return BuildPackedAddr_1FFD98(a0, v);
}

__attribute__((section(".text.ForwardDispatchByMode_27F170")))
void ForwardDispatchByMode_27F170(void *a0) {
    func_001347E8(D_00462FC0, a0);
    func_00306200(a0, 1, 2);
}

__attribute__((section(".text.func_002A9D60")))
void *func_002A9D60(void) {
    if (D_00460D50 == 0) {
        func_0031EEC8(&D_00460D50, D_0044AF10);
    }
    return &D_00460D50;
}

__attribute__((section(".text.func_002B6528")))
void *func_002B6528(void) {
    if (D_00460D58 == 0) {
        func_0031EEC8(&D_00460D58, D_0044B330);
    }
    return &D_00460D58;
}

__attribute__((section(".text.func_002BAD40")))
void *func_002BAD40(void) {
    if (D_00460D60 == 0) {
        func_0031EEC8(&D_00460D60, D_0044BE98);
    }
    return &D_00460D60;
}

__attribute__((section(".text.GetOrInit_460D68_2BAFA0")))
void *GetOrInit_460D68_2BAFA0(void) {
    if (D_00460D68 == 0) {
        func_0031EEC8(&D_00460D68, &D_0044BF60);
    }
    return &D_00460D68;
}

__attribute__((section(".text.Forward2CF6F8_2CB6A0")))
int Forward2CF6F8_2CB6A0(int a0, int a1, int a2) {
    return func_002CF6F8(func_002CC4B8(a0), a1, a2);
}

__attribute__((section(".text.func_002D5BB8")))
void *func_002D5BB8(void) {
    if (D_00460D78 == 0) {
        func_0031EEC8(&D_00460D78, &D_0044D200);
    }
    return &D_00460D78;
}

__attribute__((section(".text.func_002D5BF8")))
void *func_002D5BF8(void) {
    if (D_00460D80 == 0) {
        func_0031EEC8(&D_00460D80, &D_0044D210);
    }
    return &D_00460D80;
}

__attribute__((section(".text.GetOrInit_D00460D88_2D9EC8")))
void *GetOrInit_D00460D88_2D9EC8(void) {
    if (D_00460D88 == 0) {
        func_0031EEC8(&D_00460D88, &D_0044D3A0);
    }
    return &D_00460D88;
}

__attribute__((section(".text.func_002D9FF8")))
void *func_002D9FF8(void) {
    if (D_00460D90 == 0) {
        func_0031EEC8(&D_00460D90, &D_0044D3D8);
    }
    return &D_00460D90;
}

__attribute__((section(".text.func_002FFD88")))
int func_002FFD88(int a0) {
    if (a0) {
        func_002FBCC8();
        *(int*)((char*)a0 + 0x2B0) = 0;
        *(int*)((char*)a0 + 0xF0) = (int)&D_0044EE38;
    }
    return a0;
}

__attribute__((section(".text.func_003071A0")))
int func_003071A0(void) {
    if (D_00460D98 == 0) {
        func_0031EEC8(&D_00460D98, &D_00450098);
    }
    return (int)&D_00460D98;
}

__attribute__((section(".text.Get_460D70_3BAFF8")))
int Get_460D70_3BAFF8(void) {
    if (D_00460D70 == 0) {
        func_0031EEC8(&D_00460D70, &D_0045A5F8);
    }
    return (int)&D_00460D70;
}

__attribute__((section(".text.func_0037B5E0")))
void func_0037B5E0(int a0) {
    func_00374980(0, (void*)((char*)a0 + 0x16C));
    func_00374980(1, (void*)((char*)a0 + 0x18C));
    *(char*)((char*)a0 + 0x28) = 0;
    *(char*)((char*)a0 + 0x29) = 0;
}
