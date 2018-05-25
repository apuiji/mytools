#include"varray.h"

#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include"../mem.h"

#define outlength(me,i) (i<0||i>=me->length)
#define outmxleng(me,i) (i<0||i>=me->mxleng)
static size_t enoleng(varray_t*, size_t);
static int tryreleng(varray_t*, size_t);

int varrayc(varray_t*me, int i, void*pvalue){
	if(i<0){
		if(tryreleng(me,me->length-i))goto ERROR;
		me->length -= i;
		memshl(me->hook, me->hook, me->length, (i*me->esize)<<3);
		memcpy(me->hook, pvalue, me->esize);
	}else if(i>=me->length){
		if(tryreleng(me, i+1))goto ERROR;
		void*dest = varrayr(me,i);
		me->length = i+1;
		memcpy(dest, pvalue, me->esize);
	}else{
		if(tryreleng(me, me->length+1))goto ERROR;
		void*dest = varrayr(me,i);
		++me->length;
		memshr(dest, dest, me->length-i, me->esize<<3);
		memcpy(dest, pvalue, me->esize);
	}
	return 0;
	ERROR:return -1;
}
void*varrayr(varray_t*me, int i){
	void*out = NULL;
	if(outlength(me,i))errno=ERANGE;
	else out=me->esize*i+(char*)me->hook;
	return out;
}
int varrayu(varray_t*me, int i, void*pvalue){
	void*upd = varrayr(me,i);
	if(upd==NULL)return -1;
	memcpy(upd, pvalue, me->esize);
	return 0;
}
int varrayd(varray_t*me, int i, ssize_t leng){
	if(leng==0)goto OVER;
	void*del = varrayr(me,i);
	if(del==NULL)goto ERROR;
	if(leng<0||i+leng>me->length)leng=me->length-i;
	memshl(del, del, (me->length-i)*me->esize, (leng*me->esize)<<3);
	me->length -= leng;
	OVER:return 0;
	ERROR:return -1;
}
int varrayreleng(varray_t*me, size_t newleng){
	if(newleng==me->mxleng)goto OVER;
	void*newhook = realloc(me->hook, newleng);
	if(newhook==NULL)goto ERROR;
	me->hook = newhook;
	if(newleng<me->mxleng)me->length=newleng;
	me->mxleng = newleng;
	OVER:return 0;
	ERROR:return -1;
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

