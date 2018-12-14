CC := g++
RM := rm -f
LIBS =

all: gtest

clean:
	$(RM)  *.exe *.o

basic: basic.o
	$(CC) basic.o -o basic
basic.o: basic.cpp
	$(CC) -c basic.cpp -o basic.o

mainzz3: mainzz3.o
	$(CC) mainzz3.o -o mainzz3
mainzz3.o: openjudge/mainzz3.cpp
	$(CC) -c openjudge/mainzz3.cpp -o mainzz3.o

main0001: main0001.o
	$(CC) main0001.o -o main0001
main0001.o: main0001.cpp
	$(CC) -c main0001.cpp -o main0001.o

main0003: main0003.o
	$(CC) main0003.o -o main0003
main0003.o: main0003.cpp
	$(CC) -c main0003.cpp -o main0003.o

main0005: main0005.o
	$(CC) main0005.o -o main0005
main0005.o: main0005.cpp
	$(CC) -c main0005.cpp -o main0005.o

main0006: main0006.o
	$(CC) main0006.o -o main0006
main0006.o: main0005.cpp
	$(CC) -c main0006.cpp -o main0006.o
	
main0016: main0016.o
	$(CC) main0016.o -o main0016
main0016.o: main0016.cpp
	$(CC) -c main0016.cpp -o main0016.o

# 获取极大值和极小值
get_max_min: get_max_min.o
	$(CC) get_max_min.o -o get_max_min
get_max_min.o: get_max_min.cpp
	$(CC) -c get_max_min.cpp -o get_max_min.o
	
main