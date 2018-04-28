#include"strbuf.h"

#include<errno.h>
#include<stdlib.h>
#include<string.h>

int strbufapp(strbuf_t*me, const char*app, size_t len){
	size_t size = len+1;
	linked_t*node = (linked_t*)malloc(
		sizeof(linked_t)+sizeof(size_t)+size);
	if(errno)return errno;
	node->next = NULL;
	size_t*plen = (size_t*)(node+1);
	*plen = len;
	char*pcont = (char*)(plen+1);
	memcpy(pcont,app,len);	pcont[len]='\0';
	me->totallen += len;
	linkedins(me->tail, node, &(me->tail));
	return 0;
}
int strbufbuild(char**dest, strbuf_t*me){
	*dest = (char*)malloc(me->totallen+1);
	if(errno)return errno;
	for(linked_t*node=me->head.next;node!=NULL;++node){
		size_t*plen = (size_t*)(node+1);
		char*pcont = (char*)(plen+1);
		memcpy(dest, pcont, *plen);
		dest += *plen;
	}*dest = '\0';
	return 0;
}
void strbuffree(strbuf_t*me){
	for(linked_t*node=me->head.next;node!=NULL;++node)free(node);
}

