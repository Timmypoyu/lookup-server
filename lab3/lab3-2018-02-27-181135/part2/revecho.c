#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.h"

static void printString(void *p){
	printf("%s\n", (char *)p);
}

int main(int argc, char **argv){
	argv++;

	//Initializing the list
	struct List list;
	initList(&list); 

	while(*argv){
		addFront(&list, (void *)*argv);
		argv++; 
	}	

	traverseList(&list, &printString);
	printf("\n");
	char *sought = "dude"; 
	if(findNode(&list,(void *)sought,
		(int (*)(const void *,const void *))strcmp)!=0){
		printf("dude found\n");
	}else{
		printf("dude not found\n");
	}
	
	removeAllNodes(&list);

}
