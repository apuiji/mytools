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
}membitlogic_op;
extern void*membitlogic(void*,const void*,const void*,size_t,membitlogic_op);
#define membitand(dest,src1,src2,size) membitlogic(dest,src1,src2,size,AND)
#define membitor(dest,src1,src2,size) membitlogic(dest,src1,src2,size,OR)
#define membitnot(dest,src,size) membitlogic(dest,src,NULL,size,NOT)
#define membitxor(dest,src1,src2,size) membitlogic(dest,src1,src2,size,XOR)

typedef enum{
	SHL=0x00, SAL=0x01, ROL=0x02,
	SHR=0x10, SAR=0x11, ROR=0x12,
}memshift_op;
extern void*memshift(void*, const void*, size_t, size_t, memshift_op);
#define memshl(dest,src,size,nb) memshift(dest,src,size,nb,SHL)
#define memsal(dest,src,size,nb) memshift(dest,src,size,nb,SAL)
#define memrol(dest,src,size,nb) memshift(dest,src,size,nb,ROL)
#define memshr(dest,src,size,nb) memshift(dest,src,size,nb,SHR)
#define memsar(dest,src,size,nb) memshift(dest,src,size,nb,SAR)
#define memror(dest,src,size,nb) memshift(dest,src,size,nb,ROR)

enum memendian{
	LITTLE=-1, BIG=1,
};
extern enum memendian memendian();
extern void*memendianrvs(void*, const void*, size_t);

#endif//MEM
