#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"
// struct job{
//    int no;
//    char *name;
//    char *state;
//    char *pid;
//    char *time;
// };
struct job jobs[1000];
int cmp(const void *a,const void *b){
	struct job *A=(struct job*)a;
	struct job *B=(struct job*)b;
	return (A->time-B->time);
}
int jobs_size=0;
void exec_jobs(){
   jobs_size=0;
   DIR *d;
   struct dirent *dir;
   
   FILE *status_file,*stat_file;
   // int a1=0;
   d=opendir("//proc");
   char * line=NULL;
   size_t len=0;


   
   if(d){
   	
   // printf("heelo\n");
      while((dir=readdir(d))!=NULL){
         char path[1000];
         char path2[1000];
         strcpy(path,"/proc/");       
         if(dir->d_name[0]<='9' && dir->d_name[0]>='1'){
            struct job j;
            strcpy(j.pid,dir->d_name);
            
            strcat(path,dir->d_name);
            strcpy(path2,path);
            strcat(path,"/status");
            strcat(path2,"/stat");
            status_file=fopen(path,"r");
            
           
            while(getline(&line,&len,status_file)!=-1){
               if(strncmp(line,"Name",4)==0){
                  // printf("%s\n",line);
                  // j.name=(char *)malloc(1000*sizeof(char));
                  int i=5;
                  int x=0;
                  while(line[i]==' ' || line[i]=='\t' || line[i]=='\n'){
                     i++;
                  }
                  while(i<strlen(line) && (line[i]!=' ' && line[i]!='\t' && line[i]!='\n') ){
                     j.name[x++]=line[i++];
                  }
                  j.name[x]='\0';
               }
               if(strncmp(line,"State",5)==0){
                  // j.state=(char *)malloc(1000*sizeof(char));
                  int i=6;
                  int x=0;
                  while(line[i]==' ' || line[i]=='\t' || line[i]=='\n'){
                     i++;
                  }
                  while(i<strlen(line) && (line[i]!='\t' && line[i]!='\n')){
                     j.state[x++]=line[i++];
                  }
                  j.state[x]='\0';
               }
            }
           fclose(status_file);
            // printf("%s\n",path2 );
            stat_file=fopen(path2,"r");
            while(getline(&line,&len,stat_file)!=-1){
            	int space=0,xx=0,k=0,nn=(int)strlen(line);
            	for(k=0;k<nn;k++){
            		// printf("yaay");
            		if(line[k]==' '){
            			space++;
            			if(space==21){
            				space=k;
            				break;
            			}
            		}
            	}
            	space++;
            	// printf("%d\n",space );
            	// j.time=(char *)malloc(1000*sizeof(char)); 
            	while(line[space]!=' '){
            		j.time[xx++]=line[space++];
            	}
            	 j.time[xx]='\0';
            }
            fclose(stat_file);
            jobs[jobs_size]=j;
            jobs_size++;
         }
      }
      closedir(d);
      
   }
   qsort(jobs,jobs_size,sizeof(jobs[0]),cmp);   
}
void printjobs(){
      for(int i=0;i<jobs_size;i++){
      	 jobs[i].no=i+1;	
         printf("[%d] %s %s %s\n",jobs[i].no,jobs[i].pid,jobs[i].state,jobs[i].name);
      }
}