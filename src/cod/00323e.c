/* cygnus-2.96 matched TU — CRI libadxe, recovered from recvx-decomp (CC0). */

typedef signed char Sint8;
typedef signed int  Sint32;
extern void func_0033F130(const Sint8 *msg);                     /* ADXERR_CallErrFunc1 */
extern Sint32 func_00323CF0(void *adxf, Sint32 nsct, void *buf); /* ADXF_ReadNw32 */
extern const Sint8 D_004517C8[];  /* "E0120401:'buf' isn't 64byte alignment.(ADXF_ReadNw)" */

__attribute__((section(".text.ADXF_ReadNw")))
Sint32 ADXF_ReadNw(void *adxf, Sint32 nsct, void *buf) {
    if (((Sint32)buf & 0x3F)) {
        func_0033F130(D_004517C8);
        return -3;
    }
    return func_00323CF0(adxf, nsct, buf);
}
