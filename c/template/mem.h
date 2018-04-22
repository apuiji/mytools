#ifndef MEM
#define MEM

#include<sys/types.h>

#define memget(p,i,t) (((t*)(p))[i])
extern void memshift(void*, size_t, off_t, int);

#endif//MEM
