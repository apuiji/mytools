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
XB_t(K,1<<10); XB_t(M,1<<20); XB_t(G,1<<30);
#undef XB_t

extern size_t memnof1(const void*, size_t);
extern void*membitmsk(void*, size_t, ssize_t);

typedef enum{
	AND, OR, NOT, XOR,
}membitlogicop;
extern void*membitlogic(void*,const void*,const void*,size_t,membitlogicop);
#define membitand(dest,src1,src2,size) membitlogic(dest,src1,src2,size,AND)
#define membitor(dest,src1,src2,size) membitlogic(dest,src1,src2,size,OR)
#define membitnot(dest,src,size) membitlogic(dest,src,NULL,size,NOT)
#define membitxor(dest,src1,src2,size) membitlogic(dest,src1,src2,size,XOR)

typedef enum{
	SHL=0x00, SAL=0x01, ROL=0x02,
	SHR=0x10, SAR=0x11, ROR=0x12,
}memshiftop;
extern void*memshift(void*, const void*, size_t, size_t, memshiftop);
#define memshl(dest,src,size,nbit) memshift(dest,src,size,nbit,SHL)
#define memshr(dest,src,size,nbit) memshift(dest,src,size,nbit,SHR)
#define memsal(dest,src,size,nbit) memshift(dest,src,size,nbit,SAL)
#define memsar(dest,src,size,nbit) memshift(dest,src,size,nbit,SAR)
#define memrol(dest,src,size,nbit) memshift(dest,src,size,nbit,ROL)
#define memror(dest,src,size,nbit) memshift(dest,src,size,nbit,ROR)

#endif//MEM
