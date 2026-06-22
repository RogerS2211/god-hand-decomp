/* cEmSetParam_roomInit — clear the room-set counters (0x8, 0xC) and run the
 * per-room init func_00295600.  sn-2.95.3-136. */

extern void func_00295600(void *);

__attribute__((section(".text.cEmSetParam_roomInit")))
void cEmSetParam_roomInit(void *a0) {
    *(int *)((char *)a0 + 0x8) = 0;
    *(int *)((char *)a0 + 0xC) = 0;
    func_00295600(a0);
}
