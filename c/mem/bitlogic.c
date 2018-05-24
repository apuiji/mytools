#include"../mem.h"

void membitlogic(
	void*dest, const void*src1, const void*src2, size_t size, int op
){
	#define TMP(T) for(size_t n##T=size/sizeof(T);n##T;--n##T){\
		switch(op){\
		case 0:*(T*)dest=*(T*)src1&*(T*)src2;break;\
		case 1:*(T*)dest=*(T*)src1|*(T*)src2;break;\
		case 2:*(T*)dest=~*(T*)src1;break;\
		case 3:*(T*)dest=*(T*)src1^*(T*)src2;break;\
		}\
		dest=1+(T*)dest; src1=1+(T*)src1; src2=1+(T*)src2;\
	}size=size%sizeof(T)
	TMP(long); TMP(int); TMP(short); TMP(char);
	#undef TMP
}

