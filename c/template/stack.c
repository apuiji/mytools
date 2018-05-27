#include"stack.h"

linked_t*stackpop(stack_t*me){
	linked_t*out = me->next;
	if(out)me->next=out->next;
	return out;
}

