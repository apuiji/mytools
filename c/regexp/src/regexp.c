#include"regexp.h"

#include<sys/types.h>
#include<stdbool.h>
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include"mem.h"
#include"varray.h"

int repcomp(regexp_t*me, const char*exp, int cflags){
	me->flags = cflags;
	linked_t pathead;
	int expi=0;
	int errcd = comp_group(&pathead, exp, &expi, 0, 0, 0);
	me->pats = pathead.next;
	if(errcd)goto ERR;
	if(exp[*expi]==')'){errcd=REG_EPAREN;goto ERR;}
	return 0;
	ERR:
	repfree(me);
	return errcd;
}
int repexec(
	const regexp_t*me, const char*str,
	size_t nmatch, regmatch_t*matches,
	int eflag
){
	
}
size_t reperror(
	int errcode, const regexp_t*me,
	char*buf, size_t bufsize
){
	
}
void repfree(regexp_t*me){
	
}
static F_COMP(group_pre);
static F_COMP(chrset_pre);
static F_COMP(count_min);
static F_COMP(count_max);
static F_COMP(count_quest);
typedef struct pat_common{
	linked_t proto;
	void*matcher;
	varray_t str;
}pat_common;
F_COMP(common){
	pat_common*pat = (pat_common*)malloc(sizeof(pat_group));
	pat->matcher = exec_common;
	linkedins(pathead, (linked_t*)pat, NULL);
	pat->str->point = calloc(
		pat->str->esize=sizeof(char),
		pat->str->size=32);
	pat->str->length = 0;
	int errcd = 0;
	LOOP:for(char ch=exp[*expi];true;ch=exp[++*expi]){
		switch(ch){
		case'\0':case'\\':
		case'(':case'[':case'{':
		case'?':case'+':case'*':break LOOP;
		default:
			if(varrayc(pat->str, -1, &ch))errcd=REG_ESIZE;
			break;
		}
		if(errcd)break;
	}
	return errcd;
}
F_COMP(escape){
	switch(exp[++*expi]){
	case'\0'
	}
}
typedef struct pat_group{
	linked_t proto;
	void*matcher;
	int gindex;
	bool not;
	linked_t*gpats; 
}pat_group;
F_COMP(group){
	pat_group*pat = (pat_group*)malloc(sizeof(pat_group));
	pat->matcher = exec_group;
	va_list vargs;
	va_start(vargs, expi);
	pat->not = va_arg(vargs, int);
	int nogrp = va_arg(vargs, int);
	int gindex = va_arg(vargs, int);
	pat->gindex = nogrp?-1:(gindex++);
	va_end(vargs);
	linkedins(pathead, (linked_t*)pat, NULL);
	linked_t gpathead;	int errcd=0;
	LOOP:for(char ch=exp[*expi];true;ch=exp[*expi]){
		switch(ch){
		case'\0':case')':break LOOP;
		case'\\':
			errcd = comp_escape(gpathead, exp, expi);break;
		case'(':
			errcd = comp_group_pre(gpathead, exp, expi, gindex);break;
		case'[':
			errcd = comp_chrset_pre(gpathead, exp, expi);break;
		case'{':
			errcd = comp_count_min(gpathead, exp, expi);break;
		case'?':
			errcd = comp_count_quest(gpathead, exp, expi);break;
		case'+':
			errcd = comp_count(gpathead, exp, expi, 1, -1);break;
		case'*':
			errcd = comp_count(gpathead, exp, expi, 0, -1);break;
		default:
			errcd = comp_common(gpathead, exp, expi);break;
		}
		if(errcd)break;
	}
	pat->gpats = linkedreverse(gpathead.next, NULL, NULL);
	return errcd;
}
typedef struct pat_chrset{
	linked_t proto;
	void*matcher;
	bool not;
	linked_t*spats;
}pat_chrset;
F_COMP_EXEC(chrrng);
F_COMP(chrset){
	pat_chrset*pat = (pat_chrset*)malloc(sizeof(pat_chrset));
	pat->matcher = exec_chrset;
	va_list vargs;
	va_start(vargs, expi);
	pat->not = va_arg(vargs, int);
	va_end(vargs);
	linkedins(pathead, (linked_t*)pat, NULL);
	linked_t spathead;	int errcd = 0;
	LOOP:for(char ch=exp[*expi];true;ch=exp[++*expi]){
		switch(ch){
		case'\0':errcd=REG_BADPAT;
		case']':break LOOP;
		case'\\':
			errcd = comp_escape(spathead, exp, expi);break;
		case'-':
			errcd = comp_chrrng(spathead, exp, expi);break;
		default:
			errcd = comp_common(spathead, exp, expi);break;
		}
		if(errcd)break;
	}
	pat->spats = linkedreverse(spathead.next, NULL, NULL);
	return errcd;
}
F_CMOP(group_pre){
	va_list vargs;
	va_start(vargs, expi);
	int not = false;
	int nogrp = false;
	int gindex = va_arg(vargs, int);
	va_end(vargs);
	bool err = true;
	if(exp[*expi]=='?'){
		++*expi;
		if(exp[*expi]=='!'){
			++*expi;
			not = true;
			err = false;
		}
		if(exp[*expi]==':'){
			++*expi;
			nogrp = true;
			err = false;
		}
	}
	return err?REG_BADRPT:comp_group(pathead, exp, expi, not, nogrp, gindex);
}
F_COMP(chrset_pre){
	int not = false;
	if(exp[*expi]=='^'){
		++*expi;
		not = true;
	}
	return comp_chrset(pathead, exp, expi, not);
}

