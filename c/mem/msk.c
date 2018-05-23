#include"../mem.h"

#include<string.h>

void membitdmsk(void*p, size_t nbytes, ssize_t nof1){
	if(nof1<0){
		size_t div8 = -nof1>>3;
		if(div8>=nbytes){
			memset(p, 0xff, nbytes);
			return;
		}
		size_t rem = nbytes-div8;
		char*c = rem+(char*)p;
		memset(c--, 0xff, div8);
		size_t mod8 = -nof1&7;
		if(mod8)for(*c=1;--mod8;)*c=(*c<<1)&1;
		else *c = 0;
		memset(p, 0, rem-1);
	}else if(nof1>0){
		size_t div8 = nof1>>3;
		if(div8>=nbytes){
			memset(p, 0xff, nbytes);
			return;
		}
		size_t rem = nbytes-div8;
		memset(p, 0xff, div8);
		char*c = rem+(char*)p;
		size_t mod8 = nof1&7;
		if(mod8)for(*c=0x80;--mod8;)*c=*c>>1;
		else *c = 0;
		memset(c+1, 0, rem-1);
	}else memset(p, 0, nbytes);
}

