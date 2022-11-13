cc=gcc
OBJECT=main elevator inter\
	   floor_one floor_two floor_three floor_four floor_five\
	   show
all:$(OBJECT)

%:%.c
	$(cc) -Wall -o $@ $< `pkg-config --cflags --libs gtk+-3.0`
.PHONY:clean
clean:
	rm $(OBJECT) 
