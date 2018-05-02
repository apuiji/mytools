#ifndef BST
#define BST

#include"bintree.h"
#include<stddef.h>

typedef struct bstnod_t bstnod_t;
struct bstnod_t{
	btnod_t proto;
	char data[0];
};
typedef struct{
	int(*cmp)(void*,void*);
	bstnod_t*root;
}bst_t;

extern int bstput(bst_t*, void*, size_t);
extern int bstget(bstnod_t**, bst_t*, void*);
extern int bstrmv(bst_t*, void*);

#endif//BST
