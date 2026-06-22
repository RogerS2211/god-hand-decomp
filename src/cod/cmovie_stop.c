/* cMovie_Stop — stop the active movie: if the player object exists
 * (func_002B4F98), tear it down (func_002D42E0), then clear the playing flags
 * (bit 0x2000) in the movie-system state D_00747A84.  sn-2.95.3-136. */

extern void *func_002B4F98(void);
extern void func_002D42E0(void *);
extern int D_00747A84;

__attribute__((section(".text.cMovie_Stop")))
void cMovie_Stop(void) {
    void *v0 = func_002B4F98();
    if (v0)
        func_002D42E0(v0);
    D_00747A84 &= ~0x2000;
}
