#include"varray.h"

#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"mem.h"

#define enindex(me,i) (i<0?i+me->length:i)
#define outlength(me,i) (i<0||i>=me->length)
#define outmxleng(me,i) (i<0||i>=me->mxleng)
#define tryreleng(me,reqleng) ({\
	size_t newleng = enoleng(me,reqleng);\
	newleng>me->mxleng && varrayreleng(me,newleng);\
})
static size_t enoleng(varray_t*, size_t);
int varrayc(varray_t*me, int i, void*pvalue){
	i = enindex(me,i);
	if(i<0){
		if(tryreleng(me,me->length-i))return -1;
		me->length -= i;
		memshift(me->point, me->length, -i*me->esize, 0);
		memcpy(me->point, pvalue, me->esize);
	}else if(i>=me->length){
		if(tryreleng(me,i+1))return -1;
		me->length = i+1;
		memcpy(varrayr(me,i), pvalue, me->esize);
	}else{
		if(tryreleng(me,me->length+1))return -1;
		++me->length;
		memshift(varrayr(me,i), me->length-i, me->esize, 0);
		memcpy(varrayr(me,i), pvalue, me->esize);
	}
	return 0;
}
int varrayu(varray_t*me, int i, void*pvalue){
	i = enindex(me,i);
	if(outlength(me,i))return -1;
	void*upd = varrayr(me,i);
	memcpy(upd, pvalue, me->esize);
	return 0;
}
int varrayd(varray_t*me, int i, size_t length){
	if(length==0)return 0;
	i = enindex(me,i);
	if(outlength(me,i))return -1;
	length = i+length>me->length?me->length-i:length;
	void*del = varrayr(me,i);
	memshift(del, (me->length-=length)-i, -length*me->esize, 0);
	return 0;
}
int varrayreleng(varray_t*me, size_t newleng){
	if(newleng==me->mxleng)return 0;
	void*newpoint = realloc(me->point, newleng);
	if(newpoint==NULL)return -1;
	me->point = newpoint;
	if(newleng<me->mxleng)me->length=newleng;
	me->mxleng = newleng;
	return 0;
}

size_t enoleng(varray_t*me, size_t reqleng){
	size_t mxleng = me->mxleng;
	while(mxleng<reqleng)mxleng=mxleng<<1;
	return mxleng;
}

