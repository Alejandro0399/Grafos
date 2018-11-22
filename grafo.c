#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "List.h"
#include "queue.h"

struct strGraph{
	List table;
	DestroyFunc destrcutor;
	PrintFunc printer;
	int size;
};

struct strVertice{
	List aristas;
	Type data;
	struct strVertice *padre;
};

struct strArista{
	char* color;
	struct strVertice *origen;
	struct strVertice *destino;
	double weight;
};

typedef struct strVertice *Vertex;
typedef struct strArista *Edge;

Graph graph_create(PrintFunc printer, DestroyFunc destructor){
	Graph g = (Graph)malloc(sizeof(struct strGraph));
	g->table = list_create(NULL);
	g->size = 0;
	g->destrcutor = destructor;
	g->printer = printer;
	return g;
}

void graph_destroy(Graph g){
	if (g == NULL){
		return;
	}
	for(int i = 0; i<g->size; i++){
		Vertex v = (Vertex)list_getdata(g->table, i);
		if(v->aristas != NULL){
			list_destroy(v->aristas);
		}
	}
	list_destroy(g->table);
	free(g);
}

void graph_addVertex(Graph g, Type u){
	if(g == NULL){
		return;
	}
	Vertex v = (Vertex)malloc(sizeof(struct strVertice));
	v->aristas = NULL;
	v->data = u;
	list_add(g->table, v);
}

void graph_deleteVertex(Graph g, Type v){
	if(g == NULL){
		return;
	}
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);
		if(vertice->data == v){
			list_destroy(vertice->aristas);
			list_remove(g->table, i);
		}
		for(int j = 0; j<list_size(vertice->aristas); j++){
			Edge e = (Edge)list_getdata(vertice->aristas, j);
			if(e->origen->data == v || e->destino->data == v){
				list_remove(vertice->aristas, j);
			}
		}
	}
}

void graph_addEdge(Graph g, Type u, Type v, double weight){
	if(g == NULL){
		return;
	}
	bool existeU = False;
	bool existeV = False;
	Vertex verticeU;
	Vertex verticeV;
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);
		if(vertice->data == u){
			existeU = True;
			verticeU = vertice;
		}
		if(vertice->data == v){
			existeV = True;
			verticeV = vertice;
		}
	}
	if(existeU == False || existeV == False){
		return;
	}
	if(verticeU->aristas == NULL){
		verticeU->aristas = list_create(g->destrcutor);
	}
	existeV = False;
	for(int i = 0; i<list_size(verticeU->aristas); i++){
		Edge arista = (Edge)list_getdata(verticeU->aristas, i);
		if(arista->destino->data == v){
			existeV = True;
		}
	}
	if(existeV){
		return;
	}
	Edge e = (Edge)malloc(sizeof(struct strArista));
	e->origen = verticeU;
	e->destino = verticeV;
	e->weight = weight;
	list_add(verticeU->aristas, e);
}

void graph_deleteEdge(Graph g, Type u, Type v){
	if(g == NULL){
		return;
	}
	for(int i = 0; i<g->size; i++){
		Vertex verticeU = list_getdata(g->table, i);
		if(verticeU->data == u){
			for(int j = 0; j<list_size(verticeU->aristas); j++){
				Edge e = (Edge)list_getdata(verticeU->aristas, j);
				if(e->destino->data == v){
					list_remove(verticeU->aristas, j);
					break;
				}
			}
			break;
		}
	}
}

void BFS(Graph g, Type start){

}

void DFS(Graph g){

}

void dijkstra(Graph g, Type start){

}

