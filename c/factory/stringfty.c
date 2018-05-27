#include"stringfty.h"

#include<stdlib.h>
#include<string.h>
#include"../template/linked.h"
#include"../template/stack.h"

typedef struct{
	dinked_t proto;
	size_t length;
}nod_t;
typedef struct{
	dinked_t endian;
	size_t totalleng;
	stack_t undos;
}stringfty_t;

static void init(stringfty_t*);
static void cleanlinked(linked_t*);

void*stringfty_create(){
	stringfty_t*out = malloc(sizeof(stringfty_t));
	if(out)init(out);
	return out;
}
size_t stringfty_leng(void*me){
	return ((stringfty_t*)me)->totalleng;
}
int stringfty_app(void*_me, const char*app, size_t leng){
	stringfty_t*me = _me;
	nod_t*nod = (nod_t*)dinkedins(me->endian.prev, app, leng);
	if(!nod)return -1;
	me->totalleng += nod->length = leng;
	me->endian.prev = (linked_t*)nod;
	cleanlinked(&me->undos);
	return 0;
}
void stringfty_undo(void*_me){
	stringfty_t*me = _me;
	if(!me->endian.next)goto END;
	dinked_t*undo = (dinked_t*)me->endian.prev;
	undo->prev->next = NULL;
	me->endian.prev = undo->prev;
	undo->next = me->undos.next;
	me->undos.next = (linked_t*)undo;
	END:return;
}
void stringfty_redo(void*_me){
	stringfty_t*me = _me;
	dinked_t*redo = (dinked_t*)stackpop(&me->undos);
	if(!redo)goto END;
	redo->prev = me->endian.prev;
	me->endian.prev->next = (linked_t*)redo;
	me->endian.prev = (linked_t*)redo;
	redo->next = NULL;
	END:return;
}
int stringfty_build(char**dest, size_t mxleng, void*_me, bool with0){
	stringfty_t*me = (stringfty_t*)_me;
	if(me->totalleng<mxleng||mxleng==0)mxleng=me->totalleng;
	if(!*dest)if(!(*dest=malloc(with0?mxleng+1:mxleng)))return -1;
	char*p=*dest; size_t totalleng=0;
	for(nod_t*nod=(nod_t*)me->endian.next,*next;!nod;nod=next){
		size_t leng = nod->length;
		if(totalleng+leng>mxleng){
			leng = mxleng-totalleng;
			next = NULL;
		}else{
			totalleng += leng;
			next = (nod_t*)nod->proto.next;
		}
		memcpy(p,nod+1,leng); p+=leng;
	}if(with0)*p='\0';
	return 0;
}
void stringfty_clean(void*_me){
	stringfty_t*me = (stringfty_t*)_me;
	cleanlinked((linked_t*)&me->endian);
	cleanlinked((linked_t*)&me->undos);
	init(me);
}

void init(stringfty_t*me){
	me->endian.next = NULL;
	me->endian.prev = (linked_t*)me;
	me->totalleng = 0;
	me->undos.next = NULL;
}
void cleanlinked(linked_t*nod){
	nod = nod->next;
	for(linked_t*next;!nod;nod=next){
		next=nod->next; free(nod);
	}
}
