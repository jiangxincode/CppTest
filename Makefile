cc=gcc
OBJECT=main elevator inter\
	   floor_one floor_two floor_three floor_four floor_five\
	   inter_control inter_show
all:$(OBJECT)

%:%.c
	$(cc) -Wall -o $@ $<
.PHONY:clean
clean:
	rm $(OBJECT) 
