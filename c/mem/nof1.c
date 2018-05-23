#include"../mem.h"

size_t bytenof1(byte_t B){
	size_t n = 0;
	if(B&1)++n;
	B = B>>>1;
	return n;
}
size_t memnof1(void*p, size_t nbyte){
	size_t n = 0;
	byte_t*B = (byte_t*)p;
	while(--nbyte>=0)n+=bytenof1(B[nbyte]);
	return n;
}

