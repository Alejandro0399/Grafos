#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "List.h"

struct strGraph{
	List table;
	DestroyFunc destrcutor;
	PrintFunc printer;
	int size;
};

struct strVertice{
	char* color;
	Type data;
	struct strVertice *padre;
	double weight;
	Type arista;
};

typedef struct strVertice * Vertex;

Graph graph_create(PrintFunc printer, DestroyFunc destructor){
	Graph g = (Graph)malloc(sizeof(struct strGraph));
	g->table = list_create(NULL);
	g->size = 1;
	g->destrcutor = destructor;
	g->printer = printer;
	return g;
}

void visita(Graph g, Vertex v){
	v->color = "Gris";
}

void graph_destroy(Graph g){
	list_destroy(g->table);
	free(g);
}

void graph_addVertex(Graph g, Type u){
	if(g == NULL){
		return;
	}
	Vertex vertice = (Vertex)malloc(sizeof(struct strVertice));
	vertice->data = u;
	vertice->arista = NULL;
	list_add(g->table, vertice);
	g->size++;
}

void graph_deleteVertex(Graph g, Type v){
	if(g == NULL){
		return;
	}
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);
		if(vertice->arista == v){
			vertice->arista = NULL;
		}
		if(vertice->data == v){
			list_remove(g->table, i);
		}
	}
}

void graph_addEdge(Graph g, Type u, Type v, double weight){ //¿Qué pasa si ya existe un arista entre dos vertices y se usa esta funcion?
	if(g == NULL){
		return;
	}
	bool existeU = False;
	bool existeV = False;
	int index;
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);
		if(vertice->data == u){
			existeU = True;
			index = i;
		}
		if(vertice->data == v){
			existeV = True;
		}
	}
	if(existeU == False || existeV == False){
		return;
	}
	Vertex vertice = (Vertex)list_getdata(g->table, index);
	vertice->arista = v;
	vertice->weight = weight;
}

void graph_deleteEdge(Graph g, Type u, Type v){
	if(g == NULL){
		return;
	}
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);
		if(vertice->data == u && vertice->arista == v){
			vertice->arista = NULL;
			break;
		}
	}
}

void BFS(Graph g, Type start){

}

void DFS(Graph g){
	int tiempo = 0;
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);
		vertice->color = "Blanco";
		vertice->padre = NULL;
	}
}

void dijkstra(Graph g, Type start){

}

