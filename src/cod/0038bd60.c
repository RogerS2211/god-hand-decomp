/* gbump__9streambufi — streambuf::gbump(int): advance the get pointer by a1,
 * choosing field 0x24 or 0x4 depending on flag bit 0x100. */

__attribute__((section(".text.gbump__9streambufi")))
void gbump__9streambufi(void *a0, int a1) {
    if (*(int *)a0 & 0x100) *(int *)((char *)a0 + 0x24) += a1;
    else *(int *)((char *)a0 + 0x4) += a1;
}
