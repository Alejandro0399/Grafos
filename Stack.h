#ifndef STACK_H_
#define STACK_H_
#include "List.h"
typedef struct strStack * Stack;
typedef void * Type;


Stack stack_create(void (*destructor)(Type));
int   stack_size(Stack);
bool  stack_isEmpty(Stack);
Type  stack_top(Stack);
void  stack_push(Stack, Type);
Type  stack_pop(Stack);
void  stack_destroy(Stack);


#endif /* STACK_H_ */