#include"../mem.h"

void membitand(void*out, const void*o1, const void*o2, size_t size){
	#define TMP(T) for(size_t n##T=size/sizeof(T);n##T;--n##T){\
		*(T*)out = *(T*)o1 & *(T*)o2;\
		out=1+(T*)out; o1=1+(T*)o1; o2=1+(T*)o2;\
	}size=size%sizeof(T)
	TMP(long); TMP(int); TMP(short); TMP(char);
	#undef TMP
}
void membitor(void*out, const void*o1, const void*o2, size_t size){
	#define TMP(T) for(size_t n##T=size/sizeof(T);n##T;--n##T){\
		*(T*)out = *(T*)o1 | *(T*)o2;\
		out=1+(T*)out; o1=1+(T*)o1; o2=1+(T*)o2;\
	}size=size%sizeof(T)
	TMP(long); TMP(int); TMP(short); TMP(char);
	#undef TMP
}
void membitnot(void*out, const void*o, size_t size){
	#define TMP(T) for(size_t n##T=size/sizeof(T);n##T;--n##T){\
		*(T*)out = !*(T*)o\
		out=1+(T*)out; o=1+(T*)o;\
	}size=size%sizeof(T)
	TMP(long); TMP(int); TMP(short); TMP(char);
	#undef TMP
}
void membitxor(void*out, const void*o1, const void*o2, size_t size){
	#define TMP(T) for(size_t n##T=size/sizeof(T);n##T;--n##T){\
		*(T*)out = *(T*)o1 ^ *(T*)o2;\
		out=1+(T*)out; o1=1+(T*)o1; o2=1+(T*)o2;\
	}size=size%sizeof(T)
	TMP(long); TMP(int); TMP(short); TMP(char);
	#undef TMP
}

