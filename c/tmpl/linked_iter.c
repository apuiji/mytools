#include"linked_iter.h"

#include<stdlib.h>
#include<string.h>

typedef struct{
	void *next, *prev;
}node_t;

void*linked_iter_next(void*me, int i){
	int j, k;
	if(i<0)j=1,k=-i;
	else j=0,k=i;
	void**n = (void**)((node_t*)me-1);
	for(;k>=0;--k){
		n = (void**)n[j];
		if(!n)return NULL;
	}
	return n[2];
}
void*linked_iter_insert(void*me, snake_t value, int how){
	node_t*ins = (node_t*)malloc(sizeof(node_t)+value.count);
	if(!ins)return NULL;
	void*data = ins+1;
	if(value.hook)memcpy(data,value.hook,value.count);
	if(me){
		node_t*cur = (node_t*)me-1;
		int i, j;
		if(how<0)i=1, j=0;
		else i=0, j=1;
		((void**)ins)[i] = ((void**)cur)[i];
		((void**)cur)[i] = ins;
		((void**)ins)[j] = cur;
	}else ins->next=ins->prev=NULL;
	return data;
}
void*linked_iter_remove(void*me, int how){
	if(!me)return NULL;
	node_t*cur = (node_t*)me-1;
	int i, j;
	if(how<0)i=1, j=0;
	else i=0, j=1;
	void*to_ret = ((void**)cur)[i];
	((void**)to_ret)[j] = ((void**)cur)[j];
	free(cur);
	return to_ret;
}

