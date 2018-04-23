#include"utf8.h"

static size_t chrsize(const char*);
const chrset_t chrset_utf8 = {
	chrsize:chrsize,
	isascii:isascii4varchrset,
};

size_t chrsize(const char*s){
	unsigned char ch = *s;
	if(ch>0xfc)return 6;
	if(ch>0xf8)return 5;
	if(ch>0xf0)return 4;
	if(ch>0xe0)return 3;
	if(ch>0xc0)return 2;
	return 1;
}

