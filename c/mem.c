#include"mem.h"

int native_endian(){
	static int endian = 0;
	if(!endian){
		long l = 1;
		endian = *(char*)(&l)?-1:1;
	}
	return endian;
}

