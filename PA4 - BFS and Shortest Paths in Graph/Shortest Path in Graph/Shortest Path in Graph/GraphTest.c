/**
* Davie Truong
* dtruong8@ucsc.edu
* 2/25/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 4 - Graph ADT testing file
*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {
	int size = 5;
	Graph G = newGraph(size);
	
	// Printing an empty Graph
	printGraph(stdout, G);
	// 1: 
	// 2: 
	// 3: 
	// 4:
	// 5:
	printf("Order: %d\n", getOrder(G)); // 5
	printf("Size: %d\n", getSize(G)); // 0
	printf("Source: %d\n", getSource(G)); // -2
	printf("Parent of 1: %d\n", getParent(G, 1)); // -2
	printf("Distance to source: %d\n\n", getDist(G, 1)); // -1

	addEdge(G, 1, 2);					// testing adding input into the graph
	addEdge(G, 2, 3);
	addEdge(G, 3, 4);

	printGraph(stdout, G);
	// 1: 2
	// 2: 1 3
	// 3: 2 4
	// 4: 3
	// 5:
	printf("\nOrder: %d\n", getOrder(G)); // 5
	printf("Size: %d\n", getSize(G)); // 3
	printf("Source: %d\n", getSource(G)); // -2
	printf("Parent of 1: %d\n", getParent(G, 1)); // -2
	printf("Distance to source: %d\n\n", getDist(G, 1)); // -1

	addEdge(G, 1, 2);	// adding the same edge 
	printGraph(stdout, G);
	// 1: 2
	// 2: 1 3
	// 3: 2 4
	// 4: 3
	// 5:
	printf("Size: %d", getSize(G)); // 3
	printf("\n\n");

	addArc(G, 5, 4);									// testing add arc on the same edge
	addArc(G, 4, 5); 
	printGraph(stdout, G);
	// 1: 2
	// 2: 1 3
	// 3: 2 4
	// 4: 3 5
	// 5: 4
	printf("Size: %d\n", getSize(G)); // 4
	
	BFS(G, 1);													// testing BFS 
	printf("Parent of 2: %d\n", getParent(G, 2)); // 1			// testing get parent
	printf("Distance (1,4): %d\n", getDist(G, 4)); // 3			// testing get distance

	List L = newList();					
	printf("A shortest 1-4 path is: ");
	getPath(L, G, 4);							// testing get path
	printList(stdout, L); // 1 2 3 4
	printf("\n\n");
	freeList(&L);

	makeNull(G);				//testing makeNull
	printGraph(stdout, G);
	// 1: 
	// 2: 
	// 3: 
	// 4:
	// 5:
	printf("Size: %d\n", getSize(G)); // 0			// Testing updated size
	printf("Source: %d\n", getSource(G)); // -2		// testing updates source

	// Free objects 
	freeGraph(&G);
	return(0);
}