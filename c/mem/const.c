#include"const.h"

size_t bitsofchar(){
	static size_t size = 0;
	if(!size){
		char c = 0x1;
		for(;c!=0;c=c<<1)++size;
	}
	return size;
}

