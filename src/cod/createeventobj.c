/* CreateEventObj — allocate an event object (func_00312AB0) and initialise it
 * (func_0030FB20), returning the initialised object.  sn-2.95.3-136. */

extern void *func_00312AB0(void *);
extern void *func_0030FB20(void *, void *);

__attribute__((section(".text.CreateEventObj")))
void *CreateEventObj(void *a0) {
    void *v0 = func_00312AB0(a0);
    return func_0030FB20(a0, v0);
}
