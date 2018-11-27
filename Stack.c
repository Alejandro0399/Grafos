#include "Stack.h"
#include <stdlib.h>


struct strNode
{
	struct strNode * prior;
	Type data;
};

typedef struct strNode * Node;

struct strStack
{
	struct strNode * top;
	int size;
	void (*destructor)(Type);
};

Stack stack_create(void (*destructor)(Type))
{
	Stack s = (Stack) malloc(sizeof(struct strStack));
	s->destructor = destructor;
	s->size = 0;
	s->top = NULL;
	return (s);
}

int stack_size(Stack s)
{
	if(s == NULL)
		return (-1);
	return (s->size);
}

bool stack_isEmpty(Stack s)
{
	return (s == NULL || s->size == 0);
}

Type stack_top(Stack s)
{
	if(s == NULL || s->size == 0)
		return NULL;
	return (s->top->data);
}

void stack_push(Stack s, Type t)
{
	if(s == NULL)
		return;
	Node n = (Node) malloc(sizeof(struct strNode));
	n->data = t;
	n->prior = s->top;
	s->top = n;
	s->size++;
}

Type stack_pop(Stack s)
{
	if(stack_isEmpty(s))
		return NULL;
	Type t = s->top->data;
	Node n = s->top;
	s->top = s->top->prior;
	free(n);
	s->size--;
	return (t);
}

void stack_destroy(Stack s)
{
	if(s == NULL)
		return;

	Node current, prior;
	current = s->top;

	while(current != NULL)
	{
		prior = current->prior;
		if(s->destructor != NULL)
			s->destructor(current->data);
		free(current);
		current = prior;
	}

	free(s);
}