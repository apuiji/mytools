#include"../mem.h"

size_t memnof1(const void*p, size_t size){
	size_t nof1 = 0;
	while(size)for(char c=*(char*)(p+--size),i=0;i<8;++i){
		if(c&1)++nof1;
		c >>= 1;
	}
	return nof1;
}

