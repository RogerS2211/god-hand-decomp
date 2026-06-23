/* sn-2.95.3-136 matched TU. */

extern void *(*PTR_FUN_003c490c)(void);

__attribute__((section(".text.func_00320418")))
void ***func_00320418(void)
{
  char *eh = (char *)(*PTR_FUN_003c490c)();
  return (void ***)(eh + 4);
}
