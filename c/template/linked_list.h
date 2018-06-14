#ifndef TEMPLATE_LINKED_LIST
#define TEMPLATE_LINKED_LIST

#include"snake.h"
#include<sys/types.h>

extern void*linked_list_next(void*, int);
extern void*linked_list_insert(void*, snake_t, int);
extern void*linked_list_remove(void*, int);
#define stack_push(me,value) linked_list_insert(me,value,0)
#define stack_pop(me) linked_list_remove(me,-1)

#endif//TEMPLATE_LINKED_LIST
