#ifndef TEMPLATE_BINTREE
#define TEMPLATE_BINTREE

#include<stddef.h>

typedef struct btnod_t btnod_t;
struct btnod_t{
	btnod_t *parent, *left, *right;
};

extern size_t btdepth(btnod_t*);
extern size_t btcount(btnod_t*);
extern btnod_t*btxmost(btnod_t*, int);
typedef enum{
	NLR=0x01, LNR=0x02, LRN=0x03,
	NRL=0x11, RNL=0x12, RLN=0x13,
}bt4each_t;
extern int bt4each(btnod_t*, bt4each_t, int(*)(btnod_t*,void*), void*);

#endif//TEMPLATE_BINTREE
