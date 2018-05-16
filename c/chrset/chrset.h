#ifndef CHRSET
#define CHRSET

#include<sys/types.h>
#include<stdbool.h>
#include<wchar.h>

typedef struct chrset_t chrset_t;
struct chrset_t{
	size_t(*c2w)(wchar_t*, const char*);
	size_t(*w2c)(char**, wchar_t);
};

extern size_t chrset_wcslen(
	const chrset_t*,
	const char*, const char*,
	size_t*);
extern size_t chrset_strlen(
	const chrset_t*,
	const wchar_t*, const wchar_t*,
	size_t*);
char*chrset_stridx(const chrset_t*, const char*, int, size_t*);

extern void chrset_cs2ws(const chrset_t*, wchar_t**, const char*, size_t);
extern void chrset_ws2cs(const chrset_t*, char**, const wchar_t*, size_t);
extern wchar_t chrset_c2w(const char*);

#endif//CHRSET
