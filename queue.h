#ifndef QUEUE_H_
#define QUEUE_H_

#include "List.h"

typedef struct strQueue * Queue;
typedef void* Type;

Queue queue_create(void (*destructor)(void *));
int   queue_size(Queue);	//Extrae el tama�o de la cola
bool  queue_isEmpty(Queue);//	�El primero es nulo?
Type  queue_peek (Queue);	//Consulta qui�n est� al frente (no elimina)
void  queue_offer(Queue, Type);	//Se forma uno nuevo (colocarlo al final)
Type  queue_poll(Queue);	//Atiende al que est� al frente (elimina)
void  queue_destroy(Queue);


#endif /* QUEUE_H_ */
