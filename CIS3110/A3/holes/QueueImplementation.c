/*********************************************************************
 * FILE NAME: QueueImplementation.c
 * PURPOSE: Circular array implementation of the Student Queue ADT.
 * AUTHOR: P. Matsakis (CIS2520 F15, Assignment 3 Part C)
 * DATE: 9/11/2015
 * NOTES: Here is how to modify the content of the file
 *        ListImplementation.c from Assignment 1 and get
 *        the content below:
 *        . Replace everywhere the word "List" with "Queue".
 *        . Rename Insert(), Remove() and Peek();
 *          call them Enqueue(), Dequeue() and Head(),
 *          and simplify them accordingly.
 *        . Copy/paste Head(), rename the copy Tail(),
 *          and modify it accordingly.
 *********************************************************************/


#include "QueueInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define DEBUG


static void copyItem (Item *Y, Item X) {
	InitProcess(idofProcess(X),sizeofProcess(X),Y);
}


static void destroyItem (Item *X) {
	FreeProcess(X);
}


void Initialize (Queue *L) {
	L->size=0;
	L->head=0;
#ifdef DEBUG
	if(!Empty(L) || Full(L) || Size(L)!=0) {
		printf("Violated postcondition for Initialize!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


/*==== THIS FUNCTION IS NEW (REWRITTEN FROM INSERT) ====*/
void Enqueue (Item X, Queue *L) {
#ifdef DEBUG
	int oldSize=Size(L);
	if(Full(L)) {
		printf("Violated precondition for Enqueue!\n");
		exit(EXIT_FAILURE);
	}
#endif
	copyItem(&L->items[(L->head+L->size)%MAXLISTSIZE],X);
	L->size++;	
#ifdef DEBUG
	if(Empty(L) || Size(L)!=oldSize+1) {
		printf("Violated postcondition for Enqueue!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


/*==== THIS FUNCTION IS NEW (REWRITTEN FROM REMOVE) ====*/
void Dequeue (Queue *L) {
#ifdef DEBUG
	int oldSize=Size(L);
	if(Empty(L)) {
		printf("Violated precondition for Dequeue!\n");
		exit(EXIT_FAILURE);
	}
#endif
	destroyItem(&L->items[L->head]);
	L->size--;
	L->head=(L->head+1)%MAXLISTSIZE;
#ifdef DEBUG
	if(Full(L) || Size(L)!=oldSize-1) {
		printf("Violated postcondition for Dequeue!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


int Full (Queue *L) {
	return L->size==MAXLISTSIZE;
}


int Empty (Queue *L) {
	return L->size==0;
}


int Size (Queue *L) {
	return L->size;
}


/*==== THIS FUNCTION IS NEW (REWRITTEN FROM PEEK) ====*/
void Head (Queue *L, Item *X) {
#ifdef DEBUG
	if(Empty(L)) {
		printf("Violated precondition for Head!\n");
		exit(EXIT_FAILURE);
	}
#endif
	copyItem(X,L->items[L->head]);
}


/*==== THIS FUNCTION IS NEW (REWRITTEN FROM PEEK) ====*/
void Tail (Queue *L, Item *X) {
#ifdef DEBUG
	if(Empty(L)) {
		printf("Violated precondition for Tail!\n");
		exit(EXIT_FAILURE);
	}
#endif
	copyItem(X,L->items[(L->head+L->size-1)%MAXLISTSIZE]);
}


void Destroy (Queue *L) {
	int i;
	for(i=0;i<L->size;i++)
		destroyItem(&L->items[i]);
}

