#include"chrset.h"

#include<stddef.h>

size_t strlenof(
	const chrset_t*me, const char*s, size_t*outnascii
){
	char asciich;	bool isascii;
	size_t len=0, chrsize=0, nascii=0;
	while(1){
		if(isascii=me->isascii(me,s,&asciich,&chrsize))++nascii;
		if(isascii&&asciich=='\0')break;
		++len;
		s += chrsize;
	}
	if(outnascii!=NULL)*outnascii=nascii;
	return len;
}
char*strgetof(
	const chrset_t*me, const char*s, int i, size_t*outchrsize
){
	char asciich;	bool isascii;	size_t chrsize;
	for(;i>=0;--i){
		isascii = me->isascii(me,s,&asciich,&chrsize);
		if(isascii&&asciich=='\0')break;
		s += chrsize;
	}
	if(outchrsize!=NULL)*outchrsize=chrsize;
	return (char*)s;
}

bool isascii4varchrset(
	const chrset_t*me, const char*s, char*outchr, size_t*outchrsize
){
	size_t chrsize = me->chrsize(s);
	if(outchrsize!=NULL)*outchrsize=chrsize;
	if(chrsize>1)return false;
	char chr = *s;
	if(outchr!=NULL)*outchr=chr;
	return true;
}

