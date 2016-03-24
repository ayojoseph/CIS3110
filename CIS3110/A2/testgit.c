#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
void FCFS(int dMode,int vMode);
void RR(int dMode,int vMode,int quant);
 
 int main(int argc, char *argv[]) {
   int i=0;
   int dMode=0;
   int vMode=0;
   int mode=0;
   int quant=0;
   printf("\n");
 
   //Command Line arguments
   for(int flags=0;flags<argc;flags++)
   {
     if(strcmp(argv[flags],"-d")==0)
     {
       dMode=1;
     }
     if(strcmp(argv[flags],"-v")==0)
    {
       vMode=1;
     }
     if(strcmp(argv[flags],"-r")==0)
     {
       mode=1;
       quant=atoi(argv[flags+1]);
 
     }
   }
   //What mode
   if(mode=1)
   {
    RR(dMode,vMode,quant);
 
  }
  else
  {
    FCFS(dMode,vMode);
  }
 }
 
void FCFS(int dMode,int vMode) {
   //Declare all the variables
   int tempI=0;  
   int numRound=0;
   char temp;
 
   int numproc=0;
   int tswitch=0;
   int procswitch=0;
   int procnum=0;
   int numthread=0;
 
   int tnum=0;
   int atime=0;
   int numCPU=0;
 
   int cpuTime=0;
   int ioTime=0;
 
   int totalIoTimeA[100];
   int totalIoTime=0;
   int tempIoTime=0;
   int tempCpuTime=0;
   int totalCpuTimeA[100];
   int totalCpuTime=0;
   int finalTime=0;
 
   //Declare even more!
   int tempFinal=0;
   int j=0;
   int tTime=0;
   int tCount=0;
   int wasted=0;
   double tAvg=0;
 
   //Read first set of info
   fscanf(stdin, "%d %d %d", &numproc, &tswitch, &procswitch);
   finalTime=finalTime+(procswitch*numproc);
   //Start overhead count
   wasted=numproc*procswitch;
   //Start nested for loop
   for(int i=0; i<numproc;i++)
   {
 
     fscanf(stdin, "%d %d", &procnum, &numthread);
     tCount=tCount+numthread;
     finalTime=finalTime+(tswitch*numthread);
     wasted=wasted+(tswitch*numthread);
     for(int q=0; q<numthread;q++)
     {
       fscanf(stdin, "%d %d %d", &tnum, &atime, &numCPU);
       
       for(j=0; j<numCPU-1;j++)
       {
        fscanf(stdin, "%d %d %d",&temp, &cpuTime,&ioTime);
        totalIoTimeA[j]=ioTime;
        totalCpuTimeA[j]=cpuTime;      
      }
 
      fscanf(stdin, "%d %d",&temp, &cpuTime);
      totalCpuTimeA[j]=cpuTime;
      //Detailed info reset
      tempIoTime=0;
      for(j=0; j<numCPU-1;j++)
      {
       totalIoTime=totalIoTime+totalIoTimeA[j];
       tempIoTime=tempIoTime+totalIoTimeA[j];
     }
     //Detailed info reset
     tempCpuTime=0;
     for(j=0; j<numCPU;j++)
     {
       totalCpuTime=totalCpuTime+totalCpuTimeA[j];
       tempCpuTime=tempCpuTime+totalCpuTimeA[j];
     }
     tempFinal=tempCpuTime+tempIoTime;
     tTime=tTime+tempFinal+tswitch;
   
     if(tnum==1)
     {
       tTime=tTime+procswitch;
     }
     tAvg=tAvg+(tTime-atime);
     if(dMode==1)
     {
 
       printf("\n\nThread %d of Process %d: \n\n",tnum,procnum);  
       printf("Arrival time: %d \n",atime); 
       printf("Service time: %d units \n",tempFinal-tempIoTime); 
       printf("I/O time: %d units \n",tempIoTime); 
       printf("Turnaround time: %d units \n",tTime-atime) ;
       printf("Finish time: %d units \n\n",tTime);
     }
     if(vMode==1)
     {
       if(tnum==1 && procnum==1)
       {
         printf("Not available, please try again later\n");
       }
 
     }
   }
 }
 	finalTime=finalTime+totalCpuTime+totalIoTime;
 	double turnAvg=tAvg/tCount;
 	double CPUU=(finalTime-wasted);
 	CPUU=(CPUU/finalTime);
 	printf("\n\nTotal Time required is %d units\n",finalTime);
 	printf("Average Turnaround Time is %.2lf time units \n",turnAvg);
 	printf("CPU Utilization is %.2lf \n",CPUU*100);
}

void RR(int dMode,int vMode, int quant) {
 
   int tempI=0;  
   int numRound=0;
   char temp;
 
   int numproc=0;
   int tswitch=0;
   int procswitch=0;
   int procnum=0;
   int numthread=0;
 
   int tnum=0;
   int atime=0;
   int numCPU=0;
 
   int cpuTime=0;
   int ioTime=0;
 
   int totalIoTimeA[100];
   int totalIoTime=0;
   int tempIoTime=0;
   int tempCpuTime=0;
   int totalCpuTimeA[100];
   int totalCpuTime=0;
   int finalTime=0;
 
   int tempFinal=0;
   int j=0;
   int tTime=0;
   int tCount=0;
   int wasted=0;
   double tAvg=0;
 
   int cpuTimeQ[100];
   int ioTimeQ[100];
   int vCount=0;
 
   fscanf(stdin, "%d %d %d", &numproc, &tswitch, &procswitch);
   finalTime=finalTime+(procswitch*numproc);
   wasted=numproc*procswitch;
   for(int i=0; i<numproc;i++)
   {
     fscanf(stdin, "%d %d", &procnum, &numthread);
     tCount=tCount+numthread;
     finalTime=finalTime+(tswitch*numthread);
     wasted=wasted+(tswitch*numthread);
     for(int q=0; q<numthread;q++)
     {
 
       fscanf(stdin, "%d %d %d", &tnum, &atime, &numCPU);
 
       for(j=0; j<numCPU-1;j++)
       {
        fscanf(stdin, "%d %d %d",&temp, &cpuTime,&ioTime);
 
        //RR changes here
        for(int r=0; r<numCPU-1;r++)
        {
         ioTimeQ[r]=ioTime;
         cpuTimeQ[r]=cpuTime;
         if(ioTimeQ[r]-quant>=0)
         {
           ioTimeQ[r]=ioTimeQ[r]-quant;
           cpuTimeQ[r]=cpuTimeQ[r]-quant;
         }
 
         totalIoTimeA[j]=ioTimeQ[r];
         totalCpuTimeA[j]=cpuTimeQ[r];  
       }
 
 
 
     }
     fscanf(stdin, "%d %d",&temp, &cpuTime);
     totalCpuTimeA[j]=cpuTime;
     //Detailed info reset
     tempIoTime=0;
     for(j=0; j<numCPU-1;j++)
     {
       totalIoTime=totalIoTime+totalIoTimeA[j];
       tempIoTime=tempIoTime+totalIoTimeA[j];
     }
     //Detailed info reset
     tempCpuTime=0;
     for(j=0; j<numCPU;j++)
     {
       totalCpuTime=totalCpuTime+totalCpuTimeA[j];
       tempCpuTime=tempCpuTime+totalCpuTimeA[j];
     }
     tempFinal=tempCpuTime+tempIoTime;
     tTime=tTime+tempFinal+tswitch;
     if(tnum==1)
     {
       tTime=tTime+procswitch;
     }
     tAvg=tAvg+(tTime-atime);
     if(dMode==1)
     {
 
       printf("\n\nThread %d of Process %d: \n\n",tnum,procnum);  
       printf("Arrival time: %d \n",atime); 
       printf("Service time: %d units \n",tempFinal-tempIoTime); 
       printf("I/O time: %d units \n",tempIoTime); 
       printf("Turnaround time: %d units \n",tTime-atime) ;
       printf("Finish time: %d units \n\n",tTime);
     }
     if(vMode==1)
     {
       if(tnum==1 && procnum==1)
       {
         printf("Not available, please try again later\n");
       }
     }
 
   }
   
 }
 	finalTime=finalTime+totalCpuTime+totalIoTime;
 	double turnAvg=tAvg/tCount;
 	double CPUU=(finalTime-wasted);
 	CPUU=(CPUU/finalTime);
 	printf("\n\nTotal Time required is %d units\n",finalTime);
 	printf("Average Turnaround Time is %.2lf time units \n",turnAvg);
 	printf("CPU Utilization is %.2lf \n",CPUU*100);
}