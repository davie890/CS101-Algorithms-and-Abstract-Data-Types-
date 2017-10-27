/**
* Davie Truong
* dtruong8@ucsc.edu
* 3/7/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 5 - Graph ADT testing file
*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {
	int size = 5;
	Graph G = newGraph(size);

	printf("Test output for Empty Graph\n");
	printGraph(stdout, G);			// Printing an empty Graph
	// 1: 
	// 2: 
	// 3: 
	// 4:
	// 5:
	printf("Order: %d\n", getOrder(G));						// 5
	printf("Size: %d\n", getSize(G));						// 0
	printf("Parent of 1: %d\n", getParent(G, 1));			// -2
	printf("Discover Time of 1: %d\n", getDiscover(G, 1));	// -1
	printf("Finish Time of 1: %d\n\n", getFinish(G, 1));	// -1
	///////////////////////////////////////////////////////////////////
	printf("///////////////////////////////////////////////////////////////////\n");
	printf("Testing addArc\n");
	Graph B = newGraph(8);
	addArc(B, 1, 2);
	addArc(B, 2, 3);
	addArc(B, 2, 5);
	addArc(B, 2, 6);
	addArc(B, 3, 4);
	addArc(B, 3, 7);
	addArc(B, 4, 3);
	addArc(B, 4, 8);
	addArc(B, 5, 1);
	addArc(B, 5, 6);
	addArc(B, 6, 7);
	addArc(B, 7, 6);
	addArc(B, 7, 8);
	addArc(B, 8, 8);
	printGraph(stdout, B);
	// 1: 2
	// 2: 3 5 6
	// 3: 4 7 
	// 4: 3 8 
	// 5: 1 6
	// 6: 7 
	// 7: 6 8 
	// 8: 8
	///////////////////////////////////////////////////////////////////
	printf("\n///////////////////////////////////////////////////////////////////\n");
	List s = newList();
	for (int i = 1; i <= 8; i++) {
		append(s, i);
	}
	printf("\nTest DFS()\n");
	DFS(B, s);
	printf("Parent of 2: %d\n", getParent(B, 2));				// 1			
	printf("Discover Time of 1: %d\n", getDiscover(B, 1));		// 1
	printf("Finish Time of 1: %d\n\n", getFinish(B, 1));		// 16
	///////////////////////////////////////////////////////////////////
	printf("///////////////////////////////////////////////////////////////////\n");
	printf("Test copyGraph()\n");
	Graph T = copyGraph(B);
	printGraph(stdout, T);					// test copyGraph
	// 1: 2
	// 2: 3 5 6
	// 3: 4 7 
	// 4: 3 8 
	// 5: 1 6
	// 6: 7 
	// 7: 6 8 
	// 8: 8
	freeGraph(&T);

	printf("Test for Values in stack after DFS\n");
	printList(stdout, s);									 // stack : 1 2 5 3 7 6 4 8
	printf("\n\n");
	///////////////////////////////////////////////////////////////////
	printf("///////////////////////////////////////////////////////////////////\n");
	printf("Test transpose(B)\n");
	T = transpose(B);
	printGraph(stdout, T);
	// 1: 5
	// 2: 1 
	// 3: 2 4
	// 4: 3 
	// 5: 2
	// 6: 2 5 7
	// 7: 3 6
	// 8: 4 7 8
	DFS(T, s);
	printf("Parent of 2: %d\n", getParent(T, 2));				// 5			
	printf("Discover Time of 1: %d\n", getDiscover(T, 1));		// 1
	printf("Finish Time of 1: %d\n", getFinish(T, 1));			// 6
	printf("Test for Values in stack after DFS\n");
	printList(stdout, s);										// stack : 8 7 6 3 4 1 5 2
	///////////////////////////////////////////////////////////////////
	printf("///////////////////////////////////////////////////////////////////\n");

	// Free objects 
	freeList(&s);
	freeGraph(&G);
	freeGraph(&T);
	freeGraph(&B);
	return(0);
}