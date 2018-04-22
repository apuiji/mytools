#include"ascii.h"

static size_t chrsize(const char*);
chrset_t chrset_ascii = {
	chrsize:chrsize,
	isascii:isascii4varchrset,
	eqascii:eqascii4varchrset,
};

size_t chrsize(const char*s){return 1;}

