#include"linked.h"

#include<sys/types.h>

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
linked_t*linkedrmv(linked_t*me, size_t size){
	linked_t *rmv=me->next, *rmv0=rmv;
	for(off_t i=0;rmv!=NULL&&i<size;++i)rmv=rmv->next;
	return rmv0;
}

