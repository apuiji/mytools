#ifndef MEM
#define MEM

#include<sys/types.h>

typedef char byte_t;
typedef union{
	char bytes[2];
}word_t;
typedef union{
	char bytes[4];
	word_t words[2];
}dword_t;
typedef union{
	char bytes[8];
	word_t words[4];
	dword_t dwords[2];
}qword_t;
#define XB_t(X,NB) typedef union{\
	char bytes[NB];\
	word_t words[NB>>1];\
	dword_t dwords[NB>>2];\
	qword_t qwords[NB>>3];\
}X##B_t
XB_t(K,1<<10); XB_t(M,1<<20); XB_t(G,1<<30); XB_t(T,1<<40);
#undef XB_t

extern size_t bytenof1(byte_t);
extern size_t memnof1(const void*, size_t);
extern void membitmsk(void*, size_t, ssize_t);
extern void membitand(void*, const void*, const void*, size_t);
extern void membitor(void*, const void*, const void*, size_t);
extern void membitnot(void*, const void*, size_t);
extern void membitxor(void*, const void*, const void*, size_t);
extern void memshx(void*, const void*, size_t, ssize_t);
extern void memsax(void*, const void*, size_t, ssize_t);
extern void memrox(void*, const void*, size_t, ssize_t);
extern void memrcx(void*, const void*, size_t, ssize_t);

#endif//MEM
