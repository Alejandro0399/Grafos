#ifndef GRAFO_H_
#define GRAFO_H_

#include "List.h"

typedef struct strGraph * Graph;
typedef void (*DestroyFunc) (Type);
typedef void (*PrintFunc) (Type);
typedef struct strVertice *Vertex;

Graph graph_create(PrintFunc printer, DestroyFunc destructor);
void graph_destroy(Graph g);
void graph_addVertex(Graph g, Type u);
void graph_deleteVertex(Graph g, Type v);
void graph_addEdge(Graph g, Type u, Type v, double weight);
void graph_deleteEdge(Graph g, Type u, Type v);
void imprimirGrafo(Graph g);
List getAristas(Vertex g);

void BFS(Graph g, Type start);
void DFS(Graph g);
void dijkstra(Graph g, Type start);



#endif
