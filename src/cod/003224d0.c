/* ee-2.9-991111 matched TU. */

extern struct object *D_00755C18;

struct dwarf_fde;
struct object {
  void *pc_begin;
  void *pc_end;
  struct dwarf_fde *fde_begin;
  struct dwarf_fde **fde_array;
  unsigned int count;
  struct object *next;
};

__attribute__((section(".text.func_003224D0")))
void func_003224D0(void *begin, struct object *ob)
{
  ob->fde_begin = begin;
  ob->fde_array = begin;
  ob->pc_begin = ob->pc_end = 0;
  ob->count = 0;
  ob->next = D_00755C18;
  D_00755C18 = ob;
}
