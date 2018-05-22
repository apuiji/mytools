#include"gbk.h"

static size_t c2wc(wchar_t*, const char*);
static size_t wc2c(char**, wchar_t);
const chrset_t chrset_gbk = {
	c2wc:c2wc, wc2c:wc2c
};

size_t c2wc(wchar_t*to, const char*c){
	size_t chrsize = *c<0?2:1;
	if(to!=NULL)*to=chrsize>1?*(wchar_t)c:*c;
	return chrsize;
}
size_t wc2c(char**to, wchar_t wc){
	size_t chrsize = wc<0?2:1;
	if(to!=NULL){
		if(chrsize>1)*(wchar_t*)to=wc;
		else *to=(char)wc;
	}
	return chrsize;
}

