#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"

int e(char *i){
  char input[10000];
  char temp1[10000]={'\0'};
  char *s;
  strcpy(input,i);
  int echo=0,cd=0,ls=0,status;
  s=trim(input);

  

  if(s[0]=='e' && s[1]=='c' && s[2]=='h' && s[3]=='o'){
   	echo=1;
  }
  if(s[0]=='c' && s[1]=='d'){
   	cd=1;
  }
  if(s[0]=='l' && s[1]=='s'){
  	ls=1;
  }
  if(strncmp(s,"quit",4)==0){
   	run=0;
   	return 0;
  }
    else{
        if(strncmp(s,"pwd",3)==0){
        	int back=0;
        	if(s[strlen(s)-1]=='&'){
        		back=1;
        	}
       		int pid=fork();
       		if(pid==0){
       			s=redirect_out(s);
       			printf(">>%s\n",global_pwd);
       			exit(0);		
       		}
       		else{
       			if(back==0){
       				waitpid(pid,&status,WUNTRACED);
       			}
       			return 1;
       		}
        }
        else if(cd==1){
        	int y=0;
        	for(int i=3;i<strlen(s);i++){
        		temp1[y++]=s[i];
        	}	
        	temp1[y]='\0';
        	if(strcmp(temp1,"~")==0){
        		chdir(global_home);
        		getcwd(global_pwd,10000);
        		return 1;		
        	}
        	else{
        		chdir(temp1);
        		getcwd(global_pwd,10000);
        		return 1;
        	}
        }   
        else if(echo==1){
        	int back=0;
        	if(s[strlen(s)-1]=='&'){
        		back=1;
        		s[strlen(s)-1]='\0';
        	}
        	int pid=fork();
        	if(pid==0){
        		s=redirect_out(s);
        		for(int i=5;i<strlen(s);i++){
        			printf("%c",s[i]);
        		}
        		printf("\n");
        		exit(0);
        	}	
        	else{
        		if(back==0){
       				waitpid(pid,&status,WUNTRACED);
       			}
       			// dup2(mainfd,STDOUT_FILENO);
       			return 1;
        	}	
        } 
        else if(ls==1){
        	int back=0;
        	if(s[strlen(s)-1]=='&'){
        		back=1;
        		s[strlen(s)-1]='\0';
        	}
        	int pid=fork();
        	if(pid==0){
        		s=redirect_out(s);
        		exec_ls(s);
        		exit(0);       	 		
        	}
        	else{
        		if(back==0){
       				waitpid(pid,&status,WUNTRACED);
       			}
       			return 1;
        	}
        }
        else if(strncmp(s,"pinfo",5)==0){
        	int back=0;
        	if(s[strlen(s)-1]=='&'){
        		back=1;
        		s[strlen(s)-1]='\0';
        	}
        	int pid=fork();
        	if(pid==0){
        		s=redirect_out(s);
        		if(back==1){
        			exec_pinfo(s,getppid());
        		}
        		else{
        			exec_pinfo(s,getpid());		
        		}
        		exit(0);       	 		
        	}
        	else{
        		if(back==0){
       				waitpid(pid,&status,WUNTRACED);
       			}
       			else{
       				struct proc P;
           			strcpy(P.name,"pinfo");
           			P.pid=pid;
           			proc_arr[proc_size++]=P;
       			}
       			return 1;
        	}
        }
        else if(strncmp(s,"remindme",8)==0){
        	int pid=fork();
        	if(pid==0){
        		s=redirect_out(s);
        		exec_remind(s);
        		exit(0);
        	}
        	else{
        		struct proc P;
           		strcpy(P.name,"remindme");
           		P.pid=pid;
           		proc_arr[proc_size++]=P;
        		return 1;
        	}
        }
        else if(strncmp(s,"clock -t",8)==0){
       		exec_clock(s);
        	return 1;
        }
        else if(strncmp(s,"setenv",6)==0){
        	char name[1000];
        	char value[1000];
        	int j=0,i=7,l=0;
        	while(i<strlen(s) && s[i]!=' '){
        		name[j++]=s[i];
        		i++;
        	}
        	if(j==0){
        		printf("ERROR: no variable name given\n");
        		return 1;
        	}
        	name[j]='\0';
        	if(i==strlen(s)){
        		value[0]='\0';
        	}
        	else{
        		if(s[i+1]=='"' && s[strlen(s)-1]=='"'){
        			for(int k=i+2;k<strlen(s)-1;k++){
        				value[l++]=s[k];
        			}
        		}
        		else{
        			int k=i+1;
        			while(k<strlen(s) && s[k]!=' '){
        				value[l++]=s[k++];
        			}
        			value[l]='\0';
        			if(k!=strlen(s)){
        				printf("extra arguements\n");
        				return 1;
        			}
        		}
        	}
        	// printf("%s=%s\n",name,value);
	        	// printf("%d\n",setenv(name,value,1));
        	setenv(name,value,1);
        }
        else if(strncmp(s,"getenv",6)==0){
        	char name[1000];
        	int j=0,i=7,l=0;
        	while(i<strlen(s) && s[i]!=' '){
        		name[j++]=s[i];
        		i++;
        	}
        	name[j]='\0';
        	char *val=getenv(name);
        	if(val==NULL){
        		printf("ERROR: No variable exists\n");
        	}
        	else{
        		printf("%s\n",val);
        	}
        	return 1;
        }
        else if(strncmp(s,"unsetenv",8)==0){
        	char name[1000];
        	int j=0,i=9,l=0;
        	while(i<strlen(s) && s[i]!=' '){
        		name[j++]=s[i];
        		i++;
        	}
        	name[j]='\0';
        	char *val=getenv(name);
        	if(val==NULL){
        		printf("ERROR: No variable exists\n");
        	}
        	else{
        		unsetenv(name);
        		// printf("%s\n",val);
        	}
        	return 1;
        }
        else if(strncmp(s,"jobs",4)==0){
        		exec_jobs();
        		printjobs();
        		return 1;
        }
        else if(strncmp(s,"kjob",4)==0){
        	char pp[1000],sig[1000];
        	int i=5,x=0;
        	while(i<strlen(s) && s[i]!=' '){
        		pp[x++]=s[i++];
        	}
        	pp[x]='\0';
        	i++;
        	x=0;
        	while(i<strlen(s) && s[i]!=' '){
        		sig[x++]=s[i++];
        	}	
        	sig[x]='\0';
       		exec_kjob(atoi(pp),atoi(sig));
       		return 1;
        }
        else if(strncmp(s,"bg",2)==0){
        	char pp[1000];
        	int i=3,x=0;
        	while(i<strlen(s) && s[i]!=' '){
        		pp[x++]=s[i++];
        	}
        	pp[x]='\0';
       		exec_bg(atoi(pp));
       		return 1;
        }
        else if(strncmp(s,"fg",2)==0){
        	char pp[1000];
        	int i=3,x=0;
        	while(i<strlen(s) && s[i]!=' '){
        		pp[x++]=s[i++];
        	}
        	pp[x]='\0';
       		exec_fg(atoi(pp));
       		return 1;
        }
        else if(strncmp(s,"overkill",8)==0){
        	for (int nn=0;nn<proc_size;nn++){
        		if(proc_arr[nn].killed!=-1){
	           		proc_arr[nn].killed=-1;
	           		kill(proc_arr[nn].pid,9);
        		}
        	}
        	return 1;
        }
        else{
        	char **arg_arr;
        	arg_arr=(char **)malloc(1000*sizeof(char*));
        	int back=0;
        	struct proc P;
	       	if(s[strlen(s)-1]=='&')
	       	{
	       		back=1;
	       		s[strlen(s)-1]='\0';

	       	}	
           	int a1=0,a2=0,a3=0,i=0;
           	
           	int pid=fork();
       		if(pid==0)
           	{
           		// printf("%s\n",s);
           		s=redirect_out(s);
           		// printf("%s\n",s);
           		s=redirect_in(s);
           		
           		// printf("%s\n",s);
           		while(i<strlen(s)){
           			a2=0;
           			arg_arr[a1]=(char*)malloc(1000*sizeof(char));
           			while(i<strlen(s) && s[i]!=' '){
           				arg_arr[a1][a2++]=s[i++];
           				// printf("%c\n",arg_arr[a1][a2-1]);
           			}
           			arg_arr[a1][a2]='\0';
           			if(a1==0 && back==1){
           				strcpy(P.name,arg_arr[a1]);
           				// printf("%s\n",P.name);

           			}
           			// printf("%d %s\n",a1,arg_arr[a1]);
           			a1++;
           			i++;
           		}
             	int err=execvp(arg_arr[0], arg_arr);
             	if(err<0){
             		printf("No such Command\n");
             	}
             	exit(0);
          	}
           	else
           	{
           		
           		if(back==0){
           			waitpid(pid,&status,WUNTRACED);
           		}
           		else{
           			
           			
           			P.pid=pid;
           			P.killed=0;
           			proc_arr[proc_size++]=P;
           		}
           		return 1;
           	}
           	//free(arg_arr);
        }
    }
}           
