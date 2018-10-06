shell: \
	 	main.o trim.o exec_lsl.o exec_ls.o exec_pinfo.o execute.o print_prompt.o exec_remind.o exec_clock.o redirect_out.o redirect_in.o piping.o exec_jobs.o exec_kjob.o exec_bg.o exec_fg.o 
	 $(CC) -g -o shell $^	
clean:
	@rm -f *.o shell
main.o:
	$(CC) -g -c main.c
trim.o:
	$(CC) -g -c trim.c
exec_lsl.o:
	$(CC) -g -c exec_lsl.c
exec_ls.o:
	$(CC) -g -c exec_ls.c
exec_pinfo.o:
	$(CC) -g -c exec_pinfo.c
execute.o:
	$(CC) -g -c execute.c
print_prompt.o:
	$(CC) -g -c print_prompt.c
exec_remind.o:
	$(CC) -g -c exec_remind.c
exec_clock.o:
	$(CC) -g -c exec_clock.c
redirect_out.o:
	$(CC) -g -c redirect_out.c
redirect_in.o:
	$(CC) -g -c redirect_in.c
piping.o:
	$(CC) -g -c piping.c
exec_jobs.o:
	$(CC) -g -c exec_jobs.c
exec_kjob.o:
	$(CC) -g -c exec_kjob.c
exec_bg.o:
	$(CC) -g -c exec_bg.c
exec_fg.o:
	$(CC) -g -c exec_fg.c