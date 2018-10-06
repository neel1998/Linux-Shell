#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "header.h"
char * redirect_out(char * s){
    char *temp,*temp1,*temp2;
    temp=(char*)malloc(10000);
    temp1=(char*)malloc(10000);
    int redirect=0,mainfd;
    int x=strlen(s);
    for(int i=0;i<x;i++){
        if(s[i]=='>'){
            redirect=i;
            // printf("redirect out found\n");
            break;
        }
    }
    int j=0,append=0;
    if(redirect!=0){
        strncpy(temp,s,redirect-1);
        if(s[redirect+1]=='>'){
            append=1;
            redirect++;
        }
        for(int i=redirect+2;i<x;i++){
            temp1[j++]=s[i];
        }
        temp1[j]='\0';
        if(append==0){
            outfd = open(temp1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        else{
            int fd=open(temp1,O_RDONLY);
            if(fd==-1){
                outfd = open(temp1, O_WRONLY | O_CREAT | O_APPEND, 0644);   
            }
            else{
                outfd = open(temp1, O_WRONLY | O_APPEND, 0644);      
            }
        }
        if(outfd == -1) {
            perror("rediret out : Failed to open file");
        }
        if(dup2(outfd, 1) != 1){ 
             perror("redirect out : dup2 fail");
             // close(mainfd);
        }
        return temp;
    }
    else{
        return s;
    }
}