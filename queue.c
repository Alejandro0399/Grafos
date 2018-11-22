#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "grafo.h"
#include "List.h"

struct strNode
{
	Type data;
	struct strNode* next;
};

typedef struct strNode* Node;

struct strQueue
{
	int size;
	Node first;
	Node last;
	void (*destructor) (void *);
};


Queue queue_create(void (*destructor)(void *))
{
	Queue q = (Queue) malloc (sizeof(struct strQueue));
	q->first = q->last = NULL;
	q->size = 0;
	q->destructor = destructor; //el parametro se asigna al atributo
	return (q);
}

int   queue_size(Queue q) //Extrae el tama�o de la cola
{
	if(q == NULL)
		return (-1);
	return (q->size);
}
bool  queue_isEmpty(Queue q) //	�El primero es nulo?
{
	return (q == NULL || q->size == 0);
}
Type  queue_peek (Queue q) //Consulta qui�n est� al frente (no elimina)
{
	if(queue_isEmpty(q))
		return (NULL);
	return (q->first->data);
}
void  queue_offer(Queue q, Type t) //Se forma uno nuevo (colocarlo al final)
{
	if(q == NULL)
		return;
	Node n = (Node) malloc(sizeof(struct strNode));
	n->data = t;
	n->next = NULL;

	if(q->size == 0)
		q->first = n;
	else
		q->last->next = n;

	q->last = n;
	q->size++;
}

Type  queue_poll(Queue q) //Atiende al que est� al frente (elimina)
{
	if(queue_isEmpty(q))
		return (NULL);
	Type t = q->first->data;
	Node n = q->first;

	q->first = q->first->next;
	free(n);
	q->size--;

	if(q->size == 0)
		q->last = NULL;

	return (t);
}

void  queue_destroy(Queue q)
{
	if(q == NULL)
			return;
	Node current = q->first;
	Node next;

	while(current != NULL)
	{
		next = current->next;
		if(q->destructor != NULL)
			q->destructor(current->data);
		free(current);
		current = next;
	}
	free(q);
}
