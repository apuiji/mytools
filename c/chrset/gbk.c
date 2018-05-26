#include"../chrset.h"

#include<string.h>

static unsigned char c2wc(wchar_t*, const char*);
static unsigned char wc2c(char**, wchar_t);
const chrset_t chrset_gbk = {
	c2wc:c2wc, wc2c:wc2c
};

unsigned char c2wc(wchar_t*to, const char*c){
	size_t chrsize = *c<0?2:1;
	if(to==NULL)goto END;
	*to = 0;
	void*dest = sizeof(wchar_t)-chrsize+(void*)to;
	memcpy(dest, c, chrsize);
	END:return chrsize;
}
unsigned char wc2c(char**to, wchar_t wc){
	size_t chrsize = wc&0xff00?2:1;
	if(to==NULL)goto END;
	void*src = sizeof(wchar_t)-chrsize+(void*)&wc;
	memcpy(*to, src, chrsize);
	END:return chrsize;
}

