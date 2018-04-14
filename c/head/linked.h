#ifndef LINKED
#define LINKED

#include"sys/types.h"

typedef struct linked_t linked_t;
struct linked_t{
	void*point;
	linked_t*next;
};
extern size_t linkedlen(linked_t*);
extern void linkedins(linked_t*, linked_t*);
extern size_t linkedrmv(linked_t*, size_t, linked_t**);
extern size_t linkedreverse(linked_t*,linked_t*);
extern size_t linked2array(void*, size_t, size_t, linked_t*);

#endif//LINKED
