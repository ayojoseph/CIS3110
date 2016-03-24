#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      /* Symbolic Constants */
#include <sys/types.h>   /* Primitive System Data Types */
#include <sys/wait.h>    /* Wait for Process Termination */
#include <errno.h>       /* Errors */
#include <string.h>     /* Strings */
#include <pthread.h>     /* pthreads library */
#include <sys/queue.h>   /* queues library */


typedef struct Thread Thread;
typedef struct Thread {
	int num;
	int aTime;
	int bursts;
	int cpuTime;
	int ioTime;
	int last; //check if it's last thread

	
} Thread;

typedef struct Process Process;
typedef struct Process {
	// pid_t pid;
	int id;
	int threadNum;
	int start;
	int end;
	Thread threads[];


} Process;

char **readFile(int *num);
Process * createProcess(char **lines, int start, int end);
Process createLastProcess(char **lines, int start);
int addupCPU(Process *pro);