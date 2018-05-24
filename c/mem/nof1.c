#include"../mem.h"

size_t bytenof1(unsigned char B){
	size_t n = 0;
	for(;B;B>>=1)if(B&1)++n;
	return n;
}
size_t memnof1(void*p, size_t nbyte){
	size_t n = 0;
	byte_t*B = (byte_t*)p;
	while(--nbyte>=0)n+=bytenof1(B[nbyte]);
	return n;
}

