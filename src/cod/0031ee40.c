/* ee-2.9-991111 matched TU. */

struct __ti { const char *_name; };
__attribute__((section(".text.type_info___eq")))
int type_info___eq(struct __ti *self, struct __ti *arg)
{
  return (arg == self) || (func_003A5678(self->_name, arg->_name) == 0);
}
