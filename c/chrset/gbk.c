#include"gbk.h"

static unsigned char c2wc(wchar_t*, const char*);
static unsigned char wc2c(char**, wchar_t);
const chrset_t chrset_gbk = {
	c2wc:c2wc, wc2c:wc2c
};

unsigned char c2wc(wchar_t*to, const char*c){
	size_t chrsize = *c<0?2:1;
	if(to!=NULL)*to=chrsize>1?(*(wchar_t*)c)>>(sizeof(wchar_t)-2):*c;
	return chrsize;
}
unsigned char wc2c(char**to, wchar_t wc){
	size_t chrsize = wc&0xff00?2:1;
	if(to!=NULL){
		if(chrsize>1)*(wchar_t*)to=wc;
		else *to=(char)wc;
	}
	return chrsize;
}

