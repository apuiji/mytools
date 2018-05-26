#include"../mem.h"

#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

static char shiftb(unsigned char*, size_t, char);
void*memshift(
	void*dest, const void*src, size_t size, size_t nb, memshift_op op
){
	if(!size)goto END;
	bool ismalloc = false;
	if(!dest){
		dest = malloc(size);
		if(!dest)goto END;
		ismalloc = true;
	}
	unsigned char dir=(op&0x10)>>4, type=op&3;
	size_t nB=nb>>3, remB;
	nb = nb&7;
	if(type>1){
		nB%=size; remB=size-nB;
		if(nB){
			char*tmp = malloc(nB);
			if(tmp==NULL){
				if(ismalloc)free(tmp);
				goto END;
			}
			if(dir){
				memcpy(tmp, src+remB, nB);
				memmove(dest+nB, src, remB);
				memcpy(dest, tmp, nB);
			}else{
				memcpy(tmp, src, nB);
				memmove(dest, src+nB, remB);
				memcpy(dest+remB, tmp, nB);
			}
			free(tmp);
		}
		if(nb){
			if(dir)
				*(char*)dest|=shiftb(dest, size, nb);
			else
				*(char*)(dest+size-1)|=shiftb(dest, size, -nb);
		}
	}else{
		char set = op==SAR&&(0x80&*(char*)src)?0xff:0;
		if((remB=size-nB)<0){
			memset(dest, set, size);
		}else{
			if(nB){
				if(dir){
					memmove(dest+nB, src, remB);
					memset(dest, set, nB);
					if(nb){
						shiftb(dest+nB, remB, nb);
						char msk; membitmsk(&msk,1,nb);
						if(set)*(char*)(dest+nB)|=msk;
						else *(char*)(dest+nB)&=~msk;
					}
				}else{
					memmove(dest, src+nB, remB);
					memset(dest+remB, set, nB);
					if(nb)shiftb(dest, remB, -nb);
				}
			}
		}
	}
	END:return dest;
}
char shiftb(unsigned char*p, size_t size, char nb){
	char msk; membitmsk(&msk,1,-nb);
	char oflow4ret, oflow=0, newoflow, remb;
	if(nb<0){
		oflow4ret = (p[0]&msk)>>(remb=8-(nb=-nb));
		for(off_t i=size-1;i>=0;--i){
			newoflow = (p[i]&msk)>>remb;
			p[i] = (p[i]<<nb)|oflow;
			oflow = newoflow;
		}
	}else{
		oflow4ret = (p[size-1]&msk)<<(remb=8-nb);
		for(off_t i=0;i<size;++i){
			newoflow = (p[i]&msk)<<nb;
			p[i] = (p[i]>>nb)|oflow;
			oflow = newoflow;
		}
	}
	return oflow4ret;
}

