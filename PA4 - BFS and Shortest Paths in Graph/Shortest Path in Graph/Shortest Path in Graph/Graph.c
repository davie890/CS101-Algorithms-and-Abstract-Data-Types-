/**
* Davie Truong
* dtruong8@ucsc.edu
* 2/21/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 4 - Graph implementation File
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
	int * distance;		// array of ints whose i elem is the distance from most recent source to vertex i
	int order;			// number of vertices of the graph
	int size;			// number of edges
	int recentSource;	// label of the vertex that was most recently used as a source for BFS
} GraphObj;
// Constructor For a Graph
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->adjMatrix = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->parent = calloc(n + 1, sizeof(int));
	G->distance = calloc(n + 1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->recentSource = NIL;				// No source because BFS() hasn't ran 

	// initialize the arrays
	for (int i = 1; i <= n; i++) {		// runs for the number of verices in the graph
		G->adjMatrix[i] = newList();	// initializes each row of the array with lists
		G->color[i] = WHITE;			// white for each vertex index
		G->parent[i] = NIL;				// NIL for each index because BFS() hasn't ran 
		G->distance[i] = INF;			// INF for each vertex index because BFS() hasn't ran 
	}
	return G;			// returns a graph pointing to a newly created GraphObj
}
// Destructor for Graph objected
void freeGraph(Graph * pG) {			// *pG : the address of a Graph reference
	if (pG != NULL && *pG != NULL) {			// pointer and the address of the pointer is not null
		free((*pG)->color);						// free the color array
		free((*pG)->parent);					// free the parent array
		free((*pG)->distance);					// free the distance array
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
// Returns the Recent Source Value (label of the vertex that was last used)
int getSource(Graph G) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling getSource() on a NULL Graph reference");
		exit(1);
	}
	return G->recentSource;	// returns source vertex most recently used in BFS()
}
// Returns the parent of vertex u in the BFS tree created by BFS
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
// Returns the distance from the most recent BFS source to vertex u 
int getDist(Graph G, int u) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling getDist() on a NULL Graph reference");
		exit(1);
	}
	if (u < 1 || G->order < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling getDist() with an incorrect vertex");
		exit(1);
	}
	return G->distance[u]; // returns the disance of the BFS source to the given vertex u
}
// appends to the List L the verticies of a shortest path in G from source to u 
// gets the path by working backwords from u to source using the parent as a guide 
void getPath(List L, Graph G, int u) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling getPath() on a NULL Graph reference");
		exit(1);
	}
	if (u < 1 || G->order < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling getPath() with an incorrect vertex");
		exit(1);
	}
	if (G->recentSource == NIL) {			// making sure BFS was used so that a path exist
		printf("Graph Error: calling getPath() before the BFS was ran, no current path Exist");
		exit(1);
	}
	if (u == G->recentSource) {			// when the source is the same as the vertex 
		append(L, G->recentSource);		// put it at the end of the list 
	}									// happens when at the top of the tree
	else if (G->parent[u] == NIL) {		// a parent doesn't exist meaning no such path exist
		append(L, INF);					// appends INF to the list, 
	}									
	else {
		getPath(L, G, G->parent[u]);	// getPath with the parent of the current vertex as the new u
										// keeps running until we hit the source 
		append(L, u);					// appends current vertex to list
	}
}

// Manipulation Procedures
// Deletes all edges of G, restoring it to its original no edge state
void makeNull(Graph G) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling makeNull() on a NULL Graph reference");
		exit(1);
	}
	for (int i = 1; i <= G->order; i++) {	// runs for the number of verticies in the graph
		clear(G->adjMatrix[i]);				// clears the edge list for all vertexes in the adjMatrix
	}
	G->size = 0;							// sets the number of edges in the graph to 0
	G->recentSource = NIL;					// set the source to Nil because there is no longer a source to keep
}
// Inserts a new edge joining u to v 
//(u is added to the adjaceny list of v, and v to the adjaceny list of u)
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling addEdge() on a NULL Graph reference");
		exit(1);
	}
	if (u < 1 || G->order < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling addEdge() with an incorrect vertex");
		exit(1);
	}
	if (v < 1 || G->order < v) {		// making sure the user enters a vetex that exist
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
	if (u < 1 || G->order < u) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling addArc() with an incorrect vertex");
		exit(1);
	}
	if (v < 1 || G->order < v) {		// making sure the user enters a vetex that exist
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
// Runs the BFS algorithm on the Graph G 
// with sources s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s) {
	if (G == NULL) {		// making sure the Graph exist
		printf("Graph Error: calling BFS() on a NULL Graph reference");
		exit(1);
	}
	if (s < 1 || G->order < s) {		// making sure the user enters a vetex that exist
		printf("Graph Error: calling BFS() with an incorrect source");
		exit(1);
	}
	for (int i = 1; i <= G->order; i++) {	// runs for the number of vertexes 
		G->parent[i] = NIL;			// resets the array of the BFS data to make sure everything is 
		G->distance[i] = INF;		// correct before setting the data 
		G->color[i] = WHITE;
	}
	G->recentSource = s;			// source gets updates to user value
	G->distance[s] = 0;				// distace to itself is 0
	G->color[s] = GREY;				// since we traversed it once
	List Q = newList();				// use list as a queue for the BFS
	append(Q, s);					// adds the top of the list to the queue to start the BFS 
	while (length(Q) != 0) {		// runs until the QUEUE is empty
		int parent = front(Q);			// stores the data of the front entry of the queue into x
		deleteFront(Q);				// removes the value of the front of the queue
		moveFront(G->adjMatrix[parent]);	// start at the front of the list for given vector in array
		while (index(G->adjMatrix[parent]) != -1) {	// runs until no more connected edges
			int child = get(G->adjMatrix[parent]);	//assigns the current data in the list, which is a connected vertex
			if ((G->color[child]) == WHITE) {			// checks to see if the neighboring vectors had been discovered
				G->color[child] = GREY;				// sets the current vector to discovered
				G->distance[child] = ((G->distance[parent]) + 1); // assigns the distance of its parents + 1
				G->parent[child] = parent;			// gives the vector a parent to know where its position in the tree
				append(Q, child);					// adds to the queue so that it can see the child of this current vector
			}
			moveNext(G->adjMatrix[parent]);			// moves the cursor to go to the next vecor connected to the current source
		}
		G->color[parent] = BLACK;	// to signify that we are finished with the vector 			
	}
	freeList(&Q); 					// frees the memory of the Q list
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