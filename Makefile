OBJECTS = std_err_process.o wrapsock.o
BIN = daytimetcpcli daytimetcpcliv6 daytimetcpsrv

all:$(BIN)

daytimetcpcli:daytimetcpcli.o $(OBJECTS)
	gcc -o $@ $^ -Wall
daytimetcpcliv6:daytimetcpcliv6.o $(OBJECTS)
	gcc -o $@ $^ -Wall
daytimetcpsrv:daytimetcpsrv.o $(OBJECTS)
	gcc -o $@ $^ -Wall
std_err_process.o:std_err_process.c
	gcc -c $^ -Wall
sockwrap.o:wrapsock.c
	gcc -c $^ -Wall
clean:
	rm $(BIN) *.o *.orig
