/* cygnus-2.96 matched TU — CRI libadxe, recovered from recvx-decomp (CC0). */

typedef signed char Sint8;
typedef signed int  Sint32;
extern Sint32 func_003A50B4(const void *a, const void *b, unsigned n);  /* memcmp */
extern const Sint8 D_00457050[];  /* ".snd" */
extern const Sint8 D_00457058[];  /* ".sd"  */

__attribute__((section(".text.ADXB_CheckAu")))
Sint32 ADXB_CheckAu(Sint8 *ibuf) {
    if ((func_003A50B4(ibuf, D_00457050, 4) == 0) || (func_003A50B4(ibuf, D_00457058, 4) == 0)) {
        return 1;
    }
    return 0;
}

typedef signed char  Sint8;
typedef signed short Sint16;
typedef signed int   Sint32;
extern Sint8 *func_00341480(Sint8 *ibuf, Sint32 ibuflen, Sint32 *sfreq, Sint32 *nch, Sint32 *bps, Sint32 *nsmpl, Sint32 *cdc);  /* AU_GetInfo */

__attribute__((section(".text.ADX_DecodeInfoAu")))
Sint32 ADX_DecodeInfoAu(Sint8 *ibuf, Sint32 ibuflen, Sint16 *dlen, Sint8 *code, Sint8 *bps, Sint8 *blksize, Sint8 *nch, Sint32 *sfreq, Sint32 *total_nsmpl, Sint32 *nsmpl_blk, Sint32 *cdc) {
    Sint8 *dt;
    Sint32 lsfreq, lnch, lbps, lnsmpl;
    if (ibuflen < 8) { *dlen = 0; return -1; }
    dt = func_00341480(ibuf, ibuflen, &lsfreq, &lnch, &lbps, &lnsmpl, cdc);
    if (dt == 0) { return -1; }
    *dlen = dt - ibuf;
    if ((*dlen * 1024) <= 0) { return -1; }
    *sfreq = lsfreq;
    *nch = lnch;
    *bps = lbps;
    *total_nsmpl = lnsmpl;
    *code = -1;
    *blksize = (*nch * *bps) / 8;
    *nsmpl_blk = 1;
    return 0;
}
