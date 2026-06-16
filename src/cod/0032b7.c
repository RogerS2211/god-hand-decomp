/* cygnus-2.96 matched TU — CRI libadxe, recovered from recvx-decomp (CC0). */

typedef unsigned short Uint16;
typedef signed char   Sint8;
typedef signed int    Sint32;
#define BSWAP_U16(_val) (Uint16)((*(Uint16*)_val >> 8) | (*(Uint16*)_val << 8))

__attribute__((section(".text.ADXT_IsEndcode")))
Sint32 ADXT_IsEndcode(Sint8 *adr, Sint32 siz, Sint32 *endsiz) {
    if (siz <= 1) {
        return 0;
    }
    if (BSWAP_U16(adr) != 0x8001) {
        return 0;
    }
    *endsiz = siz;
    return 1;
}
