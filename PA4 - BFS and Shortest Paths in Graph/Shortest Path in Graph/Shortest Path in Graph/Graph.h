/**
* Davie Truong
* dtruong8@ucsc.edu
* 2/21/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 4 - Graph ADT File Header in C
*/

#pragma once

#include<stdio.h>
#include "List.h"

#define INF -1		// represents Infinity
#define NIL -2		// represents undefined Vertex Label
#define WHITE 1
#define GREY 2
#define BLACK 3

typedef struct GraphObj * Graph;

// Constructor-Destructor
Graph newGraph(int n);
void freeGraph(Graph * pG);

// Access Functions
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulation Procedures
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other Operations 
void printGraph(FILE * out, Graph G);