all:daytimetcpcli daytimetcpcliv6

daytimetcpcli:daytimetcpcli.o std_err_process.o
	gcc -o $@ $^ -Wall
daytimetcpcliv6:daytimetcpcliv6.o std_err_process.o
	gcc -o $@ $^ -Wall
daytimetcpcli.o:daytimetcpcli.c
	gcc -c $^ -Wall
daytimetcpcliv6.o:daytimetcpcliv6.c
	gcc -c $^ -Wall
std_err_process.o:std_err_process.c
	gcc -c $^ -Wall
clean:
	rm daytimetcpcli daytimetcpcliv6 *.o
