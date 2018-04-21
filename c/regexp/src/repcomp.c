#include"regexp.h"
#include"reppat.h"

#include<stdarg.h>
#include<stdbool.h>
#include<stdlib.h>

#define F_COMP(name) int comp_##name(\
	linked_t*pathead, const char*exp, int*expi, ...)
#define F_COMP_EXEC(name) static F_COMP(name);extern F_EXEC(name);
F_COMP_EXEC(common);	F_COMP_EXEC(escape); F_COMP_EXEC(or);
F_COMP_EXEC(group);	F_COMP_EXEC(chrset);	F_COMP_EXEC(chrcls);
F_COMP_EXEC(count);
int repcomp(regexp_t*me, const char*exp, int cflags){
	me->flags = flags;
	me->newline = "\n";
	me->chrset = chrsize_ascii;
	linked_t pathead;
	int expi = 0;
	int ecd = comp_group(&pathead, exp, &expi, 0, 0, 0);
	me->pats = pathead.next;
	if(ecd)repfree(me);
	return ecd;
}
F_COMP(common){
	va_list vargs;	va_start(vargs, expi);
	pat_t*parent = va_arg(vargs, pat_t*);
	va_end(vargs);
	pat_group*parent_as_group = (pat_group*)parent;
	pat_chrset*parent_as_chrset = (pat_chrset*)parent;
	bool isrootgrp = parent->matcher==pat_chrset?false:!(
		parent_as_group->gindex||parent_as_group->reverse);
	pat_common*pat = (pat_common*)malloc(sizeof(pat_common));
	pat->proto->matcher = exec_common;
	linkedins(pathead, pat->proto->proto, NULL);
	pat->str->point = calloc(
		pat->str->esize=sizeof(char),
		pat->str->size=32);
	pat->str->length = 0;
	int ecd = 0;
	LOOP:for(char ch=exp[*expi];true;ch=exp[++*expi]){
		switch(ch){
		case'\0':
			if(parent->matcher==exec_chrset)ecd=REG_EBRACK;
			else if(parent->matcher==exec_group&&!isrootgrp)ecd=REG_EPAREN;
		case'\\':
			break LOOP;
		case')':
			if(parent->matcher==exec_group&&isrootgrp)ecd=REG_EPAREN;
			break;
		case']':
			if(parent->matcher==exec_chrset)break LOOP;
		case'(':case'[':case'{':case'?':case'+':case'*':case'.':case'|':
			if(parent->matcher==exec_group)break LOOP;
			break;
		case'-':
			if(parent->matcher==exec_chrset)break LOOP;
			break;
		}
		if(ecd)break;
		varrayc(pat->str, pat->str->length, &ch);
	}
	return ecd;
}
F_COMP(escape){
	char ch = exp[*expi];
	
	switch(ch){
	case'd':
	}
}

