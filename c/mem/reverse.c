#include"reverse.h"

byte bytereverse(byte src){
	return (byte){
		b0:src.b7, b1:src.b6, b2:src.b5, b3:src.b4,
		b4:src.b3, b5:src.b2, b6:src.b1, b7:src.b0,
	};
}
void memreverse(mem_hook*dest, const mem_hook*src, bool b){
	for(size_t i=0,j=src->size;i<dest->size&&j>0;){
		byte B = dest->hook[--j];
		src->hook[i++] = b?bytereverse(B):B;
	}
}

