#include"vlarr.h"

#include<errno.h>
#include<stdlib.h>
#include<string.h>

#define outlength(me,i) (i<0||i>=me->length)
#define outmxleng(me,i) (i<0||i>=me->mxleng)
static int tryremxleng(vlarr_t*, size_t);

void*vlarr_r(vlarr_t*me, off_t i){
	return !outlength(me,i)?me->hook+me->esize*i:NULL;
}
int vlarr_c(vlarr_t*me, off_t i, void*value){
	void*dest;
	if(i<0){
		if(tryremxleng(me,me->length-i))goto ERR;
		memmove(me->hook-i, me->hook, me->length);
		me->length -= i;
		dest = me->hook;
	}else if(i>=me->length){
		if(tryremxleng(me, i+1))goto ERR;
		me->length = i+1;
		dest = vlarr_r(me, i);
	}else{
		if(tryremxleng(me, me->length+1))goto ERR;
		dest = vlarr_r(me, i);
		memmove(dest+1, dest, me->length-i);
		++me->length;
	}
	memcpy(dest, value, me->esize);
	return 0;
	ERR:return -1;
}
int vlarr_u(vlarr_t*me, off_t i, void*value){
	void*upd = vlarr_r(me,i);
	if(upd==NULL)return -1;
	memcpy(upd, value, me->esize);
	return 0;
}
int vlarr_d(vlarr_t*me, off_t i, size_t leng){
	if(leng==0)goto END;
	void*del = vlarr_r(me,i);
	if(del==NULL)goto ERR;
	size_t rem = me->length-i;
	if(leng<rem)memcpy(del,del+leng*me->esize,(rem-leng)*me->esize);
	me->length -= leng;
	END:return 0;
	ERR:return -1;
}
int vlarr_remxleng(vlarr_t*me, size_t newleng){
	if(newleng==me->mxleng)goto END;
	void*newhook = realloc(me->hook, newleng);
	if(newhook==NULL)goto ERR;
	me->hook = newhook;
	if(newleng<me->mxleng)me->length=newleng;
	me->mxleng = newleng;
	END:return 0;
	ERR:return -1;
}

int tryremxleng(vlarr_t*me, size_t reqleng){
	if(reqleng<me->mxleng)goto END;
	size_t newleng = 1;
	while(newleng<reqleng)if(newleng<<=1);else{
		errno=ERANGE; goto ERR;
	}
	return vlarr_remxleng(me,newleng);
	END:return 0;
	ERR:return -1;
}

