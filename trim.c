#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "header.h"
char *trim(char *s){
	char *temp,*temp1,*temp2;
	temp=(char*)malloc(10000);
	temp1=(char*)malloc(10000);
	temp2=(char*)malloc(10000);
	int x=0,i;
	int n=strlen(s);
	for(i=0;i<n;i++){
    	if(s[i]=='\t'){
    		s[i]=' ';
    	}
    }
    for(i=0;i<n;i++){
    
        if(s[i]==' ' && s[i+1]==' ' ){
            continue;
        }
        else{
        	if(s[i]==' '){
        		if(x!=0 && i!=(n-1)){
        		temp[x++]=s[i];
        		}
        	}
        	else{
        		temp[x++]=s[i];
        	}	
        }
    }

    temp[x]='\0';
   	return temp;
}