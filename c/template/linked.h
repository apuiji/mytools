#ifndef TEMPLATE_LINKED
#define TEMPLATE_LINKED

#include<stddef.h>

typedef struct linked_t linked_t;
typedef struct dinked_t dinked_t;
struct linked_t{
	linked_t *next;
};
struct dinked_t{
	linked_t *next, *prev;
};

extern linked_t*linkedins(linked_t*, void*, size_t);
extern dinked_t*dinkedins(linked_t*, void*, size_t);
extern linked_t*linkedget(linked_t*, int);
extern dinked_t*dinkedget(dinked_t*, int);

#endif//TEMPLATE_LINKED
