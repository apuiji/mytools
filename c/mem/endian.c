#include"../mem.h"

#include<stdlib.h>
#include<sys/types.h>

enum memendian memendian(){
	static int v = 0;
	if(v)goto END;
	long l = 1;
	v = *(char*)&l?LITTLE:BIG;
	END:return v;
}
void*memendianrvs(void*dest, const void*src, size_t size){
	if(!dest)if(!(dest=malloc(size)))goto END;
	for(off_t i=0,j=size-1,k=size>>1;i<k;){
		char ci=*(char*)(src+i), cj=*(char*)(src+j);
		*(char*)(dest+j)=ci; *(char*)(dest+i)=cj;
		++i; --j;
	}
	END:return dest;
}

