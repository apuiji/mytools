#include"../chrset.h"

static unsigned char c2wc(wchar_t*, const char*);
static unsigned char wc2c(char**, wchar_t);
const chrset_t chrset_ascii = {
	c2wc:c2wc, wc2c:wc2c
};

unsigned char c2wc(wchar_t*to, const char*c){
	if(to!=NULL)*to=*c;
	return 1;
}
unsigned char wc2c(char**to, wchar_t wc){
	if(to!=NULL)**to=wc;
	return 1;
}

