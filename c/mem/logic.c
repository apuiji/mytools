#include"../mem.h"

#include<stdlib.h>

void*membitlogic(
	void*dest, const void*src1, const void*src2, size_t size,
	membitlogic_op op
){
	if(!dest)if(!(dest=malloc(size)))goto END;
	#define TMP(T) for(size_t n##T=size/sizeof(T);n##T;--n##T){\
		switch(op){\
		case AND:*(T*)dest=*(T*)src1&*(T*)src2;break;\
		case OR:*(T*)dest=*(T*)src1|*(T*)src2;break;\
		case NOT:*(T*)dest=~*(T*)src1;break;\
		case XOR:*(T*)dest=*(T*)src1^*(T*)src2;break;\
		}\
		dest=1+(T*)dest; src1=1+(T*)src1; src2=1+(T*)src2;\
	}size=size%sizeof(T)
	TMP(long); TMP(int); TMP(short); TMP(char);
	#undef TMP
	END:return dest;
}

