#include<errno.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"linked.h"

static void*ins(linked_t*, size_t, const void*, size_t);
linked_t*linkedins(linked_t*me, const void*item, size_t size){
	return (linked_t*)ins(me, sizeof(linked_t), item, size);
}
dinked_t*dinkedins(linked_t*me, const void*item, size_t size){
	dinked_t*nod = (dinked_t*)ins(me, sizeof(dinked_t), item, size);
	if(nod!=NULL)nod->prev=me;
	return nod;
}
void*ins(linked_t*me, size_t nodsize, const void*item, size_t size){
	linked_t*nod = (linked_t*)malloc(nodsize+size);
	if(nod!=NULL){
		nod->next = me->next;
		me->next = nod;
		if(item!=NULL)memcpy(nodsize+(char*)nod, item, size);
	}
	return nod;
}
static void*get(void*, int d, int i);
linked_t*linkedget(linked_t*me, int i){
	return get(me, 0, i);
}
dinked_t*dinkedget(dinked_t*me, int i){
	return get(me, 1, i);
}
void*get(void*me, int d, int i){
	if(i==0)return me;
	if(i<0)if(d)i=-i;
	else{
		errno=EINVAL;return NULL;
	}
	linked_t**asarray = (linked_t**)me;
	for(;asarray!=NULL;asarray=(linked_t**)asarray[d])
		if(i>0)--i;
		else break;
	return asarray;
}

