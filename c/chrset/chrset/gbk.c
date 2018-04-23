#include"utf8.h"

static size_t chrsize(const char*);
const chrset_t chrset_gbk = {
	chrsize:chrsize,
	isascii:isascii4varchrset,
};

size_t chrsize(const char*s){return *s>0x80?2:1;}

