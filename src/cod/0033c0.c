/* cygnus-2.96 matched TU — CRI ADX middleware (libadxe).
   Source recovered from recvx-decomp (CC0) and re-matched under ee-gcc 2.96. */

extern void Forward33B658_33E678(void);            /* ADXCRS_Lock  */
extern void Forward33B670_33E690(void);            /* ADXCRS_Unlock */
extern void *func_003A52F0(void *s, int c, int n); /* memset       */

typedef struct { char _pad[0x30]; } ADX_AMP;       /* sizeof == 0x30 (retail) */

__attribute__((section(".text.ADXAMP_Destroy")))
void ADXAMP_Destroy(ADX_AMP *amp) {
    if (amp != 0) {
        Forward33B658_33E678();
        func_003A52F0(amp, 0, sizeof(ADX_AMP));
        Forward33B670_33E690();
    }
}
