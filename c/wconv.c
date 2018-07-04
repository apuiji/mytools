#include"wconv.h"

#include<iconv.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct{
	iconv_t mb2wc, wc2mb;
}wconv_impl;

wconv_t wconv_open(const char*charset){
	wconv_impl*wconv = (wconv_impl*)malloc(sizeof(wconv_impl));
	wconv->mb2wc = iconv_open("WCHAR_T", charset);
	if(!wconv->mb2wc)goto MB2WC;
	wconv->wc2mb = iconv_open(charset, "WCHAR_T");
	if(!wconv->wc2mb)goto WC2MB;
	return (wconv_t)wconv;
	WC2MB:
	iconv_close(wconv->mb2wc);
	MB2WC:
	free(wconv);
	return NULL;
}
void wconv_close(wconv_t _wconv){
	wconv_impl*wconv = (wconv_impl*)_wconv;
	iconv_close(wconv->mb2wc);
	iconv_close(wconv->wc2mb);
	free(wconv);
}

static int xx2yy(iconv_t, snake_t, wchar_t*, bool);
int wconv_mb2wc(wconv_t wconv, wchar_t*wc, snake_t mb){
	return xx2yy(((wconv_impl*)wconv)->mb2wc, mb, wc, true);
}
int wconv_wc2mb(wconv_t wconv, snake_t mb, wchar_t wc){
	return xx2yy(((wconv_impl*)wconv)->wc2mb, mb, &wc, false);
}
int xx2yy(iconv_t ic, snake_t _mb, wchar_t*wc, bool mb2wc){
	static char enough[64];
	static wchar_t nowc;
	size_t always = sizeof(wchar_t);
	snake_t mb = _mb;
	if(!mb.hook)mb.hook=enough;
	if(!wc)wc=&nowc;
	char**buf[2] = { (char**)&mb.hook, (char**)&wc };
	size_t*left[2] = { &mb.count, &always };
	int i=mb2wc?0:1, j=(i+1)%2;
	iconv(ic, buf[i], left[i], buf[j], left[j]);
	return _mb.count - mb.count;
}

static size_t xxs2yys(iconv_t, snake_t, snake_t);
size_t wconv_mbs2wcs(wconv_t wconv, snake_t wcs, snake_t mbs){
	wcs.count *= sizeof(wchar_t);
	return xxs2yys(((wconv_impl*)wconv)->mb2wc, wcs, mbs)/sizeof(wchar_t);
}
size_t wconv_wcs2mbs(wconv_t wconv, snake_t mbs, snake_t wcs){
	wcs.count *= sizeof(wchar_t);
	return xxs2yys(((wconv_impl*)wconv)->wc2mb, mbs, wcs);
}
size_t xxs2yys(iconv_t ic, snake_t _yys, snake_t xxs){
	snake_t yys = _yys;
	iconv(ic, (char**)&xxs.hook, &xxs.count, (char**)&yys.hook, &yys.count);
	return _yys.count - yys.count;
}

