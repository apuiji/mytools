#include"chrset.h"

#include<stddef.h>

size_t strlenof(const chrset_t*me, const char*s, size_t*outnascii){
	size_t len=0, chrsize=0, nascii=0;
	while(1){
		if(me->isascii(me,s,&chrsize))++nascii;
		if(*s=='\0')break;
		++len;
		s += chrsize;
	}
	if(outnascii!=NULL)*outnascii=nascii;
	return len;
}
char*strgetof(const chrset_t*me, const char*s, int i, size_t*outchrsize){
	size_t chrsize = 1;
	for(;i>=0;--i){
		s += (chrsize=me->chrsize(s));
		if(*s=='\0')break;
	}
	if(outchrsize!=NULL)*outchrsize=chrsize;
	return (char*)s;
}

bool isascii4varchrset(const chrset_t*me, const char*s, size_t*outchrsize){
	size_t chrsize = me->chrsize(s);
	if(outchrsize!=NULL)*outchrsize=chrsize;
	return chrsize==1;
}
extern bool eqascii4varchrset(const chrset_t*me, const char*s, int ch){
	if(!me->isascii(me, s, NULL))return false;
	return *s==ch;
}

