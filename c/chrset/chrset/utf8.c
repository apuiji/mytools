#include"utf8.h"

static size_t c2w(wchar_t*, const char*);
static size_t w2c(char**, wchar_t);
const chrset_t chrset_utf8 = {
	c2w:c2w, w2c:w2c
};

size_t c2w(wchar_t*to, const char*c){
	unsigned char uc = *s;
	if(uc>0xfc)return 6;
	if(uc>0xf8)return 5;
	if(uc>0xf0)return 4;
	if(uc>0xe0)return 3;
	if(uc>0xc0)return 2;
	return 1;
}

