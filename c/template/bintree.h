#ifndef BINTREE
#define BINTREE

#include<stddef.h>

typedef struct btnod_t btnod_t;
struct btnod_t{
	btnod_t *parent, *left, *right;
};

extern size_t btdepth(btnod_t*);
extern size_t btcount(btnod_t*);
extern btnod_t*btxmost(btnod_t*, int);
typedef enum{
	NLR, LNR, LRN, NRL, RNL, RLN,
}bt4each_t;
extern int bt4each(btnod_t*, bt4each_t, int(*)(btnod_t*));

#endif//BINTREE
