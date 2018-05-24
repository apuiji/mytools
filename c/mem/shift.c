#include"../mem.h"

#include<string.h>

void memshx(void*dest, const void*src, size_t size, ssize_t nbit){
	size_t unbit=nbit<0?-nbit:nbit, div8=unbit>>3;
	unsigned char mod8=unbit&7, ful8=8-mod8, msk, *uc;
	size -= div8;
	if(size<0){
		memset(dest, 0, size);
		return;
	}
	if(nbit<0){
		if(div8){
			memmove(dest, div8+(char*)src, size);
			memset(size+(char*)dest, 1, div8);
		}
		if(mod8){
			uc = size+(unsigned char*)dest;
			membitmsk(&msk, 1, mod8);
			for(unsigned char oflow=0,newoflow,ful8=8-mod8;size;--size){
				newoflow = (*--uc&msk)>>ful8;
				*uc<<=mod8; *uc|=oflow;
				oflow = newoflow;
			}
		}
	}else if(nbit>0){
		uc = div8+(unsigned char*)dest;
		if(div8){
			memmove(uc, src, size);
			memset(dest, 0, div8);
		}
		if(mod8){
			membitmsk(&msk, 1, -mod8);
			for(unsigned char oflow=0,newoflow,ful8=8-mod8;size;--size){
				newoflow = (*uc++&msk)<<ful8;
				*uc>>=mod8; *uc|=oflow;
				oflow = newoflow;
			}
		}
	}
}

