#ifndef TEMPLATE_STACK
#define TEMPLATE_STACK

#include"linked.h"

typedef linked_t stack_t;

#define stackpush(me,p,size) linkedins(me,p,size)
#define stackpeek(me) linkedget(me,1)
extern linked_t*stackpop(stack_t*);

#endif//TEMPLATE_STACK
