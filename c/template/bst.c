#include"bst.h"

#include<errno.h>
#include<string.h>

static int put(bstnod_t**, void*, size_t);
int bstput(bst_t*me, void*item, size_t size){
	if(me->root==NULL)return put(&(me->root), item, size);
	for(bstnod_t*nod=me->root,**next;1;nod=*next){
		int cmp = me->cmp(item, nod->data);
		if(!cmp)return -1;
		next = cmp<0?&(nod->left):&(nod->right);
		if(*next==NULL)return put(next,item,size);
	}
}
static int put(bstnod_t**dest, void*item, size_t size){
	*dest = (nod_t*)malloc(sizeof(nod_t)+size);
	if(errno)return errno;
	**dest = (nod_t)0;
	memcpy((*dest)->data, item, size);
	return 0;
}
int bstget(bstnod_t**dest, bst_t*me, void*key){
	for(nod_t*nod=me->root,*next;nod!=NULL;nod=next){
		int cmp = me->cmp(key, nod->data);
		if(!cmp){*dest=nod;return 0;}
		next = cmp<0?nod->left:nod->right;
	}
	return -1;
}
int bstrmv(bst_t*me, void*key){
	nod_t*rmvnod = NULL;
	int notfound = find(&rmvnod, me, key);
	if(notfound)return notfound;
	nod_t *p=rmvnod->parent, *l=rmvnod->left, *r=rmvnod->right;
	free(rmvnod);
	if(btdepth((btnod_t*)l)<btdepth((btnod_t*)r)){
		r->parent = p;
		btxmost(r,-1)->left = l;
	}else{
		l->parent = p;
		btxmost(l, 1)->right = r;
	}
	return 0;
}

