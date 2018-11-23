#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "List.h"
#include "queue.h"
#include <String.h>
#include "PriorityQueue.h"

struct strGraph{
	List table;
	DestroyFunc destructor;
	PrintFunc printer;
	int size;
	int tiempo;
	Queue cola;
};

struct strVertice{
	List aristas;
	int tiempoDescubrimiento;
	int tiempoTerminacion;
	char* color;
	int distancia;
	Type data;
	struct strVertice *padre;
};

struct strArista{
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
	g->destructor = destructor;
	g->printer = printer;
	printf("Creado\n");
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
	printf("Destruido\n");
}

void graph_addVertex(Graph g, Type u){
	if(g == NULL){
		return;
	}
	Vertex v = (Vertex)malloc(sizeof(struct strVertice));
	v->aristas = NULL;
	v->data = u;
	list_add(g->table, v);
	g->size++;
	printf("Insertado Vertice\n");
}

void graph_deleteVertex(Graph g, Type v){
	if(g == NULL){
		return;
	}
	printf("1\n");
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);
		printf("%d\n", *(int*)vertice->data);
		if(vertice->data == v){
			printf("2\n");
			list_destroy(vertice->aristas);
			list_remove(g->table, i);
		}
		for(int j = 0; j<list_size(vertice->aristas); j++){
			printf("Size: %d\n", list_size(vertice->aristas));
			Edge e = (Edge)list_getdata(vertice->aristas, j);
			printf("%d %d\n", *(int*)e->origen->data, *(int*)e->destino->data);
			if(*(int*)e->origen->data == *(int*)v || *(int*)e->destino->data == *(int*)v){
				printf("3\n");
				list_remove(vertice->aristas, j);
			}
		}
	}
	printf("Vertice eliminado\n");
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
		verticeU->aristas = list_create(g->destructor);
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
	printf("Arista agregada\n");
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
	printf("Arista eliminada\n");
}

void BFS(Graph g, Type start){
	for(int i=0;i<g->size;i++){
		Vertex vertice =(Vertex) list_getdata(g->table,i);
		if(vertice->data!=start){
			vertice->color="Blanco";
			vertice->distancia=2147483647;
			vertice->padre=NULL;
		}
		else{
			vertice->color="Gris";
			vertice->distancia=0;
			vertice->padre=NULL;
			g->cola=queue_create(g->destructor);
			queue_offer(g->cola,vertice);
		}
	}
	while(queue_size(g->cola)>0){
		Vertex verticeU = (Vertex)queue_poll(g->cola);
		if(verticeU->aristas!=NULL){
			for(int i=0;i<list_size(verticeU->aristas);i++){
				Edge e = (Edge)list_getdata(verticeU->aristas,i);
				Vertex verticeV = e->destino;
				if(strcmp(verticeV->color,"Blanco")==0){
					verticeV->color="Gris";
					verticeV->distancia=verticeU->distancia+1;
					verticeV->padre=verticeU;
					queue_offer(g->cola,verticeV);
				}
			}
		}
		verticeU->color="Negro";
	}
}

void visita(Graph g, Vertex u){
	g->tiempo++;
	u->tiempoDescubrimiento=g->tiempo;
	u->color="Gris";
	if(u->aristas!=NULL){
		for(int i=0;i<list_size(u->aristas);i++){
			Edge e = (Edge)list_getdata(u->aristas,i);
			Vertex verticeV=e->destino;
				if(strcmp(u->color,"Blanco")==0){
					verticeV->padre=u;
					visita(g,verticeV);
				}
		}
		u->color="Negro";
		g->tiempo++;
		u->tiempoTerminacion=g->tiempo;
	}
}

void DFS(Graph g){
	for(int i=0;i<g->size;i++){
		Vertex verticeU = (Vertex)list_getdata(g->table,i);
		verticeU->color="Blanco";
		verticeU->padre=NULL;
	}
	g->tiempo=0;
	for(int i=0;i<g->size;i++){
		Vertex verticeU = (Vertex)list_getdata(g->table,i);
		if(strcmp(verticeU->color,"Blanco")==0){
			visita(g,verticeU);
		}
	}

}



void dijkstra(Graph g, Type start){
	Vertex verticeS;
	for(int i=0;i<g->size;i++){
		Vertex VerticeV = (Vertex)list_getdata(g->table,i);
		if(VerticeV->data!=start){
			VerticeV->distancia=2147483647;
		}
		else{
			VerticeV->distancia=0;
			verticeS=VerticeV;
		}
		VerticeV->padre=NULL;
	}
	PriorityQueue minCola=priorityqueue_create(g->destructor,NULL,g->size);
	List S = list_create(g->destructor);
	priorityqueue_offer(minCola,verticeS);
	while(priorityqueue_size(minCola)>0){
		bool existe = False;
		Vertex verticeU = (Vertex)priorityqueue_poll(minCola);
		list_add(S,verticeU);
		for(int i = 0; i<list_size(verticeU->aristas); i++){
			Edge e = (Edge)list_getdata(verticeU->aristas, i);
			Vertex verticeV = e->destino;
			for(int j = 0; j<list_size(S); j++){
				Vertex verticeS = (Vertex)list_getdata(S, i);
				if(*(int*)verticeS->data == *(int*)verticeV->data){
					existe = True;
					break;
				}
			}
			if(!existe){
				if(verticeV->distancia > (verticeU->distancia + e->weight)){
					verticeV->distancia = verticeU->distancia + e->weight;
					verticeV->padre = verticeU;
				}
			}
		}
	}

}

