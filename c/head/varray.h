#ifndef VARRAY
#define VARRAY

#include<sys/types.h>

typedef struct varray_t{
	void*point;
	size_t tsize, length, size;
}varray_t;
int varrayc(varray_t*, off_t, void*);
#define varrayr(me,i) ((void*)((me)->tsize*i+(char*)(me)->point))
int varrayu(varray_t*, off_t, void*);
int varrayd(varray_t*, off_t, size_t);
int varrayresize(varray_t*, size_t);

#endif//VARRAY
