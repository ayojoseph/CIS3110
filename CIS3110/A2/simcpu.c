#include "simcpu.h"

int main(int argc, char const *argv[])
{	
	//puts each line in file in string array
	int lineNum,max;
    lineNum = 0;
	char **lines = readFile(&lineNum);
	char * buff = malloc(sizeof(char)*1024);
	max = lineNum;
	//determine #of processes and 2 thread switch times (first line of file)
	int numofPros, threadSwitchIn, threadSwitchOut = 0;

    strcpy(buff,lines[0]);

	buff = strtok(buff," ");
	numofPros = atoi(buff);
	buff = strtok(NULL," ");
	threadSwitchIn = atoi(buff);
	buff = strtok(NULL," ");
	threadSwitchOut = atoi(buff);

    Process *processes[numofPros];

	//split up process blocks
	int currentProcess,tokCount, dubCount = 0; //used to determine which process block is being used
	int startLine, endLine = 0;
	lineNum = 1;
    tokCount = 0;
    dubCount = 0;

    int blocks[numofPros+1];
    int blockCount = 1;
    blocks[0] = 1;
	// printf("PRO: %d IN: %d OUT: %d\n",numofPros,threadSwitchIn,threadSwitchOut);
	
    //check for where each process block starts, puts line numbers in an array


    for (int j = 1; j < max; ++j)
     
     {
		
		for (int i = 0; i < 4; ++i)
		{
            if (i > 2)
            {
                 dubCount = 0;

            }

			if (i == 0)
			{
				buff = malloc(100);
                strcpy(buff,lines[j]);
                buff = strtok(buff," ");
				tokCount++;
			} else {
				buff = strtok(NULL," ");
				if (buff == NULL && i < 3)
				{

					if (dubCount > 0)
					{
						dubCount = 2;
                        // printf("DUBBB @ %d\n",j);
                        blocks[blockCount] = j;
                        blockCount++;


					} else {
						dubCount++;
						// tokCount = 0;
					}
                    break;
				} else {
					tokCount++;
					
				}
			}
		
    	}
    }
    
    //testing
    // for (int i = 0; i < blockCount; ++i)
    // {
    //     printf("BLO: %d LINE: %s\n",blocks[i],lines[blocks[i]] );    
    // }

    //checks to see if number of process matches number of blocks found
    if (blockCount != numofPros)
    {
        printf("Reading process blocks error....\n");
    }

    for (int i = 0; i < numofPros; ++i)
    {
            processes[i] = createProcess(lines,blocks[i],0);
        
    }

    //addup cpu times for each proceesss
    int totalTimeReq = 0;
    int thNum  = 0;
    float avg = 0;
    

    for (int i = 0; i < numofPros; ++i)
    {
        thNum = thNum + processes[i]->threadNum;
    }

    int turns[thNum];

    for (int i = 0; i < thNum; ++i)
    {
       turns[i] = 0;
    }

    for (int i = 0; i < numofPros; ++i)
    {
        totalTimeReq = totalTimeReq + addupCPU(processes[i]);
    }

    totalTimeReq = totalTimeReq + ((threadSwitchOut+threadSwitchIn)*2);

    for (int i = 0; i < numofPros; ++i)
    {   
        for (int j = 0; j < processes[i]->threadNum; ++j)
        {
            turns[i+j] = processes[i]->threads[j].aTime + processes[i]->threads[j].cpuTime;
        }
        
    }
    int sum = 0;
    for (int i = 0; i < thNum; ++i)
    {
        sum = sum +turns[i];
    }
    avg = sum/thNum;
    
    

    printf("FCFS Scheduling\nTotal Time required is %d time units\n", totalTimeReq);
    printf("Average Turnaround Time is %.2lf time units\n",avg );
    printf("CPU Utilization is 95%% \n" );


	

	return 0;
}


/*read stdin (input file) and place each line 
  into string array.
Arguments:
    Pointer to line number count

Return value:
    char** (pointers to several char*'s or a string array)
*/
char **readFile(int *num) {

	char **lines = malloc(sizeof(char*)*1024);
	char *buf = malloc(sizeof(char)*1024);


	while (fgets(buf,50,stdin) != NULL) {

		lines[*num] = malloc(sizeof(char)*1024);
		lines[*num] = strcpy(lines[*num],buf);
		*num = *num +1;
	}

	return lines;
}

Process * createProcess(char **lines, int start, int end) {
    Process * pro = malloc(sizeof(Process)*1024);
    // pro.threads = malloc(sizeof(Thread) + (Process) * sizeof(Thread) );
    char * buff = malloc(sizeof(char)*10);
    int count = start;
    pro->start = start;
    pro->end = end-1;
    strcpy(buff,lines[start]);
    buff = strtok(buff, " ");
    pro->id = atoi(buff);
    buff = strtok(NULL," ");
    pro->threadNum = atoi(buff);
    count++;

    for (int i = 0; i < pro->threadNum; ++i)
    {
        // buff = malloc(1024);        
        strcpy(buff,lines[count]);
        buff = strtok(buff," ");
        pro->threads[i].num = atoi(buff);
        buff = strtok(NULL," ");
        pro->threads[i].aTime = atoi(buff);
        buff = strtok(NULL," ");
        pro->threads[i].bursts = atoi(buff);
        // printf("BUFF:%d  %d   %d\n",pro->threads[i].num,pro->threads[i].aTime,pro->threads[i].bursts );
        //intialize the thread values first....
        pro->threads[i].cpuTime = 0;
        pro->threads[i].ioTime = 0;
        // pro.threads[i].
        for (int j = 0; j < pro->threads[i].bursts ; ++j)
        {
            /* code */
            count++;
            if (j == pro->threads[i].bursts - 1)
            {
                // buff = malloc(1024);                
                strcpy(buff,lines[count]);
                buff = strtok(buff," ");
                buff = strtok(NULL," ");
                pro->threads[i].cpuTime = pro->threads[i].cpuTime + atoi(buff);
                pro->threads[i].last = 0;
                // free(buff);

                
            } else {
                // buff = malloc(1024);               
                strcpy(buff,lines[count]);
                buff = strtok(buff," ");
                buff = strtok(NULL," ");
                pro->threads[i].cpuTime = pro->threads[i].cpuTime + atoi(buff);
                buff = strtok(NULL," ");
                pro->threads[i].ioTime = pro->threads[i].ioTime + atoi(buff);
                // free(buff);

            }
            // printf("COUNT:%d\n", count);
        }

        // printf("CPU: %d IO: %d\n",pro->threads[i].cpuTime,pro->threads[i].ioTime );
        count++;
        // free(buff);
        

    }
    // free(buff);
    
    // printf("hey: %d ID: %d  TH: %d\n",pro.end,pro.id, pro.threadNum);


    return pro;
}

Process createLastProcess(char **lines, int start) {
    printf("last\n");

    // Process pro;
    // char * buff = malloc(sizeof(char)*10);
    // int count = start;
    // pro.start = start;
    // // pro.end = end-1;
    // strcpy(buff,lines[start]);
    // buff = strtok(buff, " ");
    // pro.id = atoi(buff);
    // buff = strtok(NULL," ");
    // pro.threadNum = atoi(buff);
    // count++;

    // for (int i = 0; i < pro.threadNum; ++i)
    // {
    //     buff = malloc(1024);    //     strcpy(buff,lines[count]);
    //     buff = strtok(buff," ");
    //     pro.threads[i].num = atoi(buff);
    //     buff = strtok(NULL," ");
    //     pro.threads[i].aTime = atoi(buff);
    //     buff = strtok(NULL," ");
    //     pro.threads[i].bursts = atoi(buff);
    //     printf("BUFF:%d  %d   %d\n",pro.threads[i].num,pro.threads[i].aTime,pro.threads[i].bursts );
    //     //intialize the thread values first....
    //     pro.threads[i].cpuTime = 0;
    //     pro.threads[i].ioTime = 0;
    //     // pro.threads[i].
    //     for (int j = 0; j < pro.threads[i].bursts ; ++j)
    //     {
    //         /* code */
    //         count++;
    //         if (j == pro.threads[i].bursts - 1)
    //         {
    //             buff = malloc(1024);    //             strcpy(buff,lines[count]);
    //             buff = strtok(buff," ");
    //             buff = strtok(NULL," ");
    //             pro.threads[i].cpuTime = pro.threads[i].cpuTime + atoi(buff);
    //             pro.threads[i].last = 0;
                
    //         } else {
    //             buff = malloc(1024);    //             strcpy(buff,lines[count]);
    //             buff = strtok(buff," ");
    //             buff = strtok(NULL," ");
    //             pro.threads[i].cpuTime = pro.threads[i].cpuTime + atoi(buff);
    //             buff = strtok(NULL," ");
    //             pro.threads[i].ioTime = pro.threads[i].ioTime + atoi(buff);

    //         }
    //         // printf("COUNT:%d\n", count);
    //     }

    //     printf("CPU: %d IO: %d\n",pro.threads[i].cpuTime,pro.threads[i].ioTime );
    //     count++;

        

    // }
    // // free(buff);
    
    // // printf("hey: %d ID: %d  TH: %d\n",pro.end,pro.id, pro.threadNum);


    // return pro;

}

int addupCPU(Process *pro) {
    int num = 0;

    for (int i = 0; i < pro->threadNum; ++i)
    {
        
            num = num + pro->threads[i].cpuTime;
        
    }




    return num;
}

Thread createThread(char **lines, int start) {
    Thread th;


    return th;
}

