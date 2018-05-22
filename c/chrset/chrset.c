#include"chrset.h"

size_t chrset_wcslen(
	const chrset_t*me,
	const char*ss, const char*se,
	size_t*outnascii
){
	wchar_t wc;	size_t leng=0, nascii=0;
	for(size_t chrsize;!(
		*ss=='\0' || se!=NULL&&ss>=se
	);ss+=chrsize){
		chrsize = me->c2w(&wc, ss);
		if(wc<0x100)++nascii;
		++leng;
	}
	if(outnascii!=NULL)*outnascii=nascii;
	return leng;
}
size_t chrset_strlen(
	const chrset_t*me,
	const wchar_t*lss, const wchar_t*lse,
	size_t*outnascii
){
	size_t leng=0, nascii=0;
	for(size_t chrsize;!(
		*lss=='\0' || lse!=NULL&&lss>=lse
	);++lss){
		chrsize = me->wc2c(NULL, lss);
		if(*lss<0x100)++nascii;
		leng += chrsize;
	}
	if(outnascii!=NULL)*outnascii=nascii;
	return len;
}
char*chrset_stridx(const chrset_t*me, const char*s, int i, size_t*outchrsize){
	size_t chrsize;
	for(wchar_t wc;i>=0;--i){
		chrsize = me->c2wc(&wc,s);
		if(wc=='\0')break;
		s += chrsize;
	}
	if(outchrsize!=NULL)*outchrsize=chrsize;
	return (char*)s;
}

void chrset_s2ls(const chrset_t*me, wchar_t**dest, const char*src, size_t leng){
	for(int i=0;i<leng;++i)src+=me->c2wc(i+*dest,src);
	*dest[leng] = '\0';
}
void chrset_ls2s(const chrset_t*me, char**dest, const wchar_t*src, size_t leng){
	char*p = *dest;
	for(int i=0;i<leng;++i){
		size_t chrsize = me->wc2c(p,src+i);
		p += chrsize;
	}*p = '\0';
}

