#include"../mem.h"

void memshift(void*p, size_t size, ssize_t off, int c){
	if(off==0)return;
	if(off<0){
		memmove(p, (char*)p-off, size+off);
		memset((char*)p+size+off, c, -off);
	}else{
		memmove((char*)p+off, p, size-off);
		memset(p, c, off);
	}
}
void memshiftb(void*p, size_t size, int off, int c){
	if(!off)return;
	char msk, overflow, *c=(char*)p;
	if(off<0){
		msk = ~memmsk(off=-off);
		size_t esize;
		if(size>=sizeof(long)){
			esize = sizeof(long)
			*(long*)c = *(long*)c<<off;
			c+=esize;	size-=esize;
			while(size>=esize){
				
			}
		}
		while(size>=esize){
			*()
			c+=esize;	size-=esize;
		}
		#define GAP(T) if(gap=sizeof(T)-sizeof(char))while(size>sizeof(T)){\
			*(T*)c = *(T*)c<<off;\
			c+=gap;	size-=gap;\
		}else goto OVER;
		GAP(long)	GAP(int)	GAP(short)
		#undef GAP
		OVER:
	}else{
		char msk=memmsk(8-off), overflow;
	}
}

