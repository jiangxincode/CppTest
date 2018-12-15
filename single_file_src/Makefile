CC := g++
RM := rm -f
LIBRARY += -pthread
LDFLAGS += -std=c++11 -Wall
SRCS     = $(wildcard *.cpp)
#SRCS     = hwoj_get_lights_count.cpp
OBJS     = $(patsubst %.cpp, %.o, $(SRCS))
TARGETS  = $(SRCS:%.cpp=%)

$(info $(OBJS))
$(info $(TARGETS))

all : $(TARGETS)

$(TARGETS): %: %.o
	$(CC) $(LDFLAGS) $(LIBRARY) -o $@ $<

$(OBJS) : %.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	$(RM) $(TARGETS) $(OBJS)

#.SUFFIXES:
.PHONY : all clean