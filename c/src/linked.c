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
linked_t*linkedrmv(linked_t*me, size_t size, size_t*_nrmv, linked_t**last){
	if(me==NULL||size==0)return NULL;
	linked_t*result = me->next;
	size_t nrmv = 1;
	for(linked_t*rmv=result;1;++nrmv){
		if(rmv==NULL||nrmv>=size){
			if(last!=NULL)*last=rmv;
			me->next = rmv==NULL?NULL:rmv->next;
			break;
		}
		rmv=rmv->next;
	}
	if(_nrmv!=NULL)*_nrmv=nrmv;
	return result;
}
linked_t*linkedreverse(linked_t*me, linked_t*prev, size_t*size){
	size_t i = 0;
	for(linked_t*next=me;next!=NULL;){
		me = next;
		next = me->next;
		me->next = prev;
		prev = me;
		++i;
	}
	if(size!=NULL)*size=i;
	return me;
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

