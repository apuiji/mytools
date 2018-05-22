#ifndef TEMPLATE_BST
#define TEMPLATE_BST

#include<stdbool.h>
#include<stddef.h>
#include"bintree.h"

typedef struct{
	int(*cmp)(void*,void*);
	btnod_t*root;
}bst_t;

extern int bstput(bst_t*, void*, size_t);
extern btnod_t*bstget(bst_t*, void*);
extern int bstrmv(bst_t*, void*);
extern btnod_t*bstrotate(btnod_t*, int orient);

#endif//TEMPLATE_BST
