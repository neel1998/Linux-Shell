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
#include "header.h"
void exec_remind(char *ss){
	char s[1000]={'\0'};
	strcpy(s,ss);
	int n=strlen(ss);
	int i=9,time,j=0,k=0;
	char temp[1000]={'\0'},t[10]={'\0'};
	while(i<n && s[i]!=' '){
		t[j++]=s[i++];
	}
	for(int x=i;x<n;x++){
		temp[k++]=s[x];
	}
	t[j]='\0';
	temp[k]='\0';
	sscanf(t,"%d",&time);
	sleep(time);
	printf("%s\n",temp);
}