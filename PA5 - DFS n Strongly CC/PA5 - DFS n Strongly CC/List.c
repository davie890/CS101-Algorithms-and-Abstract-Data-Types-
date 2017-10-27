/**
* Davie Truong
* dtruong8@ucsc.edu
* 1/21/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 2 - List ADT File in C
*/

// A list ADT Implementation File 
// Contains struct and function definitions

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// Structure for the NodeObj 
typedef struct NodeObj {
	int data;
	struct NodeObj * next;
	struct NodeObj * prev;
} NodeObj;
// Refrence type Node
typedef NodeObj * Node;
// Constructor For a Node
Node newNode(int data, Node prev, Node next) {	// accepts data
	Node N = malloc(sizeof(NodeObj));			// declares new Node
	N->data = data;		// sets data
	N->next = next;		// sets next pointer
	N->prev = prev;		// sets previous pointer
	return(N);			// returns the node
}
// Destructor For a Node
void freeNode(Node * pN) {	// *pN : the address of a Node reference
	if (pN != NULL && *pN != NULL) {// checks if the pointer and the address of the pointer is null
		// Free all heap memory associated with *pN
		free(*pN);	// Frees the memory back to the allocator
					//		so that it can be used again
		*pN = NULL;	// sets the address of the pointer to null
	}				
}

// Structure for the ListObj
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;
// Constructor for List
List newList(void) {
	List L = malloc(sizeof(ListObj));		// declares a new list
	L->front = L->back = L->cursor = NULL;	// sets the front,back, and cursor to pointers to null
	L->length = 0;		// length of the list is empty
	L->index = -1;		// since there is no node the index fell off the list
	return(L);			// returns the list
}
// Destructor for List
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {//checks if the addresss of the pointer and the pointer is null
		Node nextNode = (*pL)->front;	// assigns the front Node to the nextNode node for deletion
		
		while (nextNode != NULL) {		// runs until the nextNode is null which means the list is empty
			Node current = nextNode;	// current node is assign nextNode
			nextNode = nextNode->next;	// updates the nextNode before deletion
			free(current);				// frees the memory of current node
		}
		free(*pL);			// frees the memory of the address of the list
		*pL = NULL;			// sets the addresss of the pointer to null
	}
}

// Access Functions
// Returns the number of nodes in the list
int length(List L) {
	if (L == NULL) {	// making sure the list exist
		printf("List Error: calling length on NULL List reference");
		exit(1);
	}
	return L->length;	// returns the length of the desired list
}
// Returns the index of the cursor element (PreCond: the cursor is defined) -1 otherwise
int index(List L) {
	if (L == NULL) {	// making sure the list exist
		printf("List Error: calling index on NULL List reference");
		exit(1);
	}
	if (L->cursor != NULL) {	// the cursor is pointing to something
		return L->index;		// returns the cursor of the desired list
	}
	else {
		return -1;
	}
}
// Returns the front element (Front Node data) (PreCond: length()> 0)
int front(List L) {
	if (L == NULL) {	// making sure the list exist
		printf("List Error: calling front on NULL List reference");
		exit(1);
	}
	if (L->length <= 0) {	// making sure there are nodes in the list
		printf("List Error: calling front on empty List");
		exit(1);
	}
	return L->front->data;	// returns the data of the front node of the list
}
// Returns the back element (Back Node data) (PreCond: length()> 0)
int back(List L) {
	if (L == NULL) {	// making sure the list exist
		printf("List Error: calling back on NULL List reference");
		exit(1);
	}
	if (L->length <= 0) {	// making sure there are nodes in the list
		printf("List Error: calling back on empty List");
		exit(1);
	}
	return L->back->data;	// returns the data of the back node of the list
}
// Returns the Cursor Element (Cursor Node data) (PreCond: Length() > 0, index() >=0)
int get(List L) {
	if (L == NULL) {	// making sure the list exist
		printf("List Error: calling get on NULL List reference");
		exit(1);
	}
	if (L->length <= 0) {	// making sure there are nodes in the list
		printf("List Error: calling get on empty List");
		exit(1);
	}
	if (L->index < 0) {		// making sure the cursor is pointing a node on the list
		printf("List Error: calling get on improper List index");
		exit(1);
	}
	return L->cursor->data;		// returns the data of the node that the cursor is at
}
// Returns true (PreCond: the List and userInput L are the same Integer Sequence)
// The cursor is ignored in both lists
int equals(List L, List input) {
	if (L == NULL || input == NULL) {	// making sure both list exist
		printf("List Error: calling equals on NULL List reference");
		exit(1);
	}
	if (L->length != input->length) {	// check to see if the are the same size
		return 0;
	}
	Node clientFront = input->front;	// makes a new node that has the same data as the input's front
	Node thisFront = L->front;		// makes a new node that has the same data as L's front
	while (clientFront->next != NULL && thisFront->next != NULL) {
		if (clientFront->data != thisFront->data) {
			return 0;
		}
		clientFront = clientFront->next;
		thisFront = thisFront->next;
	}
	return 1;
}

// Manipulation Procedures
// Resets The list to its original empty State
void clear(List L) {
	if (L == NULL) {	// Making Sure both list exist
		printf("List Error: calling clear on NULL List reference");
		exit(1);
	}
	Node nextNode = (L)->front;	// assigns the front Node to the nextNode node for deletion
	while (nextNode != NULL) {		// runs until the nextNode is null which means the list is empty
		Node current = nextNode;	// makes new current node and assigns it nextNode
		nextNode = current->next;	// updates the nextNode before deletion
		free(current);				// frees the memory of current node
	}
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}
// Places the cursor under the front element (PreCond: the list is not empty), if it is empty do nothing
void moveFront(List L) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling moveFront on NULL List reference");
		exit(1);
	}
	if (L->length >= 1) {		// checks that the list is not empty
		L->cursor = L->front;	// assigns the cursor to the front node
		L->index = 0;			// index gets updates to 0
	}
}
// Places the cursor under the back element (PreCond: the list is not empty), if it is empty do nothing
void moveBack(List L) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling moveBack on NULL List reference");
		exit(1);
	}
	if (L->length >= 1) {			// checks that the list is not empty
		L->cursor = L->back;		// assigns the cursor to the back node
		L->index = L->length -1;	// the index gets assigned to the last index of the list
	}
}
// Moves cursor one step towards front of the list when (PreCond: Cursor is defined and not at front)
// Cursor becomes undefined (PreCond: cursor is defined and at the front of the list)
// Do nothing (PreCond: cursor is undefined)
void movePrev(List L) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling movePrev on NULL List reference");
		exit(1);
	}
	if (L->cursor != NULL && L->index != 0) {	// if the cursor is point to a node and not the front
		L->cursor = L->cursor->prev;	// cursor gets assigned the node before it
		L->index -= 1;					// the index gets deducted by 1
	}
	else if (L->cursor != NULL && L->index == 0) {	// if the cursor is pointed to a node but at the front
		L->cursor = NULL;		// cursor gets assigned null because it fell of the list
		L->index -= 1;			// the index gets deducted by 1
	}
}
// Moves cursor one step towards back of the list (PreCond: cursor is defined and not at back)
// Cursor becomes undefined (PreCond: if cursor is defined and at the back)
// Do nothing (PreCond: cursor is undefined)
void moveNext(List L) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling moveNext on NULL List reference");
		exit(1);
	}
	if (L->cursor != NULL && L->index != L->length - 1) {	// if the cursor points to a node and the index is not
		L->cursor = L->cursor->next;						// at the back of the list
		L->index += 1;		// cursor gets assigned the next node and the index gets increased
	}
	else if (L->cursor != NULL && L->index == L->length - 1) { // if the cursor points to a node but is the last node
		L->cursor = NULL;	// curosr gets assigned null because it fell of the list
		L->index = -1;		// index gets assigned -1 for not being on the list
	}
}
// Insert new element into list. If list is not empty insertion takes place before front node
void prepend(List L, int data) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling prepend on NULL List reference");
		exit(1);
	}
	Node inputNode = newNode(data, NULL, L->front); // Creates node with user data and assigns front to null or
	if (L->front == NULL) { // if list is empty     // current front depending if list is empty or not
		L->back = inputNode;    // the new node is now the back
	}
	else {                  // if the list is not empty
		L->front->prev = inputNode;  // the prev pointer of the front node now points toward newNode
	}
	L->front = inputNode;   // front is assigned newNode no matter the situation
	L->length += 1;
	if (L->index != -1) {
		L->index += 1;			// increment the index since adding to the front of the list shifts all nodes by 1
	}
}
// Insert new Node into list. If the list is not empty insertion take places after back node
void append(List L, int data) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling append on NULL List reference");
		exit(1);
	}
	Node inputNode = newNode(data, L->back, NULL);	// assigns prev to L's back node and next to null because appending
	if (L->front == NULL) {	// if the list is empty
		L->front = inputNode;	// the list's front is now pointing to inputNode
	}
	else {
		L->back->next = inputNode; // updates the previous last node's next pointer new inputNode
	}
	L->back = inputNode;	// updates the list's back pointer
	L->length += 1;			// increment the length of the list by 1
}
// Insert new Node before cursor (PreCond: length() > 0, index() >= 0)
void insertBefore(List L, int data) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling insertBefore on NULL List reference");
		exit(1);
	}
	if (L->length <= 0) {	// Making sure the list is not empty to insert before
		printf("List Error: unable to insert an empty list");
		exit(1);
	}
	if (L->index < 0) {		// Making sure the cursor is at an appropriate node
		printf("List Error: Index out of bounds");
		exit(1);
	}
	Node insertNode = newNode(data, L->cursor->prev, L->cursor);	// makes new node with pre set pointers
	if (L->cursor->prev != NULL) {	// if there is a node before the cursor
		L->cursor->prev->next = insertNode;	// update the old pointer that used to point at cursor to the 
	}										// new insertNode
	else {	// if the cursor is at index 0
		L->front = insertNode;	// the new node is now at the front
	}
	L->cursor->prev = insertNode;	// update the cursor's previous pointer to point at the insertNode
	L->length += 1;	// increment the length of the list by 1
	L->index += 1; // since the insertion is before, t

}
// Insert new Node After cursor (PreCond: length() > 0, index() >= 0)
void insertAfter(List L, int data) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling insertAfter on NULL List reference");
		exit(1);
	}
	if (L->length <= 0) {	// Making sure the list is not empty to insert before
		printf("List Error: unable to insert an empty list");
		exit(1);
	}
	if (L->index < 0) {		// Making sure the cursor is at an appropriate node
		printf("List Error: Index out of bounds");
		exit(1);
	}
	Node insertNode = newNode(data, L->cursor, L->cursor->next);// makes new node with pre set pointers
	if (L->cursor->next != NULL) {	// if the insertNode is being inserted between 2 nodes
		L->cursor->next->prev = insertNode;	// updates the pointer of the node to the right of cursor
	}										// to now point its prev to the new insertNode
	else {	// the insertion is taking place at the back of the list
		L->back = insertNode;	// the list's back is now the new insertNode
	}
	L->cursor->next = insertNode;	// cursor's next pointer now points to new insertNode
	L->length += 1; // increment the length of the list by 1
}
// Deletes the front element (PreCond: length() > 0)
void deleteFront(List L) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling insertAfter on NULL List reference");
		exit(1);
	}
	if (L->length <= 0) {	// Making sure the list is not empty to insert before
		printf("List Error: unable to insert an empty list");
		exit(1);
	}
	if (L->length == 1) {  // When there is only 1 element in the list
		Node clearNode = L->front;
		L->front = L->back = L->cursor = NULL;	// all the List's data gets reset
		L->length -= 1;	// this makes the length 0
		L->index = -1;	// the index is now off the list
		freeNode(&clearNode);
	}
	else {				// When there is more than 1 element in the list
		Node clearNode = L->front; // stores the front node before it gets updates so it can be deleted
		L->front = L->front->next;	// updates the new front to point towards the prev front Node's next
		L->front->prev = NULL;	// the new front's prev now points to null
		L->length -= 1;	// the length gets decremented
		if (L->index != -1) {
			L->index -= 1;	// the index gets shifted to the left by 1
		}
		freeNode(&clearNode);	// the front node gets cleared from memory
	}
}
// Delete the back element (PreCond: length() > 0)
void deleteBack(List L) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling insertAfter on NULL List reference");
		exit(1);
	}
	if (L->length <= 0) {	// Making sure the list is not empty to insert before
		printf("List Error: unable to insert an empty list");
		exit(1);
	}
	if (L->length == 1) {  // When there is only 1 element in the list
		Node clearNode = L->back;
		L->back = L->front = L->cursor = NULL;	// all the List's data gets reset
		L->length -= 1;		// this makes the length 0
		L->index = -1;		// the index is now off the list
		freeNode(&clearNode);
	}
	else {
		if (L->cursor == L->back) {// if the cursor is the back index
			L->index = -1;			// we set index -1, because its not pointing at anything anymore
		}
		Node clearNode = L->back;	// stores the back node before it gets updated so it can be deleted
		L->back = L->back->prev;	// the new back is the current back's previous node
		L->back->next = NULL;		// now that back is updates it now points to null
		L->length -= 1;				// the length gets decrement 
		freeNode(&clearNode);		// the back node gets cleared from memory
	}
}
// Deletes Cursor element, making cursor undefined (PreCond: length() > 0, index() >= 0)
void delete(List L) {
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling insertAfter on NULL List reference");
		exit(1);
	}
	if (L->length <= 0) {	// Making sure the list is not empty to insert before
		printf("List Error: unable to insert an empty list");
		exit(1);
	}
	if (L->index < 0) {		// Making sure the cursor is at an appropriate node
		printf("List Error: Index out of bounds");
		exit(1);
	}
	if (L->cursor == L->front) {  // if the cursor is at the front element
		deleteFront(L);		// calls the deleteFront Function
	}
	else if (L->cursor == L->back) {     // if the cursor is at the back
		deleteBack(L);		// calls the deleteBack function
	}
	else {                                 // if the cursor is in between 2 elements
		Node clearNode = L->cursor;	// saves the node so it can be delete after fixing pointers
		L->cursor->prev->next = L->cursor->next;   // reassign pointers and updates the list data
		L->cursor->next->prev = L->cursor->prev;
		L->cursor = NULL;		// makes the cursor null
		L->index = -1;			// removes the index from the list since there is no longer a cursor
		L->length -= 1;			// length gets decremented
		freeNode(&clearNode);	// clear the cursor node from memory
	}

}

// Other Methods
// Prints the data elements in L on a single line to STDOUT
void printList(FILE * out, List L) {
	Node N = NULL;
	if (L == NULL) {	// Making sure both list exist
		printf("List Error: calling insertAfter on NULL List reference");
		exit(1);
	}
	for (N = L->front; N != NULL; N = N->next) {// itterates through the list until the end
		fprintf(out, "%d ", N->data);		// prints the data of the current node
	}
}
// Returns a new List representing the same integer sequence as this list
// The cursor in the new list is undefined, regardless of the state of the cursor in this list
// this list is unchanged
List copyList(List L) {
	List copiedList = newList();	// creates a new list
	Node CurrentNode = L->front;	// creates a new node and stores the front node of the list onto it
	while (CurrentNode != NULL) {				// runs until the end of the list
		append(copiedList, CurrentNode->data);	// appends the data of the current node to the new list
		CurrentNode = CurrentNode->next;		// itterates the currentNode 
	}
	return copiedList;		// the new copied list gets returned
}
// Returns a new List which is the concatenation of this list followed by L.
// The cursor in the new List is undefined, regardless of the state of the Cursors
// in this list and L. The states of this list and l are unchanged.
List concatList(List L, List input) {
	List bothList = copyList(L);    // copies this(first List) into new array
	Node CurrentNode = input->front;			// stores the front node of the input list into a new node
	while (CurrentNode != NULL) {				// loops until the end if the input list
		append(bothList, CurrentNode->data);	// appends the currentNode's data to the newList 
		CurrentNode = CurrentNode->next;		// itterates the currentNode
	}
	return bothList;	// Returns the new list that has all the nodes of both lists
}