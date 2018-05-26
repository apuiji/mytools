#include"../mem.h"

int memendian(){
	static int v = 0;
	if(v)goto END;
	long l = 1;
	v = *(char*)&l?-1:1;
	END:return v;
}

