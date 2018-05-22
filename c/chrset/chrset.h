#ifndef CHRSET
#define CHRSET

#include<stddef.h>
#include<wchar.h>

typedef struct chrset_t chrset_t;
struct chrset_t{
	size_t(*c2wc)(wchar_t*, const char*);
	size_t(*wc2c)(char**, wchar_t);
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

extern void chrset_s2ls(const chrset_t*, wchar_t**, const char*, size_t);
extern void chrset_ls2s(const chrset_t*, char**, const wchar_t*, size_t);

#endif//CHRSET
