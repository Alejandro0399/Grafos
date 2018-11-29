#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "List.h"
#include "queue.h"
#include <String.h>
#include "PriorityQueue.h"
#include "Stack.h"

struct strGraph{
	List table;
	DestroyFunc destructor;
	PrintFunc printer;
	int size;
	int tiempo;
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


typedef struct strArista *Edge;

Graph graph_create(PrintFunc printer, DestroyFunc destructor){
	Graph g = (Graph)malloc(sizeof(struct strGraph));
	g->table = list_create(NULL);
	g->size = 0;
	g->destructor = destructor;
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
	
}

void graph_deleteVertex(Graph g, Type v){
	if(g == NULL){
		return;
	}
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);	
		if(vertice->aristas!=NULL){
			for(int j = 0; j<list_size(vertice->aristas); j++){
				Edge e = (Edge)list_getdata(vertice->aristas, j);
				if(*(int*)e->origen->data == *(int*)v || *(int*)e->destino->data == *(int*)v){
					list_remove(vertice->aristas, j);
				}
			}
		}
	}
	for(int i = 0; i<g->size; i++){
		Vertex vertice = (Vertex)list_getdata(g->table, i);
		if(vertice->data == v){
				printf("2\n");
				list_destroy(vertice->aristas);
				list_remove(g->table, i);
				g->size--;
				break;
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
//todo funciona hasta este punto
void BFS(Graph g, Type start){
	Queue cola;
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
			cola=queue_create(g->destructor);
			queue_offer(cola,vertice);
		}
	}
	while(queue_size(cola)>0){
		Vertex verticeU = (Vertex)queue_poll(cola);
		if(verticeU->aristas!=NULL){
			for(int i=0;i<list_size(verticeU->aristas);i++){
				Edge e = (Edge)list_getdata(verticeU->aristas,i);
				Vertex verticeV = e->destino;
				if(strcmp(verticeV->color,"Blanco")==0){
					verticeV->color="Gris";
					verticeV->distancia=verticeU->distancia+1;
					verticeV->padre=verticeU;
					queue_offer(cola,verticeV);
				}
			}
		}
		g->printer(verticeU->data);
		verticeU->color="Negro";
	}
	queue_destroy(cola);
}

void visita(Graph g, Vertex u){
	g->tiempo++;
	u->tiempoDescubrimiento=g->tiempo;
	g->printer(u->data);
	
	u->color="Gris";
	if(u->aristas!=NULL){
		for(int i=0;i<list_size(u->aristas);i++){
			Edge e = (Edge)list_getdata(u->aristas,i);
			Vertex verticeV=e->destino;
				if(strcmp(verticeV->color,"Blanco")==0){
					verticeV->padre=u;
					visita(g,verticeV);
				}
		}
	}
	u->color="Negro";
	g->tiempo++;
	u->tiempoTerminacion=g->tiempo;
}

void DFS(Graph g){
	if(g==NULL) return;
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

int CompareFunction(Type t1, Type t2){
	Vertex v1 = (Vertex)t1;
	Vertex v2 = (Vertex)t2;
	return (v1->distancia) - (v2->distancia);
}

void dijkstra(Graph g, Type start){
	int(*Compare)(Type, Type)=CompareFunction;
	if(g==NULL)return;
	Stack padres=stack_create(g->destructor);
	PriorityQueue minCola=priorityqueue_create(g->destructor,Compare,g->size);
	List S = list_create(g->destructor);
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
		//imprimirGrafo(g);
	}
	
	/*for(int i=0;i<g->size;i++){
		Vertex verticeX = (Vertex)list_getdata(g->table,i);
		priorityqueue_offer(minCola,verticeX);
	}*/
	priorityqueue_offer(minCola,verticeS);
	//printf("sizeS : %d\n",list_size(((Vertex)priorityqueue_poll(minCola))->aristas));
	stack_push(padres,verticeS);
	while(priorityqueue_size(minCola)>0){
		
		bool existe = False;
		Vertex verticeU = (Vertex)priorityqueue_poll(minCola);
		list_add(S,verticeU);
		Vertex verticehijo;
		for(int i = 0; i<list_size(verticeU->aristas); i++){
			//imprimirGrafo(g);
			existe = False;
			Edge e = (Edge)list_getdata(verticeU->aristas, i);
			Vertex verticeV = e->destino;
			if(i==0)verticehijo=verticeV;
			for(int j = 0; j<list_size(S); j++){
				Vertex verticeS = (Vertex)list_getdata(S, j);
				if(CompareFunction((Type)verticeS->data,(Type)verticeV->data)==0){
					existe = True;
					break;
				}
			}
			if(!existe){
				if(verticeV->distancia > (verticeU->distancia + e->weight)){
					verticeV->distancia = verticeU->distancia + e->weight;
					verticeV->padre = verticeU;
					
					priorityqueue_offer(minCola,verticeV);					
				}
			}
			if(verticehijo->distancia < verticeV->distancia)verticehijo=verticeV;
		}
		Vertex vater =(Vertex) stack_top(padres);
		if(verticehijo->padre==vater)
			stack_push(padres,verticehijo);
		
	}
/*	for(int i = 0; i<list_size(verticeU->aristas); i++)
	while(Vertice!=NULL){
		printf("nodo: ");
		g->printer(Vertice->data);
		Vertice=Vertice->padre;
	}*/
	while(stack_size(padres)>0){
		Vertex v =(Vertex)stack_pop(padres);
		printf("node: ");
		g->printer(v->data);
	}
}

void imprimirGrafo(Graph g, int fun){
	if(g==NULL)return;
	if(fun == 0){ // BFS
		for(int i = 0; i<g->size; i++){
			Vertex v = (Vertex)list_getdata(g->table, i);
				printf("Dato: %d Distancia: %d Color : %s\n\t", *(int*)v->data, v->distancia, (char*)v->color);
			if(v->aristas!=NULL){
				for(int j = 0; j<list_size(v->aristas);j++){
					Edge e = (Edge)list_getdata(v->aristas, j);
					printf("-> arista a %d weight: %f color: %s\n\t", *(int*)e->destino->data, e->weight, (char*)e->destino->color);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
	else if(fun == 1){ // DFS
		for(int i = 0; i<g->size; i++){
			Vertex v = (Vertex)list_getdata(g->table, i);
				printf("Dato: %d Color : %s TiempoDescubierto: %d TiempoTerminado: %d\n\t", *(int*)v->data,(char*)v->color,v->tiempoDescubrimiento,v->tiempoTerminacion);
			if(v->aristas!=NULL){
				for(int j = 0; j<list_size(v->aristas);j++){
					Edge e = (Edge)list_getdata(v->aristas, j);
					printf("-> arista a %d weight: %f color: %s\n\t", *(int*)e->destino->data, e->weight, (char*)e->destino->color);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
	else if(fun == 2){ // Dijskra
		for(int i=0;i<g->size;i++){
		Vertex v =(Vertex)list_getdata(g->table,i);
		if(v->padre!=NULL)
			printf("dato: %d distancia: %d  padre: %d \n\t",*(int*)v->data,v->distancia,*(int*)v->padre->data);
		else
			printf("dato: %d distancia: %d \n\t",*(int*)v->data,v->distancia);
		if(v->aristas!=NULL){
			for(int j=0;j<list_size(v->aristas);j++){
				Edge e =(Edge)list_getdata(v->aristas,j);
					printf("-> arista a %d weight: %f\n\t ",*(int*)e->destino->data,e->weight);
			}	
		}
		printf("\n");
	}
	printf("\n");
	}
	/*for(int i=0;i<g->size;i++){
		Vertex v =(Vertex)list_getdata(g->table,i);
		if(v->padre!=NULL)
			printf("dato: %d distancia: %d color: %s  tiempoDescubierto: %d TiempoTerminado: %d padre: %d \n\t",*(int*)v->data,v->distancia,(char*)v->color,v->tiempoDescubrimiento,v->tiempoTerminacion,*(int*)v->padre->data);
		else
			printf("dato: %d distancia: %d color: %s tiempoDescubierto: %d TiempoTerminado: %d\n\t",*(int*)v->data,v->distancia,(char*)v->color,v->tiempoDescubrimiento,v->tiempoTerminacion);
		if(v->aristas!=NULL){
			for(int j=0;j<list_size(v->aristas);j++){
				Edge e =(Edge)list_getdata(v->aristas,j);
					printf("-> arista a %d weight: %f color: %s  ",*(int*)e->destino->data,e->weight,(char*)e->destino->color);
			}	
		}
		printf("\n");
	}
	printf("\n");*/
}

List getAristas(Vertex g){
	if(g == NULL){
		printf("Vale verga\n");
		return NULL;
	}
	return g->aristas;
}

int getdata(Vertex v){
	return *(int*)v->data;
}