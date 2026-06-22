/* ostream___ls_38A478 — ostream::operator<<(manipulator): invoke the manipulator
 * a1 on the stream a0 and return its result.  sn-2.95.3-136. */

__attribute__((section(".text.ostream___ls_38A478")))
void *ostream___ls_38A478(void *a0, void *(*a1)(void *)) {
    void *r = a1(a0);
    return r;
}
