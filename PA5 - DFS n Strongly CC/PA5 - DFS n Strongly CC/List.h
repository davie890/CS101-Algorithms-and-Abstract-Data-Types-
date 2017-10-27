/**
* Davie Truong
* dtruong8@ucsc.edu
* 1/21/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 2 - List ADT File  Header in C
*/

// A list ADT Header File
// Used to typedefs and prototype exported functions


#pragma once

typedef struct ListObj * List;

// Constructor-Destructor
List newList(void);
void freeList(List * pL);

// Access Functions 
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);

// Manipulation Procedures
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other Operations
void printList(FILE* out, List L);
List copyList(List L);
List concatList(List A, List B);