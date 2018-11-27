/*
 ============================================================================
 Name        : Proyecto.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void intDestructor(Type t){
	int * pN = (int*)t;
	free(pN);
}
void printerF(Type t){
	int  pN = *(int*)t;
	printf("%d\n", pN);
}

int main(void) {
	Graph g = graph_create(printerF, intDestructor);
	int n1 = 6;
	int n2 = 1;
	int n3 = 5;
	int n4 = 10;
	imprimirGrafo(g);
	graph_addVertex(g, &n1);
	imprimirGrafo(g);
	graph_addVertex(g, &n2);
	imprimirGrafo(g);
	graph_addVertex(g, &n3);
	graph_addVertex(g,&n4);
	imprimirGrafo(g);
	graph_addEdge(g, &n1, &n2, 10);
	imprimirGrafo(g);
	graph_addEdge(g, &n1, &n3, 20);
	imprimirGrafo(g);
	graph_addEdge(g, &n3, &n4, 15);
	//graph_addEdge(g, &n4, &n1, 15);
	imprimirGrafo(g);
	
//	imprimirGrafo(g);
	//printf("De dato %d a:\n", n1);
//	BFS(g,&n1);
//	imprimirGrafo(g);
//	DFS(g);
	dijkstra(g,&n2);
//	imprimirGrafo(g);
	/*graph_deleteVertex(g, &n1);
	imprimirGrafo(g);
	graph_deleteEdge(g, &n2, &n3);
	imprimirGrafo(g);
*/
	
	graph_destroy(g);

	return EXIT_SUCCESS;
}
