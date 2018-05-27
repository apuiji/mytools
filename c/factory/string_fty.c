#include"string_fty.h"

#include<stdlib.h>
#include<string.h>

void string_fty_init(string_fty*me){
	me->endian.next = NULL;
	me->endian.prev = (void*)me;
	me->totalleng = 0;
}
int string_fty_app(string_fty*me, const char*app, size_t leng){
	dinked_t*nod = dinkedins(me->endian.prev,NULL,sizeof(size_t)+leng);
	if(!nod)return -1;
	size_t*nodleng = (size_t*)(nod+1);
	*nodleng=leng; memcpy(nodleng+1,app,leng);
	return 0;
}
char*string_fty_join(char*dest, size_t mxleng, string_fty*me, bool with0){
	if(me->totalleng<mxleng)mxleng=me->totalleng;
	if(!dest)if(!(dest=malloc(with0?mxleng+1:mxleng)))goto END;
	char*p=dest; size_t totalleng=0;
	for(dinked_t*nod=(dinked_t*)me->endian.next,*next;nod;nod=next){
		size_t *nodleng=(size_t*)(nod+1), leng=*nodleng;
		if(totalleng+leng>mxleng){
			leng=mxleng-totalleng; next=NULL;
		}else{
			totalleng+=leng; next=(dinked_t*)nod->next;
		}
		memcpy(p,nodleng+1,leng); p+=leng;
	}if(with0)*p='\0';
	END:return dest;
}
void string_fty_clean(string_fty*me){
	for(linked_t*nod=me->endian.next,*next;nod;nod=next){
		next=nod->next; free(nod);
	}string_fty_init(me);
}

