#include"utf8.h"

static size_t c2w(wchar_t*, const char*);
static size_t w2c(char**, wchar_t);
const chrset_t chrset_gbk = {
	c2w:c2w, w2c:w2c
};

size_t c2w(wchar_t*to, const char*c){
	size_t chrsize = *c<0?2:1;
	if(to!=NULL)*to=chrsize>1?chrset_c2w(c):*c;
	return chrsize;
}
size_t w2c(char**to, wchar_t wc){
	
}

