/* sn-2.95.3-136 matched TU. */

struct __sfile {
  char _pad0[0xE];
  short _file;
  char _pad1[0x44];
  void *_data;
};

__attribute__((section(".text.func_003A6EC8")))
int func_003A6EC8(void *cookie)
{
  struct __sfile *fp = (struct __sfile *)cookie;
  return func_003ADF50(fp->_data, fp->_file);
}
