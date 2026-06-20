/* lw $v0, 0x530($a0); jr $ra; slt $v0, $zero, $v0 */
__attribute__((section(".text.func_00291FD8")))
int func_00291FD8(char *arg0) { return *(int *)(arg0 + 0x530) > 0; }
