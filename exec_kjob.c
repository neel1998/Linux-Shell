#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include "header.h"
void exec_kjob(int pid,int signal){
		
	if(kill(atoi(jobs[pid-1].pid),signal)==0){
		for (int i=0;i<proc_size;i++){
           	proc_arr[i].killed=-1;
        }
		printf("Signal Sent\n");
	}
	else{
		printf("ERROR\n");
	}
}	