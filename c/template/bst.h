#ifndef BST
#define BST

#include<stdbool.h>
#include<stddef.h>
#include"bintree.h"

typedef struct{
	btnod_t proto;
	char data[0];
}bstnod_t;
typedef struct{
	int(*cmp)(void*,void*);
	bstnod_t*root;
}bst_t;

extern int bstput(bst_t*, void*, size_t);
extern int bstget(bstnod_t**, bst_t*, void*);
extern int bstrmv(bst_t*, void*);
extern bstnod_t*bstrotate(bstnod_t*, int orient);

#endif//BST
