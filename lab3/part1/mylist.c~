#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include "mylist.h"

//addFront
struct Node *addFront(struct List *list, void *data){
	struct Node *node = malloc(sizeof(struct Node));
       	node->next = list->head;
	node->data = data; 
	list->head = node; 
	return node;
}

//traverseList
void traverseList(struct List *list, void (*f)(void *)){
	struct Node *evaluate = list->head;
	while(evaluate){
		f(evaluate->data);
		evaluate = evaluate->next;	
	}
}

//findNode
struct Node *findNode(struct List *list, const void *dataSought,
		int (*compar)(const void *, const void *)){
	struct Node *evaluate = list->head;
	while(evaluate){
		int y = compar(evaluate->data, dataSought);
		if (y == 0){
			return evaluate;
		}	
		evaluate = evaluate->next;
	}
	evaluate = NULL; 
	return evaluate;
}

//compare method for findNode
int compareDouble(const void * a, const void * b){
	return (*(double*)a > *(double*)b) - (*(double*)b > *(double*)a);
}

//flip
void flipSignDouble(void *data){
	double flipped = *(double*)data;
	flipped *= -1; 
	*(double*)data = flipped;
}

//popfront
void *popFront(struct List *list){
	if(list->head == NULL){
		return NULL;
	}
	struct Node *here =list->head;
	void *re = (list->head)->data;
	list->head = (list->head)->next;
	free(here);
	return re;
}

//remove
void removeAllNodes(struct List *list){
	struct Node *evaluate = list->head;
	while(evaluate){
		evaluate = evaluate->next;
		popFront(list);
	}
}

//addAfter 
struct Node *addAfter(struct List*list, struct Node *prevNode, void *data){
	struct Node *add;
	if(prevNode){
		add = malloc(sizeof(struct Node));
		add->data = data; 
		add->next = prevNode->next;
		prevNode->next= add;
		return add;
	}else if(prevNode == NULL){
		add = addFront(list, data);
	}	
	return add;
}

//Reverse
void reverseList(struct List *list){
	struct Node *prv = NULL;
	struct Node *cur = list->head;
	struct Node *nxt;

	/*	prv->next = cur;
	while (cur){
		cur->next = nxt->next;
		nxt->next = list->head;
		list->head= nxt;
		nxt = cur->next;	
	}
	*/

	while(cur){
		nxt = cur->next;
		cur->next = prv;
		prv = cur;
		cur = nxt;
	}
	list->head = prv;
}

