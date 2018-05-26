#include"../mem.h"

#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

int memshiftB(const memshift_ctx*ctx, size_t nB){
	size_t rem;
	unsigned char dir=(ctx->op&0x10)>>4, type=ctx->op&3;
	if(type>1){
		nB%=ctx->size; rem=ctx->size-nB;
		char*tmp = malloc(nB);
		if(!tmp)return -1;
		if(dir){
			memcpy(tmp, ctx->src+rem, nB);
			memmove(ctx->dest+nB, ctx->src, rem);
			memcpy(ctx->dest, tmp, nB);
		}else{
			memcpy(tmp, ctx->src, nB);
			memmove(ctx->dest, ctx->src+nB, rem);
			memcpy(ctx->dest+rem, tmp, nB);
		}
		free(tmp);
	}else{
		char fill = ctx->op==SAR&&(0x80&*(char*)ctx->src)?0xff:0;
		if(ctx->size<nB)memset(ctx->dest,fill,ctx->size);else{
			rem = ctx->size-nB;
			if(dir){
				memmove(ctx->dest+nB, ctx->src, rem);
				memset(ctx->dest, fill, nB);
			}else{
				memmove(ctx->dest, ctx->src+nB, rem);
				memset(ctx->dest+rem, fill, nB);
			}
		}
	}
	return 0;
}
int memshiftb(const memshift_ctx*ctx, size_t nb){
	size_t nB=nb>>3;
	if(nB)if(memshiftB(ctx,nB))return -1;
	if(!(nb&=7))goto END;
	unsigned char dir=(ctx->op&0x10)>>4, type=ctx->op&3;
	unsigned char remb=8-nb, msk, oflo, newoflo, *c;
	size_t size;
	if(type>1){
		size = ctx->size;
		if(dir){
			c = ctx->dest;
			membitmsk(&msk, 1, -nb);
			for(oflo=(msk&c[ctx->size-1])<<remb;size;--size){
				newoflo = (msk&*c)<<remb;
				*c = (*c>>nb)|oflo;
				oflo=newoflo; ++c;
			}
		}else{
			c = ctx->dest+size-1;
			membitmsk(&msk, 1, nb);
			for(oflo=(msk&*(char*)ctx->dest)>>remb;size;--size){
				newoflo = (msk&*c)>>remb;
				*c = (*c<<nb)|oflo;
				oflo=newoflo; --c;
			}
		}
	}else if(ctx->size<nB);else{
		size = ctx->size-nB;
		if(dir){
			c = ctx->dest+nB;
			membitmsk(&msk, 1, -nb);
			for(
				oflo=ctx->op==SAR&&(0x80&*(char*)ctx->src)?(0xff&msk)<<remb:0;
				size;--size
			){
				newoflo = (msk&*c)<<remb;
				*c = (*c>>nb)|oflo;
				oflo=newoflo; ++c;
			}
		}else{
			c = ctx->dest+size;
			membitmsk(&msk, 1, nb);
			for(oflo=0;size;--size){
				newoflo = (msk&*c)>>remb;
				*c = (*c<<nb)|oflo;
				oflo=newoflo; --c;
			}
		}
	}
	END:return 0;
}
int memshiftt(const memshift_ctx*ctx, size_t nb){
	return 0;
}

