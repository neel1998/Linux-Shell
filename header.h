#ifndef HEAD_H
	#define HEAD_H
	char *trim(char *s);
	void exec_lsl(char *d);
	void exec_ls(char *ss);
	void exec_pinfo(char *ss,int g);
	int e(char *i);
	void print_prompt();
	void exec_remind(char *ss);
	void exec_clock(char *ss);
	char *redirect_out(char *s);
	char * redirect_in(char * s);
	void piping(char *ss);
	void exec_jobs();
	void exec_kjob(int pid,int signal);
	void printjobs();
	void exec_bg(int pid);
	void exec_fg(int pid);

	extern char global_pwd[1000];
	extern char global_home[1000];
	extern int infd,outfd;
	extern int run;
	struct job{
   		int no;
   		char name[1000];
   		char state[1000];
   		char pid[1000];
   		char time[1000];
	};
	extern struct  job jobs[1000];
	// extern int pipefd[2];

	struct proc{
		char name[1000];
		int pid;
		int killed;
	};
	extern struct proc proc_arr[1000];
    extern int proc_size;

#endif