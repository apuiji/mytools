#ifndef LINKED
#define LINKED

#include"sys/types.h"

typedef struct linked_t linked_t;
struct linked_t{
	void*point;
	linked_t*next;
};
size_t linkedlen(linked_t*);
void linkedins(linked_t*, linked_t*);
size_t linkedrmv(linked_t*, size_t, linked_t**);
size_t linkedreverse(linked_t*,linked_t*);
size_t linked2array(void*, size_t, size_t, linked_t*);

#endif//LINKED
