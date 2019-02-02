CC := gcc
RM := rm -f
LIBS =
CFLAGS += `pkg-config --cflags libgnome-2.0 libgnomeui-2.0` -Wall
LDFLAGS += `pkg-config --libs libgnome-2.0 libgnomeui-2.0` -lm -Wall
TARGET = ImageViewer
OBJS = fileselect.o imageviewerutility.o ImageWindow.o main.o mainwindow.o

all: $(TARGET)

clean:
		$(RM)  *.exe *.o ${TARGET}

ImageViewer: ${OBJS}
		$(CC) -o ${TARGET} ${OBJS} ${LDFLAGS}

main.o:
		$(CC) -c main.c ${CFLAGS}

fileselect.o:
		$(CC) -c fileselect.c ${CFLAGS}

imageviewerutility.o:
		$(CC) -c imageviewerutility.c ${CFLAGS}
	
ImageWindow.o:
	$(CC) -c ImageWindow.c ${CFLAGS}
	
mainwindow.o:
	$(CC) -c mainwindow.c ${CFLAGS}
