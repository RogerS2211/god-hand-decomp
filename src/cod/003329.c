/* cygnus-2.96 matched TU — CRI libadxe (dvCi filesystem driver),
   recovered from recvx-decomp (CC0) and re-matched under ee-gcc 2.96.
   Matches only with -freorder-blocks disabled (see compile_config.json). */

typedef signed char  Sint8;
typedef unsigned int Uint32;

extern unsigned int strlen(const char *);   /* EE-vectorized libc strlen @ 0x003A58DC */

/* Upper-cases a path and flips '/' to '\\' (DVD "large" / yen-slash form). */
__attribute__((section(".text.dvci_to_large_to_yen")))
void dvci_to_large_to_yen(Sint8 *fname) {
    Uint32 len;
    Uint32 lp;

    len = strlen((const char *)fname);

    for (lp = 0; lp < len; lp++) {
        if (fname[lp] == '/') {
            fname[lp] = '\\';
        }
        if ((fname[lp] >= 'a') && (fname[lp] <= 'z')) {
            fname[lp] -= ' ';
        }
    }
}
