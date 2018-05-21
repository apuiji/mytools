#ifndef STRBUF
#define STRBUF

#include<stddef.h>

extern void*strbufcreate();
extern size_t strbufleng(void*);
extern int strbufapp(void*, const char*, size_t);
extern int strbufbuild(char**, size_t, void*);
extern void strbufclean(void*);

#endif//STRBUF