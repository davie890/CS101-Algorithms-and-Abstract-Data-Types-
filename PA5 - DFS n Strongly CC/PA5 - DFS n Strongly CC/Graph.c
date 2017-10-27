/**
* Davie Truong
* dtruong8@ucsc.edu
* 3/7/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 5 - Graph implementation File
*/

// A Graph ADT Implementation File 
// Contains struct and function definitions

#include<stdlib.h>
#include "Graph.h"

// Structure for the GraphObj
typedef struct GraphObj {
	List * adjMatrix;	// array of Lists whose i elem contains the neighbors of vertex i
	int * color;		// array of ints whose i elem is color(white,Gray, Black) of vertex i
	int * parent;		// array of ints whose i elem is the parent of vertex i
	int * discover;		// array of ints whose i elem is the discover time of the vertex
	int * finish;		// array of ints whose i elem is the finish time of the vertex
	int order;			// number of vertices of the grap
	int size;			// number of edges
}GraphObj;
// Constructor For a Graph
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->adjMatrix = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->parent = calloc(n + 1, sizeof(int));
	G->discover = calloc(n + 1, sizeof(int));
	G->finish = calloc(n + 1, sizeof(int));
	G->order = n;
	G->size = 0;

	// initialize the arrays
	for (int i = 1; i <= n; i++) {		// runs for the number of verices in the graph
		G->adjMatrix[i] = newList();	// initializes each row of the array with lists
		G->color[i] = WHITE;			// white for each vertex index
		G->parent[i] = NIL;				// NIL for each index because DFS() hasn't ran 
		G->discover[i] = UNDEF;			// UNDEF for each vertex index because DFS() hasn't discovered 
		G->finish[i] = UNDEF;			// UNDEF for each vertex index because DFS() hasn't finished
	}
	return G;			// returns a graph pointing to a newly created GraphObj
}
// Destructor for Graph objected
void freeGraph(Graph * pG) {			// *pG : the address of a Graph reference
	if (pG != NULL && *pG != NULL) {			// pointer and the address of the pointer is not null
		free((*pG)->color);						// free the color array
		free((*pG)->parent);					// free the parent array
		free((*pG)->discover);					// free the discover array
		free((*pG)->finish);					// free the finish array
		for (int i = 1; i <= (*pG)->order; i++) {	// loop through the number of vertexes 
			freeList(&((*pG)->adjMatrix[i]));			// free the lists of each vertex index in the array
		}
		free((*pG)->adjMatrix);					// free the adjMatrix array
		free(*pG);								// free graphObject
		*pG = NULL;								// set the address to null
	}
}

// Access Functions
// Returns the Order Value (Number of Vertex)
int getOrder(Graph G) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling getOrder() on a NULL Graph reference");
		exit(1);
	}
	return G->order;		// returns the number of Vertex in the array
}
// Returns the Size Value (Number of Edges)
int getSize(Graph G) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling getSize() on a NULL Graph reference");
		exit(1);
	}
	return G->size;			// returns the number of Edges in the graph
}
// Returns the parent of vertex u in the DFS tree created by DFS
int getParent(Graph G, int u) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling getParent() on a NULL Graph reference");
		exit(1);
	}
	if (u < 1 || G->order < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling getParent() with an incorrect vertex");
		exit(1);
	}
	return G->parent[u];	// returns the parent value of the given vertex in the BFS tree
}
// Returns the discover time of vertex u
int getDiscover(Graph G, int u) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling getDiscover() on a NULL Graph reference");
		exit(1);
	}
	if (u < 1 || getOrder(G) < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling getDiscover() with an incorrect vertex");
		exit(1);
	}
	return G->discover[u];
}
// Returns the finish time of vertex u
int getFinish(Graph G, int u) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling getFinish() on a NULL Graph reference");
		exit(1);
	}
	if (u < 1 || getOrder(G) < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling getFinish() with an incorrect vertex");
		exit(1);
	}
	return G->finish[u];
}

// Manipulation Procedures
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling addEdge() on a NULL Graph reference");
		exit(1);
	}
	if (u < 1 || getOrder(G) < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling addEdge() with an incorrect vertex");
		exit(1);
	}
	if (v < 1 || getOrder(G) < v) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling addEdge() with an incorrect vertex");
		exit(1);
	}
	addArc(G, u, v);		// using the addArc function because it does the same thing
	addArc(G, v, u);		// need to call add arc again because it adds single directed edges
							// this way it adds the edges for both u to v and v to u
}
// Inserts a new directed edge from u to v
// (v is added to the adjaceny list of u, but not u to the adjaceny list of v)
void addArc(Graph G, int u, int v) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling addArc() on a NULL Graph reference");
		exit(1);
	}
	if (u < 1 || getOrder(G) < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling addArc() with an incorrect vertex");
		exit(1);
	}
	if (v < 1 || getOrder(G) < v) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling addArc() with an incorrect vertex");
		exit(1);
	}
	moveFront(G->adjMatrix[u]);		// moves cursor of [u] list to front for correct scan and insert
	int flag = 0;					// used to know if an insertion was successful
	if (length((G->adjMatrix[u])) == 0) {	// if the list for the current vector is empty append it
		append((G->adjMatrix[u]), v);
		flag = 1;							// enable succussful flag
	}
	else {									// when there are vector values in the list
		while (flag != 1) {															// run through the list until an insertion has been made
			if (index((G->adjMatrix[u])) != -1 && v == get(G->adjMatrix[u])) {		// if the index isn't off the list and the vector matches with one already on the list
				flag = 1;															// set flag to break out the loop because we don't want double data
			}
			if (index((G->adjMatrix[u])) == -1) {			// if the cursor fell of the list
				append((G->adjMatrix[u]), v);				// append the vector to the back of the list
				flag = 1;									// enable the flag so we know successful insertion for loop to stop
			}
			if (flag != 1 && v < get(G->adjMatrix[u])) {	// if there hasn't been an insertion check if v is less than the current 
				insertBefore((G->adjMatrix[u]), v);			// insert before since v is less than the current
				flag = 1;									// enable the flag for loop control
			}
			moveNext((G->adjMatrix[u]));					// iterates the list to check elements for insertion
		}
	}
	int pairFlag = 0;									// used to test to see if their is a corresponding pair in the adj matrix ie. U-V and V-U
	if (flag == 1) {									// an edge was added to the list
		moveFront(G->adjMatrix[v]);						// start at the beginning of the list
		while (index(G->adjMatrix[v]) != -1 && pairFlag != 1) {			// run until the end of the list or the flag has been enabled
			if (get(G->adjMatrix[v]) == u) {							// if the corresponding pair is found 
				pairFlag = 1;											// enable the pairFlag, used to mean the size has already been added
			}
			moveNext(G->adjMatrix[v]);					// iterate the loop
		}
	}
	if (pairFlag == 0) {								// if the pair flag is not enabled(1) that means the size has not been accounted for
		G->size += 1;									// increase the size by 1
	}
}
// visit function used as a helper function for the DFS function
void visit(Graph G, List s, int x, int * time) {
	G->color[x] = GREY;						// set x to grey for visiting it first time
	G->discover[x] = (++*time);				// set the discover time to current value
	moveFront(G->adjMatrix[x]);				// move to the front of the list for the current vector
	while (index(G->adjMatrix[x]) != -1) {	// runs until the cursor falls off the list 
		int y = get(G->adjMatrix[x]);		// set y to the current value on the list x
		if (G->color[y] == WHITE) {			// runs when the current value hasn't been discoverd
		G->parent[y] = x;					// set the parent of the current value to the x
		visit(G, s, y, time);				// recursively call visit since the current value hasn't been discoverd
		}
		moveNext(G->adjMatrix[x]);			// move to the next value on the list x 
	}
	G->color[x] = BLACK;					// values cant be discovered anymore so color it black to represent that
	G->finish[x] = (++*time);				// give it a finish time
	prepend(s, x);							// append x to the stack because it finished and can't discover anymore
}
// Runs the DFS algorithm on the Graph G 
// with List s, setting the color, parent, discover, and finish fields of G accordingly
void DFS(Graph G, List s) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling DFS() on a NULL Graph reference");
		exit(1);
	}
	if (length(s) != getOrder(G)) {
		printf("Graph Error: called DFS() without equal sizes\n");
		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++) {	// runs for the number of vertexes 
		G->parent[i] = NIL;			// resets the array of the DFS data to make sure everything is 
		G->discover[i] = UNDEF;		// correct before setting the data 
		G->finish[i] = UNDEF;		
		G->color[i] = WHITE;
	}
	int time = 0;					// varible used to update discover and finish
	moveFront(s);					// start at the front of the stack
	while (index(s) != -1) {			// runs when there are values in the stack
		int x = get(s);				// the current index on the stack
		if (G->color[x] == WHITE) {	// if the vector hasn't been discovered
			visit(G, s, x, &time);		// visit it with the Graph, Stack, current value of the stack,
		}									// and reference of time so that it can be changed
		moveNext(s);
	}
	// delete the previous vertexs on the stack while keeping the new ones
	int halfsize = length(s) / 2;			// size of the stack divide by 2, stack contains 2x	order
	for (int i = 0; i < halfsize; i++) {	// runs for the size of half the stack to delete the previous stack
		deleteBack(s);						// removes the back of the stack up to half 
	}										// which contains the previous stack
}
// Returns a new graph object representing the transpose of G
Graph transpose(Graph G) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling transpose() on a NULL Graph reference");
		exit(1);
	}
	Graph newTranspose = newGraph(getOrder(G));		// create a new graph with the same vertex size
	for (int i = 1; i <= getOrder(G); i++) {				// runs for the number of vertices in the graph
		moveFront(G->adjMatrix[i]);							// start at the front of the list for the current vertex
		while (index(G->adjMatrix[i]) != -1) {				// runs until the end of the list for the current vertex
			addArc(newTranspose, get(G->adjMatrix[i]), i);	// add to the new graph the tranpose direction 
			moveNext(G->adjMatrix[i]);						// go to the next value on the list
		}
	}
	return newTranspose;					// return the newGraph
}
// Returns a new graph which is a copy of G
Graph copyGraph(Graph G) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling copyGraph() on a NULL Graph reference");
		exit(1);
	}
	Graph graphClone = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++) {
		moveFront(G->adjMatrix[i]);
		while (index(G->adjMatrix[i]) != -1) {
			addArc(graphClone, i, get(G->adjMatrix[i]));
			moveNext(G->adjMatrix[i]);
		}
	}
	return graphClone;
}
// Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE * out, Graph G) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling printGraph() on a NULL Graph reference");
		exit(1);
	}
	if (out == NULL) {		// making sure the out exist
		printf("Graph Error: calling printGraph() on a NULL out reference");
		exit(1);
	}
	for (int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);			// prints out the current vector index of the array
		printList(out, G->adjMatrix[i]);	// prints out the list of the vector index
		fprintf(out, "\n");					// prints out a newline for formating
	}
}