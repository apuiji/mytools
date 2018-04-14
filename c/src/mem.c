#include<string.h>
#include"mem.h"

void memshift(void*p, size_t size, off_t off){
	if(off==0)return;
	off_t uoff = off<0?-off:off;
	size -= uoff;
	void *dest, *src;
	if(off<0){
		dest=p;	src=uoff+(char*)p;
	}else{
		dest=uoff+(char*)p;	src=p;
	}
	memmove(dest, src, size);
}

