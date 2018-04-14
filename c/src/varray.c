#include"varray.h"

#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"mem.h"

#define enindex(me,i) (i<0?i+me->length:i)
#define outlength(me,i) (i<0||i>=me->length)
#define outsize(me,i) (i<0||i>=me->size)
#define tryresize(me,allocsize) ({\
	size_t newsize = enosize(me,allocsize);\
	newsize>me->size && varrayresize(me,newsize);\
})
static size_t enosize(varray_t*, size_t);
int varrayc(varray_t*me, off_t i, void*pvalue){
	i = enindex(me,i);
	if(i<0){
		if(tryresize(me,me->length-i))return -1;
		me->length -= i;
		memshift(me->point, me->length, -i*me->esize);
		memcpy(me->point, pvalue, me->esize);
	}else if(i>=me->length){
		if(tryresize(me,i+1))return -1;
		me->length = i+1;
		memcpy(varrayr(me,i), pvalue, me->esize);
	}else{
		if(tryresize(me,me->length+1))return -1;
		++me->length;
		memshift(varrayr(me,i), me->length-i, me->esize);
		memcpy(varrayr(me,i), pvalue, me->esize);
	}
	return 0;
}
int varrayu(varray_t*me, off_t i, void*pvalue){
	i = enindex(me,i);
	if(outlength(me,i))return -1;
	void*upd = varrayr(me,i);
	memcpy(upd, pvalue, me->esize);
	return 0;
}
int varrayd(varray_t*me, off_t i, size_t length){
	if(length==0)return 0;
	i = enindex(me,i);
	if(outlength(me,i))return -1;
	length = i+length>me->length?me->length-i:length;
	void*del = varrayr(me,i);
	memshift(del, (me->length-=length)-i, -length*me->esize);
	return 0;
}
int varrayresize(varray_t*me, size_t newsize){
	if(newsize==me->size)return 0;
	void*newpoint = realloc(me->point, newsize);
	if(newpoint==NULL)return -1;
	me->point = newpoint;
	if(newsize<me->size)me->length=newsize;
	me->size = newsize;
	return 0;
}

size_t enosize(varray_t*me, size_t allocsize){
	size_t size = me->size;
	while(size<allocsize)size=size<<1;
	return size;
}

