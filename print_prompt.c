#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "header.h"


void print_prompt(){
	char temp_dir[10000]={'\0'};
	char sys[10000]={'\0'};
	int x=0;	
	if(strncmp(global_home,global_pwd,strlen(global_home))==0){
		temp_dir[x++]='~';
		for(int i=strlen(global_home);i<strlen(global_pwd);i++)
		{
			temp_dir[x++]=global_pwd[i];
		}
		temp_dir[x]='\0';
	}
	else{
		strcpy(temp_dir,global_pwd);
	}
  	gethostname(sys,10000);    
  	printf("%s@%s %s>>",getenv("USER"),sys,temp_dir);
}
          