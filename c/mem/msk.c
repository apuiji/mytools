#include"../mem.h"

#include<string.h>

void membitdmsk(void*dest, size_t size, ssize_t nof1){
	if(nof1<0){
		size_t div8 = (-nof1)>>3;
		if(size<div8){
			memset(dest, 0xff, size);
			return;
		}
		size_t rem = size-div8;
		char*c = rem + dest;
		memset(c--, 0xff, div8);
		size_t mod8 = (-nof1)&7;
		if(mod8)for(*c=1;--mod8;)*c=(*c<<1)&1;
		else *c = 0;
		memset(dest, 0, rem-1);
	}else if(nof1>0){
		size_t div8 = nof1>>3;
		if(size<div8){
			memset(dest, 0xff, size);
			return;
		}
		size_t rem = size-div8;
		memset(dest, 0xff, div8);
		char*c = rem + dest;
		size_t mod8 = nof1&7;
		if(mod8)for(*c=0x80;--mod8;)*c>>=1;
		else *c = 0;
		memset(c+1, 0, rem-1);
	}else memset(dest, 0, size);
}

