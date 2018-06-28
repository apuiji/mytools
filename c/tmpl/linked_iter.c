#include"linked_iter.h"

#include<stdlib.h>
#include<string.h>

typedef union{
	void*asarray[2];
	struct{
		void *next, *prev;
	};
}nod_t;

void*linked_iter_next(void*me, int i){
	if(!me)goto E_NOEXIST;
	int j, k;
	if(i<0)j=1,k=-i;
	else j=0,k=i;
	nod_t*wrap = (nod_t*)me-1;
	for(;k>=0;--k){
		wrap = (nod_t*)wrap->asarray[j];
		if(!wrap)goto E_NOEXIST;
	}
	return wrap+1;
	E_NOEXIST:
	return NULL;
}
void*linked_iter_insert(void*me, snake_t value, int how){
	nod_t*ins = (nod_t*)malloc(sizeof(nod_t)+value.count);
	if(!ins)goto E_ALLOC;
	void*data = ins+1;
	if(value.hook)memcpy(data,value.hook,value.count);
	if(me){
		nod_t*cur = (nod_t*)me-1;
		int i, j;
		if(how<0)i=1, j=0;
		else i=0, j=1;
		ins->asarray[i] = cur->asarray[i];
		cur->asarray[i] = ins;
		ins->asarray[j] = cur;
	}else ins->next=ins->prev=NULL;
	return data;
	E_ALLOC:
	return NULL;
}
void*linked_iter_remove(void*me, int how){
	if(!me)return NULL;
	nod_t*wrap = (nod_t*)me-1;
	int i, j;
	if(how<0)i=1, j=0;
	else i=0, j=1;
	nod_t*to_ret = (nod_t*)wrap->asarray[i];
	to_ret->asarray[j] = wrap->asarray[j];
	free(wrap);
	return to_ret+1;
}

