/* cygnus-2.96 matched TU — CRI libadxe, recovered from recvx-decomp (CC0). */

typedef signed int Sint32;
typedef unsigned int Uint32;
extern Sint32 D_007561C0[];   /* dtx_sbuf */
extern char   D_003D8D40;     /* dtx_cd (sceSifClientData; pass &) */
extern Sint32 D_007562C0[];   /* dtx_rbuf */
extern void func_003B3128(void *cd, int rno, int mode, void *sbuf, int ssize,
                          void *rbuf, int rsize, void *efunc, void *epara);  /* sceSifCallRpc */

__attribute__((section(".text.dtx_destroy_rmt")))
void dtx_destroy_rmt(void *dtx) {
    D_007561C0[0] = (Sint32)dtx;
    func_003B3128(&D_003D8D40, 3, 0, D_007561C0, sizeof(Uint32), D_007562C0, 0, 0, 0);
}
