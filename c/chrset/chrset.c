#include"chrset.h"

#include<stddef.h>

size_t strlenof(
	const chrset_t*me, const char*s, size_t*outnascii
){
	size_t len=0, chrsize=0, nascii=0;
	while(1){
		if(me->isascii(me,s,NULL,&chrsize,NULL))++nascii;
		if(*s=='\0')break;
		++len;
		s += chrsize;
	}
	if(outnascii!=NULL)*outnascii=nascii;
	return len;
}
char*strgetof(
	const chrset_t*me, const char*s, int i, size_t*outchrsize
){
	size_t chrsize = 1;
	for(;i>=0;--i){
		s += (chrsize=me->chrsize(s));
		if(*s=='\0')break;
	}
	if(outchrsize!=NULL)*outchrsize=chrsize;
	return (char*)s;
}

bool isascii4varchrset(
	const chrset_t*me, const char*s,
	char*outchr, size_t*outchrsize,
	const char*rng
){
	size_t chrsize = me->chrsize(s);
	if(outchrsize!=NULL)*outchrsize=chrsize;
	if(chrsize>1)return false;
	char chr = *s;
	bool result = false;
	if(rng==NULL)result=true;
	else while(1){
		if(chr==*rng){
			result = true;
			break;
		}
		if(chr=='\0')break;
	}
	if(result&&outchr!=NULL)*outchr=chr;
	return result;
}

