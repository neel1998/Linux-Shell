#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "header.h"
char * redirect_in(char * s){
    char *t,*t1;
    t=(char*)malloc(10000);
    t1=(char*)malloc(10000);
    int redirect=0;
    int x=strlen(s);
    for(int i=0;i<x;i++){
        if(s[i]=='<'){
            redirect=i;
            // printf("redirect in found\n");
            break;
        }
    }
    int j=0;
    if(redirect!=0){
        strncpy(t,s,redirect);
        
        for(int i=redirect+2;i<x;i++){
            t1[j++]=s[i];
        }
        t1[j]='\0';
        infd = open(t1, O_RDONLY);
        
        if(infd == -1) {
            perror("redirect in : Failed to open file");
        }
        if(dup2(infd,0) != 0){ 
             perror("redirect in : dup2 fail");
             // close(fd);
        }
        return t;
    }
    else{
        return s;
    }
}