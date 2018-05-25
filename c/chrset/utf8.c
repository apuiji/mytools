#include"utf8.h"

static size_t c2wc(wchar_t*, const char*);
static size_t wc2c(char**, wchar_t);
const chrset_t chrset_utf8 = {
	c2wc:c2wc, wc2c:wc2c
};

size_t c2wc(wchar_t*to, const char*c){
	unsigned char uc = *c;
	size_t chrsize = uc>0xfc?6:uc>0xf8?5:uc>0xf0?4:uc>0xe0?3:uc>0xc0?2:1;
	if(to!=NULL)switch(chrsize){
	case 1:*to=*c;break;
	case 2:
	}
	return chrsize;
}

