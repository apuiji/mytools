#ifndef CHRSET
#define CHRSET

#include<stddef.h>
#include<sys/types.h>
#include<wchar.h>

typedef struct{
	unsigned char(*c2wc)(wchar_t*, const char*);
	unsigned char(*wc2c)(char**, wchar_t);
}chrset_t;

extern size_t chrset_lengifwcs(const chrset_t*, const char*, size_t);
extern size_t chrset_sizeifstr(const chrset_t*, const wchar_t*, size_t);
extern char*chrset_idxifwcs(const chrset_t*, const char*, size_t, off_t);

extern int chrset_str2wcs(
	wchar_t**, size_t*, const chrset_t*, const char*, size_t);
extern int chrset_wcs2str(
	char**, size_t*, const chrset_t*, const wchar_t*, size_t);

extern const chrset_t
	chrset_ascii,
	chrset_gbk,
	chrset_utf8;

#endif//CHRSET
