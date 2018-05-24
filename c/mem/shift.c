#include"../mem.h"

#include<string.h>

typedef struct{
	char*dest; const char*src;
	size_t size; size_t div8, rem8;
	unsigned char mod8, ful8;
	char dir, type;
}ctx_t;
void memshift(
	void*dest, const void*src, size_t size,
	size_t nbit, int dir_type
){
	ctx_t ctx = {
		dest:dest, src:src,
		size:size, div8:nbit>>3, mod8:nbit&7,
		dir:dir_type&0x10, type:ctx->dir_type&0xf,
	};
	ctx->rem8=size-ctx->mod8;	ctx->ful8=8-ctx->mod8;
	void(*fn)(ctx_t*);
	switch(dir_type&0x0f){
	case 0:
	case 1:fn=shx;break;
	case 2:fn=rox;break;
	case 3:fn=rcx;break;
	default:return;
	}
	fn(&ctx);
}
static void shx(ctx_t*ctx){
	size_t rem8 = ctx->rem8;
	if(rem8<0){
		memset(ctx->dest, 0, ctx->size);
		return;
	}
	if(ctx->dir){
		unsigned char*uc = ctx->dest+ctx->div8;
		if(ctx->div8){
			memmove(uc, src, rem8);
			memset(ctx->dest, ctx->type?0xff:0, ctx->div8);
		}
		if(ctx->mod8){
			unsigned char msk;membitmsk(&msk,1,-ctx->mod8);
			for(unsigned char oflow=0,newoflow;rem8;--rem8){
				newoflow = (*uc++&msk)<<ful8;
				*uc>>=mod8; *uc|=oflow;
				oflow = newoflow;
			}
		}
	}else{
		if(ctx->div8){
			memmove(ctx->dest, ctx->src+ctx->div8, rem8);
			memset(ctx->dest+rem8, 0, ctx->div8);
		}
		if(ctx->mod8){
			unsigned char msk, *uc=ctx->dest+ctx->rem8;
			membitmsk(&msk, 1, ctx->mod8);
			for(unsigned char oflow=0,newoflow;rem8;--rem8){
				newoflow = (*--uc&msk)>>ctx->ful8;
				*uc<<=ctx->mod8; *uc|=oflow;
				oflow = newoflow;
			}
		}
	}
}
static void rox(ctx_t*ctx){
	
}

