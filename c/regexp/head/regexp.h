#ifndef REGEXP
#define REGEXP

#include<sys/types.h>
#include<stddef.h>
#include<regex.h>
#include"chrset.h"
#include"linked.h"

typedef struct regexp_t{
	int flags;
	const char*newline;
	chrsize_fn chrsize;
	linked_t*pats;
}regexp_t;
extern int repcomp(regexp_t*, const char*, int);
extern int repexec(const regexp_t*, const char*, size_t, regmatch_t*, int);
extern size_t reperror(int, const regexp_t*, char*, size_t);
extern void repfree(regexp_t*);

#endif//REGEXP
