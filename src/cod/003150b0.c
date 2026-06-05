extern int D_00747A34;
extern char D_00754C10[];

__attribute__((section(".text.func_003150B0")))
int func_003150B0(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x610, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x610);
    return SetObjVtable_19D7B0(s0);
}

__attribute__((section(".text.func_00315120")))
int func_00315120(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x800, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x800);
    return InitObjVu0Block_19D9C0(s0);
}

__attribute__((section(".text.func_00315190")))
int func_00315190(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x860, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x860);
    return InitVu0ObjBlock_19DC48(s0);
}

__attribute__((section(".text.func_00315200")))
int func_00315200(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x860, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x860);
    return InitVu0ObjData_19DED0(s0);
}

__attribute__((section(".text.func_00315270")))
int func_00315270(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x7A0, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x7A0);
    return InitObjVu0Array_19E1C0(s0);
}

__attribute__((section(".text.func_003152E0")))
int func_003152E0(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x9E0, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x9E0);
    return InitObjW17Slots_19E448(s0);
}

__attribute__((section(".text.func_00315350")))
int func_00315350(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x860, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x860);
    return InitObjW17bSlots_19E6C0(s0);
}

__attribute__((section(".text.func_003153C0")))
int func_003153C0(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x860, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x860);
    return InitObjW17cSlots_19E938(s0);
}

__attribute__((section(".text.func_00315430")))
int func_00315430(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x7A0, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x7A0);
    return InitObjW17dSlots_19EBB8(s0);
}

__attribute__((section(".text.func_003154A0")))
int func_003154A0(void){
    void *s0;
    if (D_00747A34 & 0x10000) return 0;
    s0 = func_0030EE08(0x860, 0x10, D_00754C10);
    if (s0 == 0) return 0;
    func_003A52F0(s0, 0, 0x860);
    return InitObjW17eSlots_19EE30(s0);
}
