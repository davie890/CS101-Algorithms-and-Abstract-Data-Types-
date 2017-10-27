#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Test.h"
int main(int argc, char* argv[]) {
	FILE* out = stdout;
	/*out = fopen("Test_Append.out", "w");
	if( out==NULL ){
	printf("Unable to write to file\n");
	exit(EXIT_FAILURE);
	}
	*/
	List a = newList();
	for (int i = 0; i < 5; i++) {
		append(a, i);
	}
	printList(out, a);// 0 1 2 3 4
	moveFront(a);
	while (index(a)>-1) {
		fprintf(out, "%d ", get(a)); //0 1 2 3 4
		moveNext(a);
	}
	fprintf(out, "\n");

	moveBack(a);
	while (index(a)>-1) {
		fprintf(out, "%d ", get(a)); //4 3 2 1 0
		movePrev(a);
	}
	fprintf(out, "\n");

	List b = newList();
	for (int i = 0; i < 5; i++) {
		prepend(b, i);
	}
	printList(out, b);// 4 3 2 1 0
	moveFront(b);
	while (index(b)>-1) {
		fprintf(out, "%d ", get(b));//4 3 2 1 0
		moveNext(b);
	}
	fprintf(out, "\n");

	moveBack(b);
	while (index(b)>-1) {
		fprintf(out, "%d ", get(b));//0 1 2 3 4
		movePrev(b);
	}

	fclose(out);
	freeList(&a);
	freeList(&b);
	//return 0;
}