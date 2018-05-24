#include"../mem.h"

size_t bytenof1(unsigned char B){
	size_t nof1 = 0;
	for(;B;B>>=1)if(B&1)++nof1;
	return nof1;
}
size_t memnof1(void*p, size_t nbyte){
	size_t nof1 = 0;
	for(char*B=p;--nbyte>=0)nof1+=bytenof1(B[nbyte]);
	return nof1;
}

