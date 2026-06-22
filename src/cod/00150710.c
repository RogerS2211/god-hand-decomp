/* func_00150710 — store a position vector (x, y, z) at 0x0/0x4/0x8 and 1.0 at
 * 0xC (homogeneous w). */

__attribute__((section(".text.func_00150710")))
void func_00150710(void *a0, float x, float y, float z) {
    *(float *)((char *)a0 + 0x0) = x;
    *(float *)((char *)a0 + 0x4) = y;
    *(float *)((char *)a0 + 0x8) = z;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}
