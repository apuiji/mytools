#include"ascii.h"

static size_t c2w(wchar_t*, const char*);
static size_t w2c(char**, wchar_t);
const chrset_t chrset_ascii = {
	c2w:c2w, w2c:w2c
};

size_t c2w(wchar_t*to, const char*c){
	if(to!=NULL)*to=*c;
	return 1;
}
size_t w2c(char**to, wchar_t wc){
	if(to!=NULL)*to=wc;
	return 1;
}

