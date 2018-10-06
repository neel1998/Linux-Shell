#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<math.h>
#include<time.h>
#include<signal.h>
#include "header.h"

void sigHandler(int sig){
	signal(SIGINT,sigHandler);
}	
void sigHandler2(int sig){
	signal(SIGTSTP,sigHandler2);
}
char global_pwd[1000];
char global_home[1000];

struct proc proc_arr[1000];
int proc_size=0;
int infd,outfd,run;

int main(){  
    getcwd(global_pwd,1000);
    strcpy(global_home,global_pwd);
    char pname[100];
    
    

    char ip[10000]={'\0'},cc[10000]={'\0'};
    int ii=0,yy=0,st,p;
	run=1;	    
    while(run){
        signal(SIGINT,sigHandler);
        signal(SIGTSTP,sigHandler2);
    	p=(waitpid(-1,&st,WNOHANG));
    	while(p>0){
 		   	if(WIFEXITED(st)){
                for (int i=0;i<proc_size;i++){
                    if(proc_arr[i].pid==p && proc_arr[i].killed!=-1){
                    	proc_arr[i].killed=-1;
                        printf("Background Process %s ended with pid=%d\n",proc_arr[i].name,proc_arr[i].pid );
                    }
                }
    		}
    		p=(waitpid(-1,&st,WNOHANG));
    	}
    	ii=0;
    	yy=0;
    	print_prompt();
    	fgets(ip,10000,stdin);
    	ip[strlen(ip)-1]='\0';
    	
    	while(ii<strlen(ip)){
    	 	while(ip[ii]!=';' && ii<strlen(ip)){
    			cc[yy++]=ip[ii++];
    		}
    	 	cc[yy]='\0';
    		yy=0;
    		// e(cc);
    		piping(cc);
    		if(run==0){
    			break;
    		}
    		ii++;
    	}
    } 
    return 0;
}
