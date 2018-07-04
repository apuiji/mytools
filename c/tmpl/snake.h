#ifndef TMPL_SNAKE_H
#define TMPL_SNAKE_H

#include<sys/types.h>

typedef struct{
	void*hook;
	size_t count;
}snake_t;

#define snake_string(string) ((snake_t){\
	hook:string, count:sizeof(string),\
})

#endif//TMPL_SNAKE_H
