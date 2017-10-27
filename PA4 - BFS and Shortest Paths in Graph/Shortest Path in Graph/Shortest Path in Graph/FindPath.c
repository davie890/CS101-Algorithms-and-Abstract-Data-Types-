/**
* Davie Truong
* dtruong8@ucsc.edu
* 2/25/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 4 - FindPath Execution file
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
	
	while (fgets(line, MAX_LEN, in) != NULL) {	// gets the vector and edges from the file
		sscanf(line, "%d %d", &left, &right);	// stores it in local variable
		if (left == 0 && right == 0) {			// if the input values are the cut off in the file
			break;
		}
		addEdge(G, left, right);				// add the edges to the vector
	}
	printGraph(out, G);							// print the graph

	while ((fgets(line, MAX_LEN, in) != NULL)) {	//continue iterating through the file
		fprintf(out, "\n");
		sscanf(line, "%d %d", &left, &right);		// stores the input into local variable
		if (left == 0 && right == 0) {
			break;
		}
		BFS(G, left);								// calls BFS to fill the graph with data
		int dist = getDist(G, right);				// gets the distance for the postion
		if (dist == INF) {							// checks if the distance is disconnected
			fprintf(out, "The distance from %d to %d is infinity\n", left, right);
			fprintf(out, "No %d - %d path exists\n", left, right);
		}
		else {
			List L = newList();						// prints out the distance and shortest path
			fprintf(out, "The distance from %d to %d is %d\n", left, right, dist);
			fprintf(out, "A shortest %d-%d path is: ", left, right);
			getPath(L, G, right);					// calls get path to find the shortest path
			printList(out, L);						// prints the shortest path stored in list L
			fprintf(out, "\n");
			freeList(&L);							// releases memory for the list 
		}
	}
	fprintf(out, "\n");
	freeGraph(&G);								// releases memory of the graph object
	fclose(in);									// closes the input and output file
	fclose(out);
	return(0);
}