#include"../mem.h"

#include<stdlib.h>
#include<string.h>

static char cbitmsk(char);
void*membitmsk(void*dest, size_t size, ssize_t nof1){
	if(!dest)if(!(dest=malloc(size)))goto END;
	if(!nof1){
		memset(dest, 0x00, size);
		goto END;
	}
	size_t unof1 = nof1<0?-nof1:nof1;
	size_t div8 = unof1>>3;
	if(size<div8){
		memset(dest, 0xff, size);
		goto END;
	}
	size_t rem8 = size-div8;
	char mod8 = unof1&7;
	if(nof1<0){
		char*c = dest+rem8;
		memset(c, 0xff, div8);
		c[-1] = cbitmsk(-mod8);
		memset(dest, 0, rem8-1);
	}else{
		char*c = dest+div8;
		memset(dest, 0xff, div8);
		c[0] = cbitmsk(mod8);
		memset(c+1, 0, rem8-1);
	}
	END:return dest;
}
char cbitmsk(char nof1){
	char msk;
	if(nof1<-7||nof1>7)msk=0xff;
	else if(nof1<0)for(msk=0x01;++nof1;)msk=(msk<<1)&1;
	else if(nof1>0)for(msk=0x80;--nof1;)msk>>=1;
	else msk=0;
	return msk;
}

