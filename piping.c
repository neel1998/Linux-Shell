#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include <fcntl.h>
#include<pwd.h>
#include<grp.h>
#include<math.h>
#include<time.h>
#include "header.h"
// int pipefd[2];

void piping(char *s){
	// char s[10000];
	// strcpy(s,ss);

	int pipefd[2];
	
	int main_in=dup(0);
	int main_out=dup(1);

	char ** piped_cmd;
	piped_cmd=(char **)malloc(100*sizeof(char*));
	int a1=0,a2=0,i=0,status,pre=0,nex=0;
	
	

	while(i<strlen(s)){
        a2=0;
        piped_cmd[a1]=(char*)malloc(1000*sizeof(char));
        while(i<strlen(s) && s[i]!='|'){
        	piped_cmd[a1][a2++]=s[i++];
        }
        piped_cmd[a1][a2]='\0';
        a1++;
     	i++;
    }
    if(a1>1){
	    // pipe(pipefd);
	    for(int i=0;i<a1;i++){
	    	if(i==0){
	    		nex=1;
	    		pre=0;
	    		
	    	}
	    	else if(i==a1-1){
	    		nex=0;
	    		pre=1;
	    		
	    	}
	    	else{
	    		nex=1;
	    		pre=1;

	    	}

	    	if(pre){
	    		close(pipefd[1]);
	    		main_in=dup(0);
	    		dup2(pipefd[0],0);
	    		close(pipefd[0]);
	    	}
	    	if(nex){
	    		pipe(pipefd);
	    		main_out=dup(1);
	    		dup2(pipefd[1],1);
	    	}
	    	int pid=fork();
	    	if(pid==0){
	    		e(piped_cmd[i]);
	    		exit(0);
	    	}
	    	else{
	    		waitpid(pid,&status,WUNTRACED);
	    		dup2(main_in,0);
	   			dup2(main_out,1);
	    	}
	    	
	    }
	}
	else{
		e(piped_cmd[0]);
	}
}