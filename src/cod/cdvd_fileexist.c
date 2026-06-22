/* cDvd_FileExist — return whether the DVD file handle (D_00580D40) reports the
 * file present (func_001FFA68 non-zero).  sn-2.95.3-136. */

extern int func_001FFA68(void *);
extern char D_00580D40;

__attribute__((section(".text.cDvd_FileExist")))
int cDvd_FileExist(void *a0) {
    return func_001FFA68(&D_00580D40) != 0;
}
