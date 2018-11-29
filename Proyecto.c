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
	//-----------------dijkstra
	int n1 = 1;
	int n2 = 2;
	int n3 = 3;
	int n4 = 4;
	int n5 = 5;
	int n6 = 6;
//	imprimirGrafo(g);
	graph_addVertex(g, &n1);
	graph_addVertex(g, &n2);
	graph_addVertex(g, &n3);
	graph_addVertex(g,&n4);
	graph_addVertex(g,&n5);
	graph_addVertex(g,&n6);
	graph_addEdge(g, &n1, &n2, 2);
	graph_addEdge(g, &n1, &n3, 1);
	graph_addEdge(g, &n2, &n4, 1);
	graph_addEdge(g, &n3, &n4, 3);
	graph_addEdge(g, &n3, &n5, 4);
	graph_addEdge(g, &n4, &n6, 2);
	graph_addEdge(g, &n5, &n6, 2);
//	imprimirGrafo(g);
	//------------DFS
	/*int n1 = 1;
	int n2 = 2;
	int n3 = 3;
	int n4 = 4;
	int n5 = 5;
	int n6 = 6;
	imprimirGrafo(g);
	graph_addVertex(g, &n1);
	graph_addVertex(g, &n2);
	graph_addVertex(g, &n3);
	graph_addVertex(g,&n4);
	graph_addVertex(g,&n5);
	graph_addVertex(g,&n6);
	graph_addEdge(g, &n1, &n2, 3);
	graph_addEdge(g, &n1, &n6, 1);
	graph_addEdge(g, &n1, &n5, 1);
	graph_addEdge(g, &n6, &n2, 2);
	graph_addEdge(g, &n6, &n5, 4);
	graph_addEdge(g, &n2, &n5, 5);
	graph_addEdge(g, &n5, &n4, 2);
	graph_addEdge(g, &n4, &n2, 5);
	graph_addEdge(g, &n3, &n4, 2);*/
	
	/*int n6 = 6;
	int n7 = 7;
	int n8 = 8;
	int n9 = 9;
	int n10 = 10;
	int n11 = 11;
	//imprimirGrafo(g);
	graph_addVertex(g, &n6);
	graph_addVertex(g, &n7);
	graph_addVertex(g, &n8);
	graph_addVertex(g,&n9);
	graph_addVertex(g,&n10);
	graph_addVertex(g,&n11);
	graph_addEdge(g, &n6, &n7, 3);
	graph_addEdge(g, &n6, &n11, 3);
	graph_addEdge(g, &n11, &n10, 3);
	graph_addEdge(g, &n7, &n10, 3);
	graph_addEdge(g, &n10, &n9, 3);*/
//	imprimirGrafo(g);
	//printf("De dato %d a:\n", n1);
	//BFS(g,&n6);
	//imprimirGrafo(g, 0);
//	imprimirGrafo(g);
	//DFS(g);
	dijkstra(g,&n1);
	imprimirGrafo(g,2);
	//graph_deleteVertex(g, &n1);
	//imprimirGrafo(g);
	//graph_deleteEdge(g, &n2, &n3);
	//imprimirGrafo(g);

	
	graph_destroy(g);

	return EXIT_SUCCESS;
}
