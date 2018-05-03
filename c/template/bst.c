#include"bst.h"

#include<errno.h>
#include<stdlib.h>
#include<string.h>

static int put(bstnod_t**, void*, size_t);
int bstput(bst_t*me, void*item, size_t size){
	if(me->root==NULL)return put(&(me->root), item, size);
	for(bstnod_t*nod=me->root,**next;1;nod=*next){
		int cmp = me->cmp(item, nod->data);
		if(!cmp)return -1;
		next = (bstnod_t**)(cmp<0?&(nod->proto.left):&(nod->proto.right));
		if(*next==NULL)return put(next,item,size);
	}
}
static int put(bstnod_t**dest, void*item, size_t size){
	*dest = (bstnod_t*)malloc(sizeof(bstnod_t)+size);
	if(errno)return errno;
	memset(*dest, 0, sizeof(bstnod_t));
	memcpy((*dest)->data, item, size);
	return 0;
}
int bstget(bstnod_t**dest, bst_t*me, void*key){
	for(bstnod_t*nod=me->root,*next;nod!=NULL;nod=next){
		int cmp = me->cmp(key, nod->data);
		if(!cmp){*dest=nod;return 0;}
		next = (bstnod_t*)(cmp<0?nod->proto.left:nod->proto.right);
	}
	return -1;
}
int bstrmv(bst_t*me, void*key){
	bstnod_t*rmvnod = NULL;
	int notfound = bstget(&rmvnod, me, key);
	if(notfound)return notfound;
	btnod_t
		*p = rmvnod->proto.parent,
		*l = rmvnod->proto.left,
		*r = rmvnod->proto.right,
		*n;
	free(rmvnod);
	if(btdepth(l)<btdepth(r)){
		r->parent = p;
		btxmost(n=r,-1)->left = l;
	}else{
		l->parent = p;
		btxmost(n=l, 1)->right = r;
	}
	if(p==NULL)me->root=(bstnod_t*)n;
	return 0;
}
bstnod_t*bstrotate(bstnod_t*tree, int orient){
	btnod_t*tmp;
	do{
		if(tree==NULL)break;
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

