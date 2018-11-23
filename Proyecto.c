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

int main(void) {
	Graph g = graph_create(NULL, NULL);
	int n1 = 0;
	int n2 = 1;
	int n3 = 2;
	graph_addVertex(g, &n1);
	graph_addVertex(g, &n2);
	graph_addVertex(g, &n3);
	graph_addEdge(g, &n1, &n2, 10);
	graph_addEdge(g, &n2, &n3, 20);
	graph_addEdge(g, &n1, &n3, 15);
	graph_deleteVertex(g, &n1);
	graph_deleteEdge(g, &n2, &n3);

	graph_destroy(g);

	return EXIT_SUCCESS;
}
