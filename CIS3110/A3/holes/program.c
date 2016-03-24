#include "QueueInterface.h"
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>


static void showQueueSize (Queue *L) {
	if(Empty(L)) printf("Queue is empty; ");
	else printf("Queue is not empty; ");
	if(Full(L)) printf("queue is full; ");
	else printf("queue is not full; ");
	printf("queue is of size %d:\n",Size(L));
}
	
	
static void showQueueContent (Queue *L) {
	int i;
	Process S;
	for(i=Size(L);i>0;i--) {
		Head(L,&S);
		printf("\t%s %d%%\n",idofProcess(S),sizeofProcess(S));
		Dequeue(L);
		Enqueue(S,L);
		FreeProcess(&S);
	}
}



int main(int argc, char const *argv[])
{
	printf("hello\n");
	return 0;
}