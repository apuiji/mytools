#ifndef WCONV_H
#define WCONV_H

#include<wchar.h>
#include"tmpl/snake.h"

typedef void *wconv_t;

extern wconv_t wconv_open(const char*);
extern void wconv_close(wconv_t);

extern int wconv_mb2wc(wconv_t, wchar_t*, snake_t);
extern int wconv_wc2mb(wconv_t, snake_t, wchar_t);
extern size_t wconv_mbs2wcs(wconv_t, snake_t, snake_t);
extern size_t wconv_wcs2mbs(wconv_t, snake_t, snake_t);

#endif//WCONV_H
