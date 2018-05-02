#ifndef VARRAY
#define VARRAY

#include<stddef.h>

typedef struct varray_t{
	void*point;
	size_t esize, length, mxleng;
}varray_t;
extern int varrayc(varray_t*, int, void*);
#define varrayr(_me,_i) ({\
	varray_t*me=(varray_t*)_me;	int i=(int)_i;\
	void*out = me->esize*i+(char*)me->point;\
	out;\
})
extern int varrayu(varray_t*, int, void*);
extern int varrayd(varray_t*, int, size_t);
extern int varrayreleng(varray_t*, size_t);

#endif//VARRAY
