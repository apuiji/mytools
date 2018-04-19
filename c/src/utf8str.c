#include"utf8str.h"

static size_t utf8chrlen(unsigned char);
size_t utf8strlen(const char*s){
	int j=0, k=0;
	for(char ch=s[j];ch!='\0';ch=s[j]){
		j += utf8chrlen(ch);
		++k;
	}
	return k;
}
char* utf8strget(char*s, int i){
	int j=0, k=0;
	for(char ch=s[j];k<i&&ch!='\0';ch=s[j]){
		j += utf8chrlen(ch);
		++k;
	}
	return s+j;
}
size_t utf8chrlen(unsigned char ch0){
	if(ch0>=0xfc)return 6;
	if(ch0>=0xf8)return 5;
	if(ch0>=0xf0)return 4;
	if(ch0>=0xe0)return 3;
	if(ch0>=0xc0)return 2;
	return 1;
}

