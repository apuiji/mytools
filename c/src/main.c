#include<stdlib.h>
#include<stdio.h>
#include"varray.h"

void main(){
	size_t tsize=sizeof(int), size=4;
	varray_t varray = {
		point:calloc(tsize,size),
		tsize:tsize, length:0, size:size,
	};
	for(int i=0;i<5;++i){
		int value = i*2;
		varrayc(&varray, varray.length, &value);
	}
	for(int i=0;i<varray.length;++i){
		printf("%d,",*(int*)varrayr(&varray,i));
	}
	printf("\n");
}

