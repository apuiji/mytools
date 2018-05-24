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

extern size_t bytenof1(unsigned char);
extern size_t memnof1(const void*, size_t);
extern void membitmsk(void*, size_t, ssize_t);
#define membitand(dest,src1,src2,size) membitlogic(dest,src1,src2,size,0)
#define membitor(dest,src1,src2,size) membitlogic(dest,src1,src2,size,1)
#define membitnot(dest,src,size) membitlogic(dest,src,NULL,size,2)
#define membitxor(dest,src1,src2,size) membitlogic(dest,src1,src2,size,3)
extern void membitlogic(void*, const void*, const void*, size_t, int);
#define memshl(dest,src,size,nbit) memshift(dest,src,size,nbit,0x00)
#define memshr(dest,src,size,nbit) memshift(dest,src,size,nbit,0x10)
#define memsal(dest,src,size,nbit) memshift(dest,src,size,nbit,0x01)
#define memsar(dest,src,size,nbit) memshift(dest,src,size,nbit,0x11)
#define memrol(dest,src,size,nbit) memshift(dest,src,size,nbit,0x02)
#define memror(dest,src,size,nbit) memshift(dest,src,size,nbit,0x12)
#define memrcl(dest,src,size,nbit) memshift(dest,src,size,nbit,0x03)
#define memrcr(dest,src,size,nbit) memshift(dest,src,size,nbit,0x13)
extern void memshift(void*, const void*, size_t, size_t, int);

#endif//MEM
