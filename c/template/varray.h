#ifndef VARRAY
#define VARRAY

#include<sys/types.h>

typedef struct varray_t{
	void*hook;
	size_t esize, length, mxleng;
}varray_t;

extern int varrayc(varray_t*, int, void*);
extern void*varrayr(varray_t*, int);
extern int varrayu(varray_t*, int, void*);
extern int varrayd(varray_t*, int, ssize_t);
extern int varrayreleng(varray_t*, size_t);

#endif//VARRAY