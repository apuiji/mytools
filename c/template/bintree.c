#include"bintree.h"

int btdepth(btnod_t*me){
	if(me==NULL)return 0;
	int depthl=btdepth(me->left), depthr=btdepth(me->right);
	return 1+(depthl>depthr?depthl:depthr);
}
btnod_t*btxmost(btnod_t*me, int x){
	x = x<0?1:x>0?2:0;
	for(btnod_t**asarray=(btnod_t**)me,*next;1;asarray=(btnod_t**)next){
		next = asarray[x];
		if(next==NULL)return(btnod_t*)asarray;
	}
}
int bt4each(btnod_t*tree, bt4each how, int(*hdl)(btnod_t*)){
	if(tree==NULL)return 0;
	int fail = 0;
	switch(how){
	case LNR:
		(fail=bt4each(tree->left,how,hdl))||
		(fail=hdl(tree))||
		(fail=bt4each(tree->right,how,hdl));
		break;
	case LRN:
		(fail=bt4each(tree->left,how,hdl))||
		(fail=bt4each(tree->right,how,hdl))||
		(fail=hdl(tree));
		break;
	case NRL:
		(fail=hdl(tree))||
		(fail=bt4each(tree->right,how,hdl))||
		(fail=bt4each(tree->left,how,hdl));
		break;
	case RNL:
		(fail=bt4each(tree->right,how,hdl))||
		(fail=hdl(tree))||
		(fail=bt4each(tree->left,how,hdl));
		break;
	case RLN:
		(fail=bt4each(tree->right,how,hdl))||
		(fail=bt4each(tree->left,how,hdl))||
		(fail=hdl(tree));
		break;
	default://NLR
		(fail=hdl(tree))||
		(fail=bt4each(tree->left,how,hdl))||
		(fail=bt4each(tree->right,how,hdl));
		break;
	}
	return fail;
}

