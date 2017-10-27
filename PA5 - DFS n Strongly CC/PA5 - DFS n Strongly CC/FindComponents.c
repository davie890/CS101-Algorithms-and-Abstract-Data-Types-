/**
* Davie Truong
* dtruong8@ucsc.edu
* 3/7/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 5 - FindComponents Execution file
*/

#include <string.h>
#include <stdlib.h>
#include "Graph.h"
#define MAX_LEN 160

int main(int argc, char* argv[]) {

	FILE *in, *out;
	char line[MAX_LEN];

	//// check command line for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if (out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	int size = 0;								// size variable used to create graph object
	int left = 0;								// used to store the vector point
	int right = 0;								// used to store the edge point of the vector
	fgets(line, MAX_LEN, in);					// get the first line to use as size of graph
	sscanf(line, "%d", &size);					// coverts the line data to int and stores in size
	Graph G = newGraph(size);					// create a graph object with given size
	List s = newList();							// creates a new list used as a stack for finished vertex
	for (int i = 1; i <= size; i++) {			// initially create this list so DFS goes in increasing order 1 to size
		append(s, i);							// append the order to the stack
	}

	while (fgets(line, MAX_LEN, in) != NULL) {	// gets the vector and edges from the file
		sscanf(line, "%d %d", &left, &right);	// stores it in local variable
		if (left == 0 && right == 0) {			// if the input values are the cut off in the file
			break;
		}
		addArc(G, left, right);					// add the arc to the vector
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);							// print the graph
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	DFS(G, s);									// run DFS on the original graph to get the updated stack
	Graph T = transpose(G);						// make new graph of the Transpose of G
	DFS(T, s);									// run DFS on the transposed graph with the new stack to get the strongly connected components
	int numOfScc = 0;							// used to keep trach the number of strongly connected components;
	moveFront(s);								// move the cursor to the front of the stack
	while (index(s) != -1) {					// run until the stack is empty
		if (getParent(T, get(s)) == NIL) {			// if the parent for current value from the stack is NIL, that means that is the root of a SCC
			numOfScc += 1;							// increase the counter for number of strongly connected components
		}
		moveNext(s);							// move to the next value on the stack
	}

	List collectionOfScc[numOfScc];			// used to store the differnt lists of SCC vertex
	for (int i = 0; i < numOfScc; i++) {	// runs for the number of strongly connected components that exist
		collectionOfScc[i] = newList();		// create a new list for each group of strongly connected components 
	}

	moveBack(s);							// start at the back of the stack 
	int i = 0;								// the starting point for the collectionOfScc[i]
	while (index(s) != -1) {				// while the cursor hasn't fallen off the stack
		if (getParent(T, get(s)) == NIL) {	// if the current value of the stack is a root put it at the front of the list for that list of SCC
			prepend(collectionOfScc[i], get(s));	
			i += 1;							// increment i so that it can add the new SCC vectors to the next list in the array of collectionOfScc
		}
		else {
			prepend(collectionOfScc[i], get(s));	// prepend the current s value so to list of the current position we are in the array
		}
		movePrev(s);						// go to the next value on the stack
	}

	fprintf(out, "\nG contains %d strongly connected components:", numOfScc);
	for (int i = 0; i < numOfScc; i++) {
		fprintf(out, "\nComponent %d: ", i + 1);
		printList(out, collectionOfScc[i]);
		freeList(&(collectionOfScc[i]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////
	freeList(&s);								// release memory of the list used as a stack 
	freeGraph(&T);								// release memory of the graph object
	freeGraph(&G);								// releases memory of the graph object
	fclose(in);									// closes the input and output file
	fclose(out);
	return(0);
}