/**
* Davie Truong
* dtruong8@ucsc.edu
* 3/7/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 5 - Graph ADT File Header in C
*/

#pragma once

#include<stdio.h>
#include "List.h"

#define WHITE 1
#define GREY 2
#define BLACK 3
#define NIL -2
#define UNDEF -1

typedef struct GraphObj * Graph;

// Constructor-Destructor
Graph newGraph(int n);
void freeGraph(Graph * pG);

// Access Functions
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

// Manipulation Procedures
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List s);

// Other Functions 
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE * out, Graph G);