#ifndef TMPL_LINKED_ITER_H
#define TMPL_LINKED_ITER_H

#include"snake.h"
#include<sys/types.h>

extern void*linked_iter_next(void*, int);
extern void*linked_iter_insert(void*, snake_t, int);
extern void*linked_iter_remove(void*, int);
#define stack_push(me,value) linked_iter_insert(me,value,0)
#define stack_pop(me) linked_iter_remove(me,-1)

#endif//TMPL_LINKED_ITER_H
