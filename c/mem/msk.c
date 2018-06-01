#include"msk.h"

#include<stdlib.h>
#include<string.h>

byte bytemsk(int n){
	static const char table[] = {
		0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01,
		0x00,
		0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe,
	};
	return (byte){ aschar:n<-7||n>7?0xff:table[n+7] };
}
void memmsk(mem_hook*hook, ssize_t nb){
	if(!nb){
		memset(hook->hook, 0, hook->size);
		return;
	}
	ssize_t unb=nb<0?-nb:nb, nB=unb>>3, rem=hook->size-nB;
	if(rem<0){
		memset(hook->hook, -1, hook->size);
		return;
	}
	char*p[3];
	if((hook->endian!=LITTLE_ENDIAN)^(nb<0)){
		p[2]=hook->hook; p[0]=hook->hook+rem; p[1]=p[0]-1;
	}else{
		p[0]=hook->hook; p[1]=hook->hook+nB; p[2]=p[1]+1;
	}
	memset(p[0],-1,nB); memset(p[2],0,rem-1);
	unb&=7; memset(p[1],bytemsk(nb<0?-unb:unb),1);
}

