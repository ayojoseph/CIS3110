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
		printf("ID: %c SIZE: %d\n",idofProcess(S),sizeofProcess(S));
		Dequeue(L);
		Enqueue(S,L);
		FreeProcess(&S);
	}
}

// Queue waitQu;

char memory[128];
int freeMem;
int holes[];
int holeNum;
int inMem;
int off;
float memUsage;
double memCum;
int tot;

int main(int argc, char const *argv[])
{
	Process P[1000];
	Process temp;
	Queue Q;
	Initialize(&Q);
	Queue waitQu;
	int size;
	char id;
	char nl;
	FILE *fp;
	

	fp = fopen(argv[1],"r");
	int i,j;
	i = 0;
	j = 0;
	off = 0;
	tot = 0;

	for (int k = 0; k < 128; ++k)
	{
		memory[k] = '*';
	}

	while(1) {
		if ( fscanf(fp, "%c %d", &id, &size) != EOF )
		{
			P[i].size = size;
			P[i].id = id;
			i++;
			fscanf(fp,"%c",&nl);
		} else {
			break;
			// printf("finir\n");
		}

	}

	//putting all processes in wait Queue
	Initialize(&waitQu);	
	while(j < i) {
		Enqueue(P[j],&waitQu);
		j++;
	}
	//set free space
	freeMem = 128;
	//send in the first process
	Head(&waitQu,&temp);
	Enqueue(temp,&Q);
	Dequeue(&waitQu);
	addtoMem(temp,off);
	freeMem = freeMem - temp.size;
	off = off + temp.size;

	while(!Empty(&waitQu)) {
		Head(&waitQu,&temp);
		if (freeMem < temp.size) {
			Head(&Q,&temp);
			freeMem = freeMem + temp.size;
			Dequeue(&Q);
			off = off - temp.size;
			inMem = inMem - 1;
			continue;
		} else {
			Enqueue(temp,&Q);
			Dequeue(&waitQu);
			addtoMem(temp,off);
			freeMem = freeMem - temp.size;
			off = off + temp.size;

		}

	}
	// showQueueContent(&waitQu);
	// showQueueContent(&Q);

	// addtoMem(P[5],0);
	printMemory();

	// printf("done %d\n",Size(&waitQu) );

	return 0;
}

void addtoMem(Process P, int place) {
	inMem++;
	int m;
	m = memstatus();
	static int use = 0;
	for (int i = 0; i < P.size+1; ++i)
	{
		memory[place + i] = P.id;
	}

	memUsage = 128 - freeMem;
	memUsage = (memUsage / 128) * 100;
	tot = tot + memUsage;
	use++;
	memCum = tot/use;
	holeNum = 1;
	// printf("%.2lf\n",memUsage);
	

	printf("pid loaded, #processes: %d, #holes: %d, %%memusage: %.2lf%%, cumulative %%mem = %.2lf%%\n",inMem, holeNum, memUsage,memCum  );
}

void printMemory() {

	printf("\n Printing mem Map. ' * ' indicate free memory. \n\n");
	for (int i = 0; i < 128; ++i)
	{
		if (i % 16 == 0)
		{
			printf("\n");
		} else {
			printf("%c",memory[i] );
		}
	}
	printf("\n");
}

int memstatus() {

	int tr = 0;

	for (int i = 0; i < 128; ++i)
	{
		if (memory[i] != '*')
		{
			tr++;
			// printf("hit\n");
		}
	}

	return tr;
}