#ifndef MEM
#define MEM

#include<sys/types.h>

#define memget(p,i,t) (((t*)(p))[i])
void memshift(void*, size_t, off_t);

#endif//MEM
