#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<signal.h>
#include "header.h"
void exec_fg(int pid){
	int st;
	waitpid(atoi(jobs[pid-1].pid),&st,WUNTRACED);	
}	