#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 




//mutex for threads
pthread_mutex_t lock[1000];
int philNum;
int eatNum;


void * execute(int args[]) {
	int cur = 0; 
	cur = args[0];
	int prev;
	int eat = 0;
	// printf("THREAD: %d\n",cur );
	if (cur < 1) {

		prev = philNum -1;
	} else {
		prev = cur -1;
	}

	while (eat < eatNum) {
		printf("philosopher %d is thinking...\n",cur + 1);

		//philsopher is ready to eat
		pthread_mutex_lock(&lock[cur]);
		pthread_mutex_lock(&lock[prev]);
		sleep(1);
		eat++;
		printf("philsopher %d eating\n", cur +1);
		pthread_mutex_unlock(&lock[cur]);
		pthread_mutex_unlock(&lock[prev]);

	}
	printf("philosopher %d is thinking...\n",cur + 1);
	// printf("LOCKING CUR: %d PREV: %d\n",cur,prev);
	// // pthread_mutex_lock(&lock[prev]);
	// // printf("%d   %d\n",args[0],args[1] );
	// sleep(1);
	// printf("UnLOCKING CUR: %d PREV: %d\n",cur,prev);
	// // pthread_mutex_unlock(&lock[cur]);
	// // pthread_mutex_unlock(&lock[prev]);
	// printf("UNLOCKEDTHREAD: %d\n",cur +1 );



	return NULL;
}

int main(int argc, char const *argv[])
{

	if ( (argc < 2) || (atoi(argv[1]) < 2))
	{
		printf("Please Enter a number of philosophers (greater than 2) and times to eat!\n");
		exit(0);
	}
	philNum = atoi(argv[1]);
	
	eatNum = atoi(argv[2]);
	int theadId[1000];
	pthread_t threads[1000];
	int args[2];
	int res;
	for (int i = 0; i < philNum; ++i)
	{
		if (i == 0)
		{
			
		}

		theadId[i] = i;
		args[0] = i;
		args[1] = eatNum;
		res = pthread_create( &(threads[i])	, NULL, &execute, &args );
		// printf("ARGS: %d\n",args[0] );
		// printf("\n");
		pthread_mutex_init(&lock[i],NULL);
		// res = pthread_join(threads[i],NULL);
					// printf("COMPLETE: %d\n",i );
		sleep(1);

	}
	// printf("%d :yyy\n", theadId[1]);

	for (int i = 0; i < philNum; ++i)
	{
		res = pthread_join(threads[i],NULL);
	}
		

	// printf("NUM: %d EAT: %d\n",philNum,eatNUm );

	return 0;
}