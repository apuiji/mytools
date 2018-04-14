#include"linked.h"

#include<sys/types.h>
#include<string.h>

size_t linkedlen(linked_t*me){
	size_t len = 0;
	for(;me!=NULL;me=me->next)++len;
	return len;
}
void linkedins(linked_t*me, linked_t*him){
	if(me==NULL||him==NULL)return;
	linked_t*next = me->next;
	for(me=me->next=him;me->next!=NULL;me=me->next);
	me->next = next;
}
size_t linkedrmv(linked_t*me, size_t size, linked_t**pops){
	if(me==NULL||size==0)return 0;
	linked_t*rmv = me->next;
	if(pops!=NULL)*pops = rmv;
	size_t npop = 1;
	for(;rmv!=NULL&&npop<=size;++npop)rmv=rmv->next;
	me->next = rmv;
	return npop;
}
size_t linkedreverse(linked_t*me, linked_t*prev){
	size_t i = 0;
	for(linked_t*next=NULL;me!=NULL;me=next){
		if(me==NULL)break;
		next = me->next;
		me->next = prev;
		prev = me;
		++i;
	}
	return i;
}
size_t linked2array(void*dest, size_t esize, size_t length, linked_t*src){
	size_t i = 0;
	for(;i<length;++i){
		if(src==NULL)break;
		src = src->next;
		memcpy(esize*i+(char*)dest, src->point, esize);
	}
	return i;
}

