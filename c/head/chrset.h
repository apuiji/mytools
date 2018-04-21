#ifndef CHRSET
#define CHRSET

#include<sys/types.h>

typedef size_t(*chrsize_fn)(const char*);
extern char*strget(const char*, chrsize_fn, int, size_t*);
extern size_t strlenof(const char*, chrsize_fn, size_t*);
extern chrsize_fn
	chrsize_ascii,
	chrsize_gbk,
	chrsize_utf8;

#endif//CHRSET
