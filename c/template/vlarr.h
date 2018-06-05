#ifndef TEMPLATE_VLARR
#define TEMPLATE_VLARR

#include<sys/types.h>

typedef struct{
	void*hook;
	size_t esize, length, mxleng;
}vlarr_t;

extern void*vlarr_r(vlarr_t*, off_t);
extern int vlarr_c(vlarr_t*, off_t, void*);
extern int vlarr_u(vlarr_t*, off_t, void*);
extern int vlarr_d(vlarr_t*, off_t, size_t);
extern int vlarr_remxleng(vlarr_t*, size_t);

#endif//TEMPLATE_VARRAY
