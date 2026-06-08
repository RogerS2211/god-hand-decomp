/* SN ProDG ee-gcc 2.95.3 matched TU. */

extern void CustomIDWork_SetDisp(char *a0, int a1);

__attribute__((section(".text.SetCustomIDDispOneOrAll_1F29C0")))
void SetCustomIDDispOneOrAll_1F29C0(char *a0, int a1, int a2)
{
	char *p;
	int i;

	if (a2 != 0) {
		if (a1 == 0x12) {
			p = a0 + 0x60;
			for (i = 0x11; i >= 0; i--) {
				CustomIDWork_SetDisp(p, 1);
				p += 0x7C;
			}
		} else {
			CustomIDWork_SetDisp(a0 + (a1 * 0x7C + 0x60), 1);
		}
	} else {
		if (a1 == 0x12) {
			p = a0 + 0x60;
			for (i = 0x11; i >= 0; i--) {
				CustomIDWork_SetDisp(p, 0);
				p += 0x7C;
			}
		} else {
			CustomIDWork_SetDisp(a0 + (a1 * 0x7C + 0x60), 0);
		}
	}
}
