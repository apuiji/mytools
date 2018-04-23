#ifndef CHRSET
#define CHRSET

#include<sys/types.h>
#include<stdbool.h>

typedef struct chrset_t chrset_t;
struct chrset_t{
	size_t(*chrsize)(const char*);
	bool(*isascii)(const chrset_t*, const char*, char*, size_t*);
};

extern size_t strlenof(const chrset_t*, const char*, size_t*);
extern char* strgetof(const chrset_t*, const char*, int, size_t*);

extern bool isascii4varchrset(
	const chrset_t*, const char*, char*, size_t*
);

#endif//CHRSET
