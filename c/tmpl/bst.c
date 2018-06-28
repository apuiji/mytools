#include"bst.h"

#include<errno.h>
#include<stdlib.h>
#include<string.h>

static int put(btnod_t**, void*, size_t);
int bstput(bst_t*me, void*item, size_t size){
	if(me->root==NULL)return put(&(me->root), item, size);
	for(btnod_t*nod=me->root,**next;1;nod=*next){
		int cmp = me->cmp(item, nod+1);
		if(!cmp){errno=EALREADY;return -1;}
		next = cmp<0?&(nod->left):&(nod->right);
		if(*next!=NULL)continue;
		int fail = put(next,item,size);
		if(!fail)(*next)->parent=nod;
		return fail;
	}
}
static int put(btnod_t**dest, void*item, size_t size){
	*dest = (btnod_t*)malloc(sizeof(btnod_t)+size);
	if(*dest==NULL)goto E_ALLOC;
	memset(*dest, 0, sizeof(btnod_t));
	memcpy(1+*dest, item, size);
	return 0;
	E_ALLOC:
	return -1;
}
btnod_t*bstget(bst_t*me, void*key){
	for(btnod_t*nod=me->root,*next;nod!=NULL;nod=next){
		int cmp = me->cmp(key, nod+1);
		if(!cmp)return nod;
		next = cmp<0?nod->left:nod->right;
	}
	return NULL;
}
int bstrmv(bst_t*me, void*key){
	btnod_t*rmvnod = bstget(me, key);
	if(rmvnod==NULL)goto E_NOEXIST;
	btnod_t
		*p=rmvnod->parent, *l=rmvnod->left, *r=rmvnod->right, *n;
	free(rmvnod);
	if(btdepth(l)<btdepth(r)){
		r->parent = p;
		btxmost(n=r,-1)->left = l;
	}else{
		l->parent = p;
		btxmost(n=l, 1)->right = r;
	}
	if(p==NULL)me->root=n;
	return 0;
	E_NOEXIST:
	return -1;
}
btnod_t*bstrotate(btnod_t*tree, int orient){
	do{
		if(tree==NULL)break;
		btnod_t*tmp;
		if(orient<0){
			if(tree->left==NULL)break;
			tmp = tree->left->right;
			tree->left->right = tree;
			tree->left = tmp;
			tree = tree->left;
		}else if(orient>0){
			if(tree->right==NULL)break;
			tmp = tree->right->left;
			tree->right->left = tree;
			tree->right = tmp;
			tree = tree->right;
		}
	}while(0);
	return tree;
}

