/* cygnus-2.96 matched TU — CRI libadxe, recovered from recvx-decomp (CC0). */

typedef signed char  Sint8;
typedef signed short Sint16;
typedef signed int   Sint32;
extern Sint8 *func_00340B00(Sint8 *ibuf, Sint32 *sfreq, Sint32 *nch, Sint32 *bps, Sint32 *nsmpl);  /* AIFF_GetInfo */

__attribute__((section(".text.ADX_DecodeInfoAiff")))
Sint32 ADX_DecodeInfoAiff(Sint8 *ibuf, Sint32 ibuflen, Sint16 *dlen, Sint8 *code, Sint8 *bps, Sint8 *blksize, Sint8 *nch, Sint32 *sfreq, Sint32 *total_nsmpl, Sint32 *nsmpl_blk) {
    Sint8 *dt;
    Sint32 lsfreq, lnch, lbps, lnsmpl;
    if (ibuflen < 4096) { *dlen = 0; return -1; }
    dt = func_00340B00(ibuf, &lsfreq, &lnch, &lbps, &lnsmpl);
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
