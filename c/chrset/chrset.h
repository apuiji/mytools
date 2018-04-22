#ifndef CHRSET
#define CHRSET

#include<sys/types.h>
#include<stdbool.h>

typedef struct chrset_t{
	bool fix;
	size_t(*chrsize)(const char*);
	bool(*isascii)(const char*);
	bool(*eqascii)(const char*, int);
}chrset_t;
extern char*strget(const char*, chrsize_fn, int, size_t*);
extern size_t strlenof(const char*, chrsize_fn, size_t*);

extern chrset_t
	chrset_ascii,
	chrset_gbk,
	chrset_utf8;

#endif//CHRSET
