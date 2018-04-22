#include"chrset.h"

#include<stddef.h>

char*strget(const char*s, chrsize_fn fn, int i, size_t*outsize){
	size_t size = 1;
	for(;i>=0;--i){
		s += (size=fn(s));
		if(*s=='\0')break;
	}
	if(outsize!=NULL)*outsize=size;
	return (char*)s;
}
size_t strlenof(const char*s, chrsize_fn fn, size_t*outsincount){
	size_t len=0, chrsize=0, sincount=0;
	for(char ch=*s;1;ch=*s){
		chrsize = fn(s);
		if(chrsize==1)++sincount;
		if(ch=='\0')break;
		++len;
		s += chrsize;
	}
	if(outsincount!=NULL)*outsincount=sincount;
	return len;
}

static bool isascii4nofix(const char*){
	
}
chrset_t chrset_ascii = {};
size_t chrsize_ascii(const char*s){return 1;}
size_t chrsize_gbk(const char*s){return *s>0x80?2:1;}
size_t chrsize_utf8(const char*s){
	unsigned char ch = *s;
	if(ch>0xfc)return 6;
	if(ch>0xf8)return 5;
	if(ch>0xf0)return 4;
	if(ch>0xe0)return 3;
	if(ch>0xc0)return 2;
	return 1;
}

