#ifndef VARRAY
#define VARRAY

#include<sys/types.h>

typedef struct varray_t{
	void*point;
	size_t esize, length, size;
}varray_t;
extern int varrayc(varray_t*, off_t, void*);
#define varrayr(me,i) ((void*)((me)->esize*i+(char*)(me)->point))
extern int varrayu(varray_t*, off_t, void*);
extern int varrayd(varray_t*, off_t, size_t);
extern int varrayresize(varray_t*, size_t);

#endif//VARRAY
