#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include "header.h"
void exec_bg(int pid){
	
	if(kill(atoi(jobs[pid-1].pid),SIGCONT)==0){
		printf("Signal Sent\n");
	}
	else{
		printf("ERROR\n");
	}
}	