/**
* Davie Truong
* dtruong8@ucsc.edu
* 1/22/2017
* CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
* Programming Assignment 2 - Lex Implementation file in C
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#define MAX_LEN 160


int main(int argc, char* argv[]) {

	int lineCount = 0;
	FILE *in, *out;
	char wordString[MAX_LEN];

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

	// Data Gathering Part of Lex
	// read each line of input file to get the count
	while (fgets(wordString, MAX_LEN, in) != NULL) {
		lineCount++;
	}

	//char wordArray[lineCount][MAX_LEN];	// makes the array to store the word
	char wordArray[20][MAX_LEN];	// makes the array to store the word
	rewind(in);							// start at the beginning of the input file
	int i = 0;							// used to iterate the array
	// this loop stores the words from the file into the array 
	while (fgets(wordString, MAX_LEN, in) != NULL) {
		strcpy(wordArray[i], wordString);
		i++;
	}
	fclose(in);							// close the input file

	// Sorting Part of Lex
	List intList = newList();			// Creates an empty List
	append(intList, 0);					// append the first word/int to the list so there is a starting point
	for (i = 1; i < lineCount; i++) {
		moveFront(intList);				// sets the cursor at the front of the list
		int completeInsertion = 0;			// used as a loop control to determne if the index gets added
		while (completeInsertion == 0) {		// if the insertion has not been made
			if (index(intList) < 0) {			// checks to see if the cursor fell of the list
				append(intList, i);				// if the cursor fell of the list it means the data is greatest value of list 
				completeInsertion = 1;			// set loop control to true so it can exit out and start next data
			}
			else if (strcmp(wordArray[get(intList)], wordArray[i]) > 0) {	// checks to see if the data is less than current
				insertBefore(intList, i);	// insert before because the data is less than current index data
				completeInsertion = 1;		// set loop control to true so it can exit and start on next data
			}
			else {
				moveNext(intList);	// moves the index next because the data is greater so can't insert before
			}
		}
	}

	// Storing the sorted words into an output list
	moveFront(intList);
	for (i = 0; i < lineCount; i++) {
		fprintf(out, "%s" ,wordArray[get(intList)]);
		moveNext(intList);
	}
	freeList(&intList);	// frees the list from memory
	fclose(out);		// closes the output file

	return (0);
}