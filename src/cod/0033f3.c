/* cygnus-2.96 matched TU — CRI libadxe (ADX error-message helpers),
   recovered from recvx-decomp (CC0) and re-matched under ee-gcc 2.96. */

typedef signed char Sint8;
typedef signed int  Sint32;

extern unsigned int strlen(const char *);                    /* libc strlen  @ 0x003A58DC */
extern char *strncat(char *, const char *, unsigned int);    /* libc strncat @ 0x003A5A20 */
extern void ADXERR_ItoA(Sint32 val, Sint8 *str, Sint32 len); /* CRI ADXERR_ItoA @ 0x0033F240 */
extern const Sint8 D_00456938[];                             /* the literal " " in retail .rodata */

/* Renders "<val> <val2>" into str: val, then a space, then val2 in the
   remaining width. */
__attribute__((section(".text.ADXERR_ItoA2")))
void ADXERR_ItoA2(Sint32 val, Sint32 val2, Sint8 *str, Sint32 len) {
    ADXERR_ItoA(val, str, len);
    strncat((char *)str, (const char *)D_00456938, (len - strlen((const char *)str)) - 1);
    ADXERR_ItoA(val2, &str[strlen((const char *)str)], 4 - strlen((const char *)str));
}
