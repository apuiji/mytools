#include"vlarr.h"

#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include"../mem.h"

#define outlength(me,i) (i<0||i>=me->length)
#define outmxleng(me,i) (i<0||i>=me->mxleng)
static int tryreleng(vlarr_t*, size_t);

void*vlarr_r(vlarr_t*me, off_t i){
	return !outlength(me,i)?me->hook+me->esize*i:NULL;
}
int vlarr_c(vlarr_t*me, off_t i, void*value){
	if(i<0){
		if(tryreleng(me,me->length-i))goto ERR;
		me->length -= i;
		memshr(me->hook, me->hook, me->length, (i*me->esize)<<3);
		memcpy(me->hook, value, me->esize);
	}else if(i>=me->length){
		if(tryreleng(me, i+1))goto ERR;
		me->length = i+1;
		memcpy(vlarr_r(me,i), value, me->esize);
	}else{
		if(tryreleng(me, me->length+1))goto ERR;
		++me->length;
		void*dest = vlarr_r(me,i);
		memshr(dest, dest, me->length-i, me->esize<<3);
		memcpy(dest, value, me->esize);
	}
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
	if(i+leng>me->length)leng=rem;
	memshl(del, del, rem*me->esize, (leng*me->esize)<<3);
	me->length -= leng;
	END:return 0;
	ERR:return -1;
}
int vlarr_releng(vlarr_t*me, size_t newleng){
	if(newleng==me->mxleng)goto END;
	void*newhook = realloc(me->hook, newleng);
	if(newhook==NULL)goto ERR;
	me->hook = newhook;
	if(newleng<me->mxleng)me->length=newleng;
	me->mxleng = newleng;
	END:return 0;
	ERR:return -1;
}

int tryreleng(vlarr_t*me, size_t reqleng){
	if(reqleng<me->mxleng)goto END;
	size_t newleng = 1;
	while(newleng<reqleng)if(newleng<<=1);else{
		errno=ERANGE; goto ERR;
	}
	return vlarr_releng(me,newleng);
	END:return 0;
	ERR:return -1;
}

