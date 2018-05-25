#include"../chrset.h"

#include<stdlib.h>
#include"../template/vlarr.h"

size_t chrset_lengifwcs(const chrset_t*me, const char*str, size_t size){
	size_t leng=0, i=0;
	for(;i<size&&str[i];i+=me->c2wc(NULL,str+i))++leng;
	return leng;
}
size_t chrset_sizeifstr(const chrset_t*me, const wchar_t*wcs, size_t leng){
	size_t size=0, i=0;
	for(;i<leng&&wcs[i];++i)size+=me->wc2c(NULL, wcs[i]);
	return size;
}
char*chrset_idxifwcs(const chrset_t*me, const char*str, size_t size, off_t i){
	size_t j=0; unsigned char chrsize;
	for(;i&&*str;--i)if(j>=size)return NULL;else{
		chrsize=me->c2wc(NULL,str); j+=chrsize; str+=chrsize;
	}
	return str;
}

int chrset_str2wcs(
	wchar_t**outwcs, size_t*outleng,
	const chrset_t*me, const char*str, size_t size
){
	vlarr_t wcs = {
		hook:NULL, esize:sizeof(wchar_t), length:0, mxleng:0,
	};
	if(vlarr_releng(&wcs,size>>1))goto ERR;
	wcs.length = 0;
	off_t i=0; unsigned char chrsize; wchar_t wc;
	for(;i<size&&*str;i+=chrsize){
		chrsize = me->c2wc(&wc,str);
		if(vlarr_c(&wcs,wcs.length,&wc))goto FREE;
		str += chrsize;
	}
	if(
		vlarr_c(&wcs,wcs.length,&(wc=0))||
		vlarr_releng(&wcs,wcs.length)
	)goto FREE;
	*outwcs=wcs.hook; *outleng=wcs.length;
	return 0;
	FREE:free(wcs.hook);
	ERR:return -1;
}
int chrset_wcs2str(
	char**outstr, size_t*outsize,
	const chrset_t*me, const wchar_t*wcs, size_t leng
){
	vlarr_t str = {
		hook:NULL, esize:1, length:0, mxleng:0,
	};
	if(vlarr_releng(&str,leng<<1))goto ERR;
	str.length = 0;
	off_t i=0; unsigned char chrsize;
	for(;i<leng&&*wcs;++i){
		chrsize = me->wc2c(NULL,*wcs);
		if(vlarr_releng(&str,str.length+chrsize))goto FREE;
		me->wc2c(str.hook+str.length-chrsize, *wcs, chrsize);
		++wcs;
	}
	if(
		vlarr_c(&str,str.length,NULL)||
		vlarr_releng(&str,str.length)
	)goto FREE;
	*(char*)(str.hook+str.length-1) = 0;
	*outstr=str.hook; *outsize=str.length;
	return 0;
	FREE:free(str.hook);
	ERR:return -1;
}

