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
	char i=0, j=chrsize-1, k=j, tmp[6];
	memcpy(tmp,c,chrsize);
	for(char*dest=tmp+j;i<k;dest=tmp+--j)memshl(dest,dest,++i,2);
	memshl(tmp, tmp, chrsize, chrsize+1);
	memshr(tmp, tmp, 6, (i<<1)+chrsize+1);
	*to=0; char gap=chrsize-sizeof(wchar_t);
	if(gap<0)
		memcpy(-gap+(char*)to, tmp, chrsize);
	else
		memcpy(to, tmp+gap, sizeof(wchar_t));
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
	if(!to)goto END;
	if(chrsize==1){
		**to=wc; goto END;
	}
	wc <<= (sizeof(wchar_t)<<3)-nchcd;
	char msk1; membitmsk(&msk1, 1, chrsize);
	char msk2; membitmsk(&msk2, 1, chrsize-7);
	**to = msk1|(wc>>(sizeof(wchar_t)-7+chrsize))&msk2;
	wc <<= chrsize+1;
	for(char i=1,shift=(char)sizeof(wchar_t)-6,*c=1+*to;i<chrsize;++i){
		*c=0x80|(wc>>shift)&0x3f; wc<<=6; ++c;
	}
	END:return chrsize;
}

