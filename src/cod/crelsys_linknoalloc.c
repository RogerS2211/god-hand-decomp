/* cRelSys_linkNoAlloc — set REL-table entry a3 (stride 8) to (a1, a2) without
 * allocating, via SetValueAndValidate_2BE630.  sn-2.95.3-136. */

extern void SetValueAndValidate_2BE630(void *, int, int);

__attribute__((section(".text.cRelSys_linkNoAlloc")))
void cRelSys_linkNoAlloc(void *a0, int a1, int a2, int a3) {
    SetValueAndValidate_2BE630((char *)a0 + a3 * 8, a1, a2);
}
