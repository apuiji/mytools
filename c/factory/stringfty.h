#ifndef FACTORY_STRING
#define FACTORY_STRING

#include<stdbool.h>
#include<stddef.h>

extern void*stringfty_create();
extern size_t stringfty_leng(void*);
extern int stringfty_app(void*, const char*, size_t);
extern void stringfty_undo(void*);
extern void stringfty_redo(void*);
extern char*stringfty_build(char*, size_t, void*, bool);
extern void stringfty_clean(void*);

#endif//STREAM_STRING
