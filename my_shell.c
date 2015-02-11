// Assignment 1 - Part 2
// 02/02/2015
// Author: Archit Sood

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h> 



//A Magic funtion. Not entirely sure what it does but fixed quite a few bugs
void childHandler(int sig)
{
	int pid;
	pid = wait(0);
}

// The following function handles the pipes:
void pipeExec(char **arguments, int pipeCounter, int *pipeIndexArray){

	int i;
	int status;
	int fds[pipeCounter*2];
	int currentArg=0;

//Initiate the pipes:
	for (i=0; i< 2*pipeCounter; i=i+2){
		pipe(fds+i);
	}
// First Pipe:**************************************
	if (currentArg==0){
		pid_t pid1;
		pid1 = fork();
		if (pid1 == 0){
        	close(1);
        	dup2(fds[1], 1);
        	int k;
        	for (k=0; k<pipeCounter*2; k++){
        		close(fds[k]);
        	}
        	int errorCheck;
        	errorCheck=execvp(arguments[0],arguments);
        	if (errorCheck<0){
		   		printf("Invalid Command\n");
		   		exit(0);
 			}

      	}

      	else if (pid1 < 0){
			printf("forking has failed");
			exit(0);
        	}

	}
		currentArg++;	
// Middle Pipes:**************************************

		while(currentArg<=pipeCounter){
			
			if (currentArg<pipeCounter){
				pid_t pid2;
				pid2 = fork();
				if(pid2==0) {
					dup2(fds[currentArg*2-2],0);
					dup2(fds[currentArg*2+1],1);
					int k;
					for (k=0; k<pipeCounter*2; k++){
        				close(fds[k]);
        			}
 					   	int errorCheck;
 					   	errorCheck=execvp(arguments[pipeIndexArray[currentArg]],arguments+pipeIndexArray[currentArg]);
 					   	if (errorCheck<0){
 					   		printf("Invalid Command\n");
 					   		exit(0);
 					   	}
				}
				else if(pid2 < 0){
					printf("Forking failed\n");
				}

			}
// Last Pipe********************************************
			else{ //last child
				pid_t pid3;
				pid3 = fork();
				if(pid3==0) {
					dup2(fds[currentArg*2-2],0);
					int k;
					for (k=0; k<pipeCounter*2; k++){
        				close(fds[k]);
        			}
        				int errorCheck;
        				errorCheck=execvp(arguments[pipeIndexArray[currentArg]],arguments+pipeIndexArray[currentArg]);
					   	if (errorCheck<0){
 					   		printf("Invalid Command\n");
 					   		exit(0);
 					   	}
				}
				else if (pid3 < 0){
					printf("Forking failed\n");
				}
			}
			
			currentArg++;
		}
   	
// Close the pipes:**************************************
			int k;
			for (k=0; k<pipeCounter*2; k++){
        		close(fds[k]);
        	}

// Waits for child processes to end:*********************
        	int waitCount;
			for (waitCount=0;waitCount<pipeCounter;waitCount++){
				wait(0);
			}
     
        		
}

int main () {


while(1){

	fflush(stdout);
	printf("archits_shell$> ");       // User Prompt
	fflush(stdout);

	char buff[1000];                  // Holder for user input
	fgets(buff, sizeof(buff), stdin); // gets the user input into buffer 
	signal(SIGCHLD, childHandler);	  // child stopper
	int status;

	//Lets tokenize the user input**************************************
	char *token;
	token=strtok(buff," \t\n");
	char *arguments[1000]; // This array hold tokenized inputs after parsing

	int argCount=0; 
	int pipeCounter=0; // Counts the number of pipes in user input
	int pipeIndexArray[100]; // Array that keeps track of 
	int argPosition=1;
	pipeIndexArray[0]=0;

	//Parse the user input:
	while(argCount < 1000 && token != NULL){
		//printf("%s", token);
		if (strcmp(token,"|")==0){
			arguments[argCount]=NULL;
			pipeIndexArray[argPosition]=argCount+1;
			argPosition++;
			pipeCounter++;
		}
		else{
			arguments[argCount] = token;		
		}
		
		token = strtok(NULL," \t\n");
		argCount++;
	}
		arguments[argCount] = NULL;

	//********************************************************************
	
	// The following checks the "&" at the end of command and checks the backgrounding 
	int index;
	index=0;
	bool backgroundCheck = false;
	while(arguments[index]!=NULL){
		if (strcmp(arguments[index],"&")==0){
			backgroundCheck=true;
			arguments[index]=NULL; // Replace "&" by NULL
			break;
		}
		index++;
	}

	//If no command is entered. And user just presses Enter at the prompt******* 
	if (arguments[0]==0){
		continue;
	}

	//If just "&" is entered as the first argument******************************
	else if (strcmp(arguments[0],"&")==0){
		perror("Invalid Command\n");
		continue;
	}

	//Command for exiting the shell**********************************************
	else if (strcmp(arguments[0],"exit")==0){
		exit(0);
	}

	//The fg and bg commands have not been implemented yet
	else if (strcmp(arguments[0],"fg")==0 || strcmp(arguments[0],"bg")==0){
		printf("Maybe Some Day\n");
	}

	//The cd commands helps to change the directory*******************************
	else if (strcmp(arguments[0],"cd")==0){	
		int check;
		check=chdir(arguments[1]);
		if (check == -1){
			printf("failed to change the directory\n");
			continue;
		}
		else{
			printf("You are in %s directory \n", arguments[1]);
		}
	}

	// Did not implement jobs, but system call ps displayes the process status along with jobs in background that go
	// with "&" at the end of command.
	else if (strcmp(arguments[0],"jobs")==0){
		system("ps");
	}

	//The following checks if the user input has pipes and executes the piping function 
	else if (pipeCounter>0){
		pipeExec(arguments, pipeCounter, pipeIndexArray);
	}

	//The following excecutes commands like "ls", "ps" etc.************************* 
	else{
		
		int pid;
		pid=fork();
		if (pid < 0){
			printf("forking has failed");
		}


		else if (pid==0){

			int errorCheck;
			errorCheck= execvp(arguments[0], arguments);

			if (errorCheck == -1){
				printf("Invalid Command\n");
				exit(0);
			}

		}

		else if (pid > 0){
			// if backgrounding check with "&" is false
			if (!backgroundCheck){
				wait(&status);
			}
		}

		else{
			printf("ERROR :child process not created.\n");
		}


	}

	}
return 0;

}

//References:
// http://stackoverflow.com/
//https://github.com/Jollyra/blsh/blob/master/main.c
//https://github.com/pulkitarora21/LinuxShell/blob/master/shellv2.c