#ifndef FACTORY_STRING
#define FACTORY_STRING

#include<stdbool.h>
#include<stddef.h>
#include"../template/linked.h"
#include"../template/stack.h"

typedef struct{
	dinked_t endian;
	size_t totalleng;
}string_fty;

extern void string_fty_init(string_fty*);
extern int string_fty_app(string_fty*, const char*, size_t);
extern char*string_fty_join(char*, size_t, string_fty*, bool);
extern void string_fty_clean(string_fty*);

#endif//FACTORY_STRING
