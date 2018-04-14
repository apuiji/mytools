#ifndef LINKED
#define LINKED

#include<string.h>

typedef struct linked_t linked_t;
struct linked_t{
	void*point;
	linked_t*next;
};
size_t linkedlen(linked_t*);
void linkedins(linked_t*, linked_t*);
linked_t*linkedrmv(linked_t*, size_t);

#endif//LINKED
