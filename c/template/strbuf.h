#ifndef STRBUF
#define STRBUF

#include"linked.h"

typedef struct strbuf_t{
	size_t totallen;
	linked_t head, *tail;
}strbuf_t;

#define strbufinit(_me) {\
	strbuf_t*me = _me;\
	me->totallen = 0;\
	me->tail = &(me->head);\
}
extern int strbufapp(strbuf_t*, const char*, size_t);
extern int strbufbuild(char**, strbuf_t*);
extern void strbuffree(strbuf_t*);

#endif//STRBUF
