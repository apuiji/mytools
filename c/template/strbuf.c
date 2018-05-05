#include"strbuf.h"

#include<errno.h>
#include<stdlib.h>
#include<string.h>

typedef struct nod_t nod_t;
struct nod_t{
	nod_t*next;
	size_t length;
	char cont[0];
};
typedef struct{
	nod_t*first;
	size_t totalleng;
	nod_t*tail;
}strbuf_t;

void*strbufcreate(){
	strbuf_t*out = (strbuf_t*)malloc(sizeof(strbuf_t));
	if(out!=NULL){
		out->first = NULL;
		out->totalleng = 0;
		out->tail = (nod_t*)out;
	}
	return out;
}
size_t strbufleng(void*me){
	return ((strbuf_t*)me)->totalleng;
}
int strbufapp(void*_me, const char*app, size_t leng){
	size_t size = leng+1;
	nod_t*nod = (nod_t*)malloc(sizeof(nod_t)+size);
	if(nod==NULL)return errno;
	nod->next = NULL;
	nod->length = leng;
	memcpy(nod->cont,app,leng);	nod->cont[leng]='\0';
	strbuf_t*me = (strbuf_t*)_me;
	me->totalleng += leng;
	me->tail = me->tail->next = nod;
	return 0;
}
int strbufbuild(char**dest, size_t mxleng, void*_me){
	strbuf_t*me = (strbuf_t*)_me;
	if(me->totalleng<mxleng||mxleng==0)mxleng=me->totalleng;
	if(*dest==NULL){
		*dest = (char*)malloc(mxleng+1);
		if(*dest==NULL)return errno;
	}
	size_t totalleng = 0;
	for(nod_t*nod=me->first,*next;nod!=NULL;nod=next){
		size_t leng = nod->length;
		if(totalleng+leng>mxleng){
			leng = mxleng-totalleng;
			next = NULL;
		}else{
			totalleng += leng;
			next = nod->next;
		}
		memcpy(dest, nod->cont, leng);
		dest += leng;
	}*dest = '\0';
	return 0;
}
void strbufclean(void*_me){
	strbuf_t*me = (strbuf_t*)_me;
	for(nod_t*nod=me->first,*next;nod!=NULL;nod=next){
		next = nod->next;
		free(nod);
	}
}

