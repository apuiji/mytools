#include"../chrset.h"

#include<string.h>
#include"../mem.h"

static unsigned char c2wc(wchar_t*, const char*);
static unsigned char wc2c(char**, wchar_t);
const chrset_t chrset_utf8 = {
	c2wc:c2wc, wc2c:wc2c
};

unsigned char c2wc(wchar_t*to, const char*c){
	unsigned char uc=*c, chrsize=
		uc>0xfc?6:uc>0xf8?5:uc>0xf0?4:
		uc>0xe0?3:uc>0xc0?2:1;
	if(!to)goto END;
	if(chrsize==1){
		*to=*c; goto END;
	}
	char tmp[6]; memcpy(tmp,c,chrsize);
	{//var tmp : 6b-size charCode in big-endian-mode
		char i = 0;
		for(char j=chrsize-1,k=j,*dest=tmp+j;i<k;dest=tmp+--j)
			memshl(dest,dest,++i,2);
		memshl(tmp, tmp, chrsize, chrsize+1);
		memshr(tmp, tmp, 6, (i<<1)+chrsize+1);
	}*to=0;{//copy tmp to *to as a big-endian-mode wchar_t
		char gap=chrsize-sizeof(wchar_t);
		if(gap<0)
			memcpy(-gap+(char*)to, tmp, chrsize);
		else
			memcpy(to, tmp+gap, sizeof(wchar_t));
	}
	if(memendian()<0)memendianrvs(to, to, sizeof(wchar_t));
	END:return chrsize;
}
unsigned char wc2c(char**to, wchar_t wc){
	unsigned char chrsize, nchcd;
	if(wc<0x00000080){
		chrsize=1;
	}else if(wc<0x00000800){
		chrsize=2; nchcd=11;
	}else if(wc<0x00010000){
		chrsize=3; nchcd=16;
	}else if(wc<0x00200000){
		chrsize=4; nchcd=21;
	}else if(wc<0x04000000){
		chrsize=5; nchcd=26;
	}else{
		chrsize=6; nchcd=31;
	}
	if(to)if(chrsize==1)**to=wc;else{
		//consider wc as a left-out bit-stream
		char nbofwc = sizeof(wchar_t)<<3;
		wc <<= nbofwc-nchcd;
		//export count-mask in 1st char
		char shift = 7-chrsize;
		char msk1; membitmsk(&msk1, 1, chrsize);
		char msk2; membitmsk(&msk2, 1, -shift);
		**to = msk1|(wc>>(nbofwc-shift))&msk2;
		wc<<=shift;
		//export charCode to chars
		for(char i=1,fix=nbofwc-6,*c=1+*to;i<chrsize;++i){
			*c = 0x80|(wc>>fix)&0x3f; wc<<=6; ++c;
		}
	}
	return chrsize;
}

