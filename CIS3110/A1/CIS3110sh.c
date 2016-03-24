#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>


void shellLoop();
char ** lineTok(char *line);
char *readLine();
void printArr(char**args);
int execution(char**args, int (*pids)[30]);
int openShell(char**args);
// int backopenShell(char**args, pid_t pids[30]);
int backopenShell(char**args, int (*pids)[30]);
int FileOutShell(char**args);
int FileInShell(char**args);
int shellExit(char **args);
int shell_cd(char **args);
char *dir;

int main(int argc, char const *argv[])
{

	// char *functionStr[] = {
	// 	"exit"
	// };

	// int (*functPtr[]) (int) = {
	// 	&shellExit
	// };
	shellLoop();
	return 0;
}


void shellLoop() {
	// ReadLine
	//Create Arguments
	//Execute

	//Vairbles
	char *line;
	// char *dir = getcwd(dir,1024); 
	char **args; 
	int pids[30];
	int status = 1;
	dir = getcwd(dir,1024);

	do {

		printf("%s > ",dir);
		line = readLine();
		args = lineTok(line);
		status = execution(args,&pids);
		if (status == 2)
		{
			// printf("CHILD: %d\n",pids[0] );
			status = 1;
		}

	} while(status); 

	//used for testing. prints out pids at the end of shellloop

	// for (int i = 0; i < 5; ++i)
	// {
	
	// 	printf("PID: %d\n",pids[i] );
	// }


	free(args);
	free(line);
}

char * readLine() {
	int i = 0;
	int size = 1024;
	char * line = malloc(sizeof(char)*size);
	fgets(line,1024,stdin);
	i = strlen(line);

	line = strtok(line,"\n");



		if (i >= size)
		{
			size = size + 1024;
			line  = realloc(line,size);
		}

	return line;
}

char ** lineTok(char *line) {
	char **args = malloc(sizeof(char*)*1024);
	int i = -1;

	do
	{
		i++;
		if (i == 0) {
				args[i] = strtok(line," ");
		} else {

			args[i] = strtok(NULL," ");
		}
		 
	} while(args[i] != NULL);

	args[i] = '\0';

	return args;
}

int execution(char**args, int (*pids)[30]) {
	int cmdNum = 2;
	char **functionStr= malloc(sizeof(char*)*cmdNum+1);
	int i = 0;
	int cmp;
	functionStr[0] = "exit";
	functionStr[1] = "cd";


	int (*functPtr[2]) (char**);
	//  = {
	// 	&shellExit
	// 	&shell_cd
	// };
	functPtr[0] = shellExit;
	functPtr[1] = shell_cd;

	if (args[0] == NULL) {
		return 1;
	}

	//CHECKS IF ANY BUILTS-IN FIRST

	for (int i = 0; i < cmdNum; ++i)
	{
		if (strcmp(args[0],functionStr[i])== 0) {
			return (*functPtr[i])(args);
		}
	}

	//CHECKS IF BACKGROUND PROCESS NEEDED SECONDLY

	if (args[0] != NULL)
	{
	    do {
	        
	        cmp = strcmp("&",args[i]);
	    
	        if (cmp == 0) {
	            if (args[i+1] != NULL) { //checks if anything is after the sign
	                perror("Content");
	                break;
	            } else {
	                // printf("good\n");
	                args[i] = NULL;
	                return backopenShell(args,pids);
	            }
	        }


	        //file redirect
	        cmp = strcmp(">",args[i]);
	        if (cmp == 0) {
	        	printf("file RE\n");
	        	return FileOutShell(args);
	        	break;
	        }

	        
	         //file indirect
	        cmp = strcmp("<",args[i]);
	        if (cmp == 0) {
	        	printf("file IN\n");
	        	
	        	break;
	        }

	        i=i+1;
	    } while(args[i] != NULL);

	    return openShell(args);

	} 
	return 1;
	
}

int openShell(char**args) {
	pid_t child, wpid;
	int status;

	child = fork();
	if (child < 0)	{ //fork failed.
		perror("Forking Error");
	} else if (child == 0) {
		// printf("%d\n",getpid() );
		if(execvp(args[0],args) == -1) {
			perror("Program Error");
			// return 1;
		}
		exit(EXIT_FAILURE);
	} else {
			// printf("Parent\n");
			do {
				wpid = waitpid(child,&status,0);
			}while(!WIFEXITED(status));
			// printf("good..\n");
			
		}
		status = wpid;
		wpid = status;

	// child = fork();
	// execvp(args[0],args);
	return 1;

}

int backopenShell(char**args, int (*pids)[30]) {
	pid_t child, wpid;
	int status;
	static int countPid = 0;

	child = fork();
	if (child < 0)	{ //fork failed.
		perror("Forking Error");
	} else if (child == 0) { //child process
		
		printf("COUNT: %d\n",countPid);
		// (*pids)[countPid] = getpid();
		// printf("%d\n",(*pids)[countPid]);
		// countPid = countPid + 1;
		if(execvp(args[0],args) == -1) {
			perror("Program Error");
			// return 1;
		}
		exit(EXIT_FAILURE);
	} else { //parent
			printf("Parent\n");
			(*pids)[countPid] = child;
		printf("CHILD: %d\n",(*pids)[countPid]);
		countPid = countPid + 1;
			// do {
			// 	wpid = waitpid(child,&status,0);
			// }while(!WIFEXITED(status));
			// printf("good..\n");
			// exit(EXIT_FAILURE);
			
		}
	// child = fork();
	// execvp(args[0],args);
	return 2;

}
int FileOutShell(char**args) {
	pid_t child, wpid;
	int status;
	int i=0;
	FILE *fp;
	char * fileName;
	
	while (args[i+1] != NULL ) {
		i++;
	}
	fileName = strcat(args[i],".txt");
	fp = fopen(fileName,"w+");
	fp = freopen(fileName,"w",stdout);
	args[i] = NULL;
	args[i-1] = NULL;

	child = fork();
	if (child < 0)	{ //fork failed.
		perror("Forking Error");
	} else if (child == 0) { //child process
		if(execvp(args[0],args) == -1) {
			perror("Program Error");
		}
		exit(EXIT_FAILURE);
	} else { //parent process

			do {
				wpid = waitpid(child,&status,0);
			}while(!WIFEXITED(status));
	
		}
		status = wpid;

	return 1;
}

int FileInShell(char**args) {
	pid_t child, wpid;
	int status;
	int i=0;
	FILE *fp;
	char * fileName;
	
	while (args[i+1] != NULL ) {
		i++;
	}
	fileName = strcat(args[i],".txt");
	fp = fopen(fileName,"r");
	fp = freopen(stdout,"r",fileName);
	args[i] = NULL;
	args[i-1] = NULL;

	child = fork();
	if (child < 0)	{ //fork failed.
		perror("Forking Error");
	} else if (child == 0) { //child process
		if(execvp(args[0],args) == -1) {
			perror("Program Error");
		}
		exit(EXIT_FAILURE);
	} else { //parent process

			do {
				wpid = waitpid(child,&status,0);
			}while(!WIFEXITED(status));
	
		}

	return 1;
}

int shellExit(char **args) {
	printf("logout\n");
	// exit(0);
	return 0;
}

int shell_cd(char **args) {


	if (args[1] == NULL)
	{
		printf("Please Specifiy directory.\n");
	} else{
		if (chdir(args[1]) < 0) //change error
		{
			perror("Directory does not exist.");
		} else {
			dir = getcwd(dir,1024); //updates directory tag
		}

	}
	return 1;

}

void printArr(char**args) {
	int i = 0;

	// printf("%l\n",sizeof(args) );
	while(args[i] != '\0')
	{
		if (strlen(args[i])<=0 || i >= sizeof(args))
		{
			// break;
		}
		printf("String @ %d : %s\n",i,args[i] );
		i++;
	}
}
