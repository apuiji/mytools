#include"varray.h"

#include<errno.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"mem.h"

#define outlength(me,i) (i<0||i>=me->length)
#define outmxleng(me,i) (i<0||i>=me->mxleng)
static size_t enoleng(varray_t*, size_t);
static int tryreleng(varray_t*, size_t);

int varrayc(varray_t*me, int i, void*pvalue){
	if(i<0){
		int err = tryreleng(me, me->length-i);
		if(err)return err;
		me->length -= i;
		memshift(me->point, me->length, -i*me->esize, 0);
		memcpy(me->point, pvalue, me->esize);
	}else if(i>=me->length){
		int err = tryreleng(me, i+1);
		if(err)return err;
		void*dest = varrayr(me,i);
		if(errno)return errno;
		me->length = i+1;
		memcpy(dest, pvalue, me->esize);
	}else{
		int err = tryreleng(me, me->length+1);
		if(err)return err;
		void*dest = varrayr(me,i);
		if(errno)return errno;
		++me->length;
		memshift(dest, me->length-i, me->esize, 0);
		memcpy(dest, pvalue, me->esize);
	}
	return 0;
}
void*varrayr(varray_t*me, int i){
	void*out = NULL;
	if(outlength(me,i))errno=ERANGE;
	else out=me->esize*i+(char*)me->point;
	return out;
}
int varrayu(varray_t*me, int i, void*pvalue){
	void*upd;
	if(varrayr(&upd,me,i))return errno;
	memcpy(upd, pvalue, me->esize);
	return 0;
}
int varrayd(varray_t*me, int i, ssize_t length){
	if(length==0)return 0;
	void*del;
	if(varrayr(&del,me,i)return errno;
	length = length<0||i+length>me->length?me->length-i:length;
	memshift(del, (me->length-=length)-i, -length*me->esize, 0);
	return 0;
}
int varrayreleng(varray_t*me, size_t newleng){
	if(newleng==me->mxleng)return 0;
	void*newpoint = realloc(me->point, newleng);
	if(newpoint==NULL)return errno;
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
int tryreleng(varray_t*me, size_t reqleng){
	size_t newleng = enoleng(me,reqleng);
	return newleng>me->mxleng?varrayreleng(me,newleng):0;
}

