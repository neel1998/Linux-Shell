#include<stdio.h>
#include<unistd.h>
#include<string.h>
void exec_pinfo(char *ss,int g){
	char s[1000]={'\0'};
	strcpy(s,ss);
	int gpid=g;
    char path[1000]="/proc/",path2[1000],ans_path[1000];
    char get_pid[10];
   	if(strlen(s)==5){
   		sprintf(get_pid,"%d",gpid);
   		strcat(path,get_pid);
   	}
   	else{
   		for(int i=6,j=strlen(path);i<strlen(s);i++,j++)
   			path[j]=s[i];
   	}
   	strcpy(path2,path);
   	
   	
   	strcat(path,"/status");
   	strcat(path2,"/exe");
   	
   	char * line=NULL;
   	size_t len=0;
   	FILE *status_file=fopen(path,"r");
   	
   	readlink(path2,ans_path,1000);
   	if(status_file==NULL){
   		printf("No such process found\n");
   	}
   	else{
  		printf("pid--%d\n",gpid);
   		while(getline(&line,&len,status_file)!=-1){
   					if((line[0]=='S' && line[1]=='t')|| ( strncmp(line,"VmSize",6)==0)){
   						printf("%s\n",line);
   					}
   		}
   		printf("executable path:%s\n\n",ans_path);
   	}
}