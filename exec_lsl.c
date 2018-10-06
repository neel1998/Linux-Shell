#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
void exec_lsl(char *d){
	struct stat st;
	if(stat(d,&st)==0){
		mode_t mt=st.st_mode;
		off_t ot=st.st_size;
		if(S_ISSOCK(mt)){
			printf("s");
		}
		else if(S_ISLNK(mt)){
			printf("l");
		}
		else if(S_ISREG(mt)){
			printf("-");
		}
		else if(S_ISBLK(mt)){
			printf("b");
		}
		else if(S_ISDIR(mt)){
			printf("d");
		}
		else if(S_ISCHR(mt)){
			printf("c");
		}
		else if(S_ISFIFO(mt)){
			printf("p");
		}
	   	printf("%c",(mt & S_IRUSR)?'r':'-');
   		printf("%c",(mt & S_IWUSR)?'w':'-');
   		printf("%c",(mt & S_IXUSR)?'x':'-');

   		printf("%c",(mt & S_IRGRP)?'r':'-');
   		printf("%c",(mt & S_IWGRP)?'w':'-');
   		printf("%c",(mt & S_IXGRP)?'x':'-');

   		printf("%c",(mt & S_IROTH)?'r':'-');
   		printf("%c",(mt & S_IWOTH)?'w':'-');
   		printf("%c",(mt & S_IXOTH)?'x':'-');

   		printf(" %d ",(int)((st.st_nlink)));

   		struct passwd *pw=getpwuid(st.st_uid);
   		printf(" %s",pw->pw_name);	
   		struct group *gw=getgrgid(st.st_uid);
   		printf(" %s",gw->gr_name);
   		printf(" %ld",ot);
   		
   		char time[100]={'\0'};
   		strftime(time,100,"%d-%m-%y %H:%M",localtime(&(st.st_mtime)));
   		printf("\t%s",time);
	}
}