#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<signal.h>
#include "header.h"
static volatile int running=1;
void InteruptHandler(int x){
	running=0;
}	
void exec_clock(char *ss){
	
	char s[1000]={'\0'};
	strcpy(s,ss);
	int n=strlen(ss);

	char interval[10]={0};
	int i=9,j=0,inter;
	while(i<n){
		interval[j++]=s[i++];
	}
	interval[j]='\0';
	sscanf(interval,"%d",&inter);

	signal(SIGINT,InteruptHandler);
	signal(SIGTSTP,InteruptHandler);

	while(running){
		time_t mtime=time(NULL);
		char time[100]={'\0'};
	   	strftime(time,100,"%H:%M:%S",localtime(&(mtime)));
		printf("%s\n", time);
		sleep(inter);
	}
}
