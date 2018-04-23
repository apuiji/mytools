#include"ascii.h"

static size_t chrsize(const char*);
const chrset_t chrset_ascii = {
	chrsize:chrsize,
	isascii:isascii4varchrset,
};

size_t chrsize(const char*s){return 1;}

