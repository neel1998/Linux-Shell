#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include "header.h"
void exec_ls(char *ss){
	char s[1000]={'\0'};
	strcpy(s,ss);
	int n=strlen(s),args,x=0,l=0,a=0;
	char d_arg[1000]={'\0'},flags[1000]={'\0'};
	DIR *d;
	struct dirent *dir;
	if(n==2){
		d_arg[0]='.';
	}
	else{
		for(int i=0;i<n;i++){
			if(s[i]=='-'){
				args++;
			}
		}
		if(args==0){
			for(int i=3;i<n;i++){
				d_arg[x++]=s[i];
			}
		}
		else{
			int i=3,y=0;
			x=0;

			while(i<n){
				if(s[i]=='-'){
					while(s[i]!=' ' && i<n){
						flags[y++]=s[i++];
					}
					i++;
				}
				else{
					d_arg[x++]=s[i++];
				}
			}
		}
	}
	if(d_arg[(int)strlen(d_arg)-1]==' '){
		d_arg[(int)strlen(d_arg)-1]='\0';
	}
	if(d_arg[0]==' ' || strlen(d_arg)==0 || ( d_arg[0]=='~' && ( (strlen(d_arg)==1)|| (strlen(d_arg)==2) ) ) ){
		d_arg[0]='.';
		d_arg[1]='\0';
	}
	d=opendir(d_arg);
	if(args==0){
		if(d){
			while((dir=readdir(d))!=NULL){
				if(dir->d_name[0]!='.'){
					printf("%s\t",dir->d_name);
				}
			}
			closedir(d);
		}
		printf("\n");
	}
	else{
		for(int i=0;i<strlen(flags);i++){
			if(flags[i]=='l'){
				l++;
			}
			if(flags[i]=='a'){
				a++;
			}
		}
		if(l==1 && a==1){
			if(d){
			while((dir=readdir(d))!=NULL){
				char temp[1000]={'\0'};
				strcpy(temp,d_arg);
				temp[(int)strlen(d_arg)]='/';
				strcat(temp,dir->d_name);
				exec_lsl(temp);
				printf("\t%s\n",dir->d_name);
			}
			closedir(d);
			}
			printf("\n");
		}
		else if(l==1 && a==0){
			if(d){
			while((dir=readdir(d))!=NULL){
				if(dir->d_name[0]!='.'){
					char temp[1000]={'\0'};
					strcpy(temp,d_arg);
					temp[(int)strlen(d_arg)]='/';
					strcat(temp,dir->d_name);
					exec_lsl(temp);
					printf("\t%s\n",dir->d_name);
				}
			}
			closedir(d);
			}
			printf("\n");
		}
		else if(l==0 && a==1){
			if(d){
				while((dir=readdir(d))!=NULL){
					printf("%s\t",dir->d_name);
				}
				closedir(d);
			}
			printf("\n");		
		}
	}
	return;
}