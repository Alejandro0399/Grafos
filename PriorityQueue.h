#include "List.h"

typedef void* Type;
typedef struct strPriorityQueue* PriorityQueue;
typedef int (*CompareFunc) (Type, Type);
typedef void (*DestroyFunc) (Type);

PriorityQueue priorityqueue_create(DestroyFunc dF, CompareFunc cF, int capacity);
void priorityqueue_destroy(PriorityQueue);
int priorityqueue_size(PriorityQueue);
void priorityqueue_offer(PriorityQueue, Type);
Type priorityqueue_peek(PriorityQueue);
Type priorityqueue_poll(PriorityQueue);
void print_pq(PriorityQueue);
