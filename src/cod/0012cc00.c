__attribute__((section(".text.func_003059A8")))
int func_003059A8(void *a0, int a1, void *a2) {
    int sp[4];
    int r;
    if (a1 == 5) {
        return 0;
    }
    r = func_003058D8(a0, a1);
    if (r != 0) {
        return func_00305858(r, a2);
    }
    func_003053C0(sp, a1);
    return 0;
}

__attribute__((section(".text.func_003733C8")))
void func_003733C8(void *a0) {
    if (func_00373A50(a0) != 0) {
        if (func_00373B20(a0) == 1) {
            func_00374318(a0);
        } else {
            func_00373D48(a0);
        }
        func_003A52F0(a0, 0, 0x84);
    }
}

__attribute__((section(".text.func_0012CC00")))
void func_0012CC00(char *a0)
{
	char *p;

	p = *(char **)(a0 + 0x644);
	if (p != 0) {
		if ((*(int *)(a0 + 0x15F4) & 0x800000) == 0) {
			if (*(int *)(p + 0x564) == 0x26A) {
				func_00306168(0, 0x79, 2);
			}
			func_00306168(0, 0x61, 2);
			*(int *)(a0 + 0x644) = 0;
		}
	}
}

__attribute__((section(".text.func_0012ECF0")))
void func_0012ECF0(char *a0)
{
	char *p;
	char *vt;
	int next;

	if (*(int *)(a0 + 0x190) != 0) {
		do {
			p = *(char **)(a0 + 0x190);
			next = *(int *)p;
			if (p != 0) {
				vt = *(char **)(p + 0x5C);
				(*(void (**)(char *, int))(vt + 0xC))(p + *(short *)(vt + 8), 3);
			}
			*(int *)(a0 + 0x190) = next;
			*(int *)(a0 + 0x194) = *(int *)(a0 + 0x194) - 1;
		} while (next != 0);
	}
}

__attribute__((section(".text.func_00147A48")))
void func_00147A48(void *a0, int a1, int a2, int a3, int t0)
{
	unsigned char e;

	e = t0;
	func_001476D0(a0);
	func_00147B60(a0, a0, a2, e);
	func_00147BF8(a0, a0, a3);
}
