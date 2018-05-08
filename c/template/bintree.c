#include"bintree.h"

#include<errno.h>

size_t btdepth(btnod_t*me){
	if(me==NULL)return 0;
	size_t depthl=btdepth(me->left), depthr=btdepth(me->right);
	return 1+(depthl>depthr?depthl:depthr);
}
size_t btcount(btnod_t*me){
	return me!=NULL?1+btcount(me->left)+btcount(me->right):0;
}
btnod_t*btxmost(btnod_t*me, int x){
	x = x<0?1:x>0?2:0;
	for(btnod_t**asarray=(btnod_t**)me,*next;1;asarray=(btnod_t**)next){
		next = asarray[x];
		if(next==NULL)return(btnod_t*)asarray;
	}
}
int bt4each(
	btnod_t*tree, bt4each_t how,
	int(*hdl)(btnod_t*, void*), void*param
){
	if(tree==NULL)return 0;
	int fail = 0;
	btnod_t*children[2];{
		int ilchild = how&0x10?1:0;
		children[ilchild] = tree->left;
		children[(ilchild+1)%2] = tree->right;
	}
	switch(how&0x0f){
	case LNR:
		(fail=bt4each(children[0],how,hdl,param))||
		(fail=hdl(tree,param))||
		(fail=bt4each(children[1],how,hdl,param));
		break;
	case LRN:
		(fail=bt4each(children[0],how,hdl,param))||
		(fail=bt4each(children[1],how,hdl,param))||
		(fail=hdl(tree,param));
		break;
	case NLR:
		(fail=hdl(tree,param))||
		(fail=bt4each(children[0],how,hdl,param))||
		(fail=bt4each(children[1],how,hdl,param));
		break;
	default:
		errno = EINVAL;
		fail = -1;
	}
	return fail;
}

