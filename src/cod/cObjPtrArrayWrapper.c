/* TU: cObjPtrArrayWrapper - recovered C++ class. */
#include "include_asm.h"

extern void func_00317FF0(void *vec, int *pos, int *val);
typedef struct {
    int *unk0;
    int *begin;   /* 0x4 */
    int *finish;  /* 0x8 */
    int *cap_end; /* 0xC */
} cVec;
typedef struct {
    cVec *vec;    /* 0x0 */
} cObjPtrArrayWrapper;

__attribute__((section(".text.cObjPtrArrayWrapper_insert")))
int *cObjPtrArrayWrapper_insert(cObjPtrArrayWrapper *this, int *position, int value)
{
    int local;
    cVec *v;
    unsigned int size;
    unsigned int cap;
    int index;
    int *b;
    int *vp;

    local = value;
    size = this->vec ? (this->vec->finish - this->vec->begin) : 0;
    v = this->vec;
    if (v) { b = v->begin; cap = v->cap_end - b; } else cap = 0;
    if (!(size < cap)) return 0;
    vp = &local;
    index = position - v->begin;
    if (v->finish != v->cap_end && position == v->finish) {
        if (position != 0) *position = local;
        v->finish = v->finish + 1;
    } else {
        func_00317FF0(v, position, vp);
    }
    return v->begin + index;
}
