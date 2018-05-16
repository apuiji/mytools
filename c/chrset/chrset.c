#include"chrset.h"

#include<stddef.h>

size_t chrset_wcslen(
	const chrset_t*me,
	const char*ss, const char*se,
	size_t*outnascii
){
	wchar_t wc;	size_t len=0, nascii=0;
	for(size_t chrsize;1;ss+=chrsize){
		if(*ss=='\0'|| se!=NULL && ss>se)break;
		chrsize = me->c2w(&wc, ss);
		if(wc<0x100)++nascii;
		++len;
	}
	if(outnascii!=NULL)*outnascii=nascii;
	return len;
}
size_t chrset_strlen(
	const chrset_t*me,
	const wchar_t*lss, const wchar_t*lse,
	size_t*outnascii
){
	size_t len=0, nascii=0;
	for(size_t chrsize;1;++lss){
		if(*lss=='\0' || lse!=NULL && lss>lse)break;
		chrsize = me->w2c(NULL, lss);
		if(*lss<0x100)++nascii;
		len += chrsize;
	}
	if(outnascii!=NULL)*outnascii=nascii;
	return len;
}
char*chrset_stridx(const chrset_t*me, const char*s, int i, size_t*outchrsize){
	wchar_t wc;	size_t chrsize;
	for(;i>=0;--i){
		chrsize = me->c2w(&wc, s);
		if(wc=='\0')break;
		s += chrsize;
	}
	if(outchrsize!=NULL)*outchrsize=chrsize;
	return (char*)s;
}

void chrset_cs2ws(chrset_t*me, wchar_t**dest, const char*src, size_t len){
	*dest[len] = '\0';
	for(int i=0;i<len;++i)src+=me->c2w(i+*dest,src);
}
void chrset_ws2cs(chrset_t*cs, char**dest, const wchar_t*src, size_t len){
	*dest[len] = '\0';
	char*p = *dest;
	for(int i=0;i<len;++i){
		size_t chrsize = me->w2c(p,src+i);
		p += chrsize;
	}
}
wchar_t chrset_c2w(const char*c){
	static const size_t wcsize = sizeof(wchar_t);
	wchar_t wc=*c;	char*p=(char*)&wc;
	for(int i=0;i<wcsize;++i)p[i]&=0x7f;
	return wc;
}

