OBJECTS = std_err_process.o wrapsock.o str_echo.o writen.o
BIN = daytimetcpcli daytimetcpcliv6 daytimetcpsrv daytimetcpsrv1\
	  tcpserv01

all:$(BIN)

daytimetcpcli:daytimetcpcli.o $(OBJECTS)
	gcc -o $@ $^ -Wall
daytimetcpcliv6:daytimetcpcliv6.o $(OBJECTS)
	gcc -o $@ $^ -Wall
daytimetcpsrv:daytimetcpsrv.o $(OBJECTS)
	gcc -o $@ $^ -Wall
daytimetcpsrv1:daytimetcpsrv1.o $(OBJECTS)
	gcc -o $@ $^ -Wall
tcpserv01:tcpserv01.o $(OBJECTS)
	gcc -o $@ $^ -Wall
std_err_process.o:std_err_process.c
	gcc -c $^ -Wall
sockwrap.o:wrapsock.c
	gcc -c $^ -Wall
str_echo.o:str_echo.c
	gcc -c $^ -Wall
writen.o:writen.c
	gcc -c $^ -Wall
clean:
	rm $(BIN) *.o
